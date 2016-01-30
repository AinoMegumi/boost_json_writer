#pragma once
#include <boost/property_tree/ptree.hpp>
#include <string>
#include <type_traits>
namespace detail {
	using std::nullptr_t;
	template<typename char_type, typename T>
	struct arithmetic_to_string_helper;
	template<typename T>
	struct arithmetic_to_string_helper<char, T> {
		std::string operator()(T n) { return std::to_string(n); }
	};
	template<typename T>
	struct arithmetic_to_string_helper<wchar_t, T> {
		std::wstring operator()(T n) { return std::to_wstring(n); }
	};

	template<typename char_type, typename T, std::enable_if_t < std::is_arithmetic<T>::value, nullptr_t> = nullptr>
	std::basic_string<char_type> arithmetic_to_string(T n) {
		return arithmetic_to_string_helper<char_type, T>()(n);
	}
	template <
		typename char_type, typename value_type, 
		bool value_is_string = 
			std::is_same<value_type, std::basic_string<char_type>>::value
			|| (std::is_pointer<value_type>::value && std::is_same<std::remove_cv_t<std::remove_pointer_t<value_type>>, char_type>::value), 
		bool value_is_arithmetic = std::is_arithmetic<value_type>::value
	> struct boost_ptree_put_value_helper;
	template<typename char_type, typename value_type> struct boost_ptree_put_value_helper<char_type, value_type, true, false> {
		using key_type = std::basic_string<char_type>;
		key_type key;
		value_type value;
		boost_ptree_put_value_helper(key_type key, value_type value) 
			noexcept(std::is_nothrow_move_constructible<key_type>::value || std::is_nothrow_copy_constructible<key_type>::value)
			: key(std::move_if_noexcept(key)), value(std::move_if_noexcept(value)){}
	};
	template<typename char_type, typename value_type> struct boost_ptree_put_value_helper<char_type, value_type, false, true> {
		using key_type = std::basic_string<char_type>;
		using data_type = key_type;
		key_type key;
		data_type value;
		boost_ptree_put_value_helper(key_type key, value_type value) : key(std::move_if_noexcept(key)), value(arithmetic_to_string<char_type>(value)){}
	};


	using namespace boost::property_tree;
	template<class K, class D, class C, typename char_type, typename value_type> 
	basic_ptree<K, D, C> & operator|(basic_ptree<K, D, C> & tree, const boost_ptree_put_value_helper<char_type, value_type>& info) {
		return tree.put(info.key, info.value);
	}
}
template<typename char_type, typename value_type>
detail::boost_ptree_put_value_helper<char_type, value_type> put_value(const std::basic_string<char_type>& key, value_type value) { return{ key, value }; }
template<typename char_type, typename value_type>
detail::boost_ptree_put_value_helper<char_type, value_type> put_value(const char_type* key, value_type value) { return{ std::basic_string<char_type>(key), value }; }

void write_utf8_with_bom_file(const char* filename, const boost::property_tree::wptree& tree);
void write_utf8_with_bom_file(const std::string& filename, const boost::property_tree::wptree& tree);
#ifndef _WIN32
void write_utf8_with_bom_file(const char* filename, const boost::property_tree::ptree& tree);
void write_utf8_with_bom_file(const std::string& filename, const boost::property_tree::ptree& tree);
#endif

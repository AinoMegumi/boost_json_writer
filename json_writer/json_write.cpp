#include"json_write.h"
#include <boost/property_tree/json_parser.hpp>
#include <fstream>
#include <locale>
#include <codecvt>
namespace detail {
	void create_utf8_with_bom_file(const char* filename) {
		std::ofstream file(filename, std::ios::out | std::ios::binary);
		constexpr unsigned char utf8[] = { 0xEF, 0xBB, 0xBF, '\0' };
		file << utf8;
	}
}
void write_utf8_with_bom_file(const char* filename, const boost::property_tree::wptree& tree) {
	detail::create_utf8_with_bom_file(filename);
	std::wofstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	file.open(filename, std::ios::app | std::ios::binary);
	file.imbue(std::locale(std::locale("japanese"), new std::codecvt_utf8_utf16<wchar_t>()));//UTF16 -> UTF-8(wchar_t in Windows.)
	boost::property_tree::write_json(file, tree);
}
void write_utf8_with_bom_file(const std::string& filename, const boost::property_tree::wptree& tree) {
	write_utf8_with_bom_file(filename.c_str(), tree);
}
#ifndef _WIN32
void write_utf8_with_bom_file(const char* filename, const boost::property_tree::ptree& tree) {
	detail::create_utf8_with_bom_file(filename);
	std::ofstream file(filename, std::ios::app | std::ios::binary);
	boost::property_tree::write_json(file, tree);
}
void write_utf8_with_bom_file(const std::wstring& filename, const boost::property_tree::wptree& tree) {
	write_utf8_with_bom_file(filename.c_str(), tree);
}
#endif

#include"json_write.h"
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/optional.hpp>

json_write::json_write(std::string filepath, std::string parent) {
	this->filepath = filepath;
	this->parent = parent;
}

void json_write::write_string_data(boost::property_tree::ptree& p, std::string tag, std::string data) {
	p.put(tag, data);
}

void json_write::write_int_data(boost::property_tree::ptree& p, std::string tag, int data) {
	this->write_string_data(p, tag, std::to_string(data));
}

void json_write::end(boost::property_tree::ptree child) {
	this->pt.add_child(this->parent, child);
	write_json(this->filepath, this->pt);
}

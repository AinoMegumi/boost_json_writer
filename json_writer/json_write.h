#pragma once
#include<boost/property_tree/ptree.hpp>
#include<string>

class json_write {
private:
	std::string filepath, parent;
	boost::property_tree::ptree pt;
public:
	json_write(std::string filepath, std::string parent);
	void write_string_data(boost::property_tree::ptree& p, std::string tag, std::string data);
	void write_int_data(boost::property_tree::ptree& p, std::string tag, int data);
	void end(boost::property_tree::ptree child);
};
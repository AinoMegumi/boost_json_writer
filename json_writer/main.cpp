#include"json_write.h"
#include<utility>

int main() {
	json_write json("test.json", "Data");
	boost::property_tree::ptree p, child;
	json.write_int_data(child, "num", 12);
	json.write_string_data(child, "str", "�݂肠");
	p.push_back(std::make_pair("", child));
	json.end(p);
	return 0;
}
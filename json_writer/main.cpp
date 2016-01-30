#include "json_write.h"
#include <utility>
#include <iostream>
int main() {
	try {
		std::locale::global(std::locale("japanese"));
		boost::property_tree::wptree p, child;
		child | put_value(L"num", 12);
		child | put_value(L"str", L"�݂肠");
		p.push_back(std::make_pair(L"", child));
		std::cout << "start writing json...";
		write_utf8_with_bom_file("test.json", p);
		std::cout << "done." << std::endl;
	}
	catch (const std::exception& er) {
		std::cerr << er.what() << std::endl;
	}
	return 0;
}
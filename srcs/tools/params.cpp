#include "tools.hpp"

//from string to vector of string of potencial param
std::vector<std::string>	params(std::string s){
	std::istringstream iss;
	iss.str(s);
	std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                 std::istream_iterator<std::string>());
	return (results);
}

std::vector<std::string>	paramsSeparedByComas(std::string txt){
	std::vector<std::string> 	v;
	size_t						pos = txt.find(',');
	while	(pos != std::string::npos){
		txt.replace(pos, 1, " ");
		pos = txt.find(',');
	}
	v = params(txt);
	return v;
}
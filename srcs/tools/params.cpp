#include "tools.hpp"

//from string to vector of string of potencial param
std::vector<std::string>	params(std::string s){
	std::istringstream iss;
	iss.str(s);
	std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                 std::istream_iterator<std::string>());
	return (results);
}
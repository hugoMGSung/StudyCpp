#include <boost/algorithm/string.hpp>
#include <string>

std::string str = "Hello World";
boost::to_upper(str);
std::string newstr = boost::to_upper_copy<std::string>("Hello World");
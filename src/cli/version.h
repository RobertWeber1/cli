#pragma once
#include <string>


namespace cli
{


class Version
{
public:
	static const std::string project_name;
	static const std::string git_tag;
	static const std::string build_date;
};


} //namespace cli

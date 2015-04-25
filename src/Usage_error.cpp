#include "Usage_error.hpp"

Usage_error::Usage_error(const std::string &error): _msg(error)
{

}

Usage_error::~Usage_error() throw()
{

}

const char *Usage_error::what() const throw()
{
	return (_msg.c_str());
}

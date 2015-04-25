#ifndef SYSTEM_ERROR_HPP_
# define SYSTEM_ERROR_HPP_

#include <stdexcept>
#include <iostream>
#include <sstream>
#include <string.h>

# define USAGE "./nibbler width height lib.so"

class Usage_error: public std::exception
{
public:
	~Usage_error() throw();
	Usage_error(const std::string &);
	const char *what() const throw();

private:
	std::string _msg;
};


#endif /* !USAGE_ERROR_HPP_ */

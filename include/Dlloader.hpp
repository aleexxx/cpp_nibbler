#ifndef DLLOADER_HPP_
# define DLLOADER_HPP_

#include <dlfcn.h>
#include <stdlib.h>
#include "Displaymodule.hpp"

class dlloader
{
public:
	dlloader();
	~dlloader();
	IDisplayModule* getInstance(std::string const &);
};

#endif /* !DLLOADER_HPP_ */

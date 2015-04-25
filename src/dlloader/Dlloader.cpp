#include "Dlloader.hpp"
#include "Usage_error.hpp"

dlloader::dlloader()
{

}

dlloader::~dlloader()
{

}

IDisplayModule* dlloader::getInstance(std::string const &name)
{
	void				*dlhandle;
	IDisplayModule 		*(*external_function)();
	std::string error;

	if (!(dlhandle = dlopen(name.c_str(), RTLD_LAZY)))
	{
		error = "Error dlopen : ";
		error += dlerror();
		throw Usage_error(error);
	}
	if (!(external_function = reinterpret_cast<IDisplayModule *(*)()> (dlsym(dlhandle, "Instanciate"))))
	{
		error = "Error dlsym : ";
		error += dlerror();
		dlclose(dlhandle);
		throw Usage_error(error);
	}
	return (external_function());
}

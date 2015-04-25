#ifndef IDISPLAYMODULE_HPP_
# define IDISPLAYMODULE_HPP_

#include <iostream>

class nibbler;

class IDisplayModule
{
	public:
		virtual ~IDisplayModule() {}
		virtual std::string const &getName() const = 0;
		virtual void init(const int &, const int &) = 0;
		virtual void stop(const int &, const int &, const int &) = 0;
		virtual void catchkey(bool &, int &, int &) = 0;
		virtual void display(int **, const int &, const int &) const = 0;
};

#endif /* IDISPLAYMODULE_HPP_ */

#ifndef LIBRARY_ONE_HPP
# define LIBRARY_ONE_HPP

#include <dlfcn.h>
#include <stdlib.h>
#include <iostream>

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Displaymodule.hpp"
#include "Rotation.hpp"

# define WHITE 255, 255, 255

class opengl: public IDisplayModule, public rotation
{
public:
	opengl();
	~opengl();
	void init(const int &, const int &);
	void stop(const int &, const int &, const int &);
	void catchkey(bool &, int &, int &);
	void display(int **, const int &, const int &) const;
	std::string const &getName() const;

protected:
	std::string const _name;
	int my_rotation;
};

#endif /* !LIBRARY_ONE_HPP */

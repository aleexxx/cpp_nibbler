#ifndef LIBRARY_NCURSES_HPP
# define LIBRARY_NCURSES_HPP

#include <dlfcn.h>
#include <stdlib.h>
#include <iostream>
#include <ncurses.h>
#include "Displaymodule.hpp"
#include "Rotation.hpp"

# define INIT "Fail on Initscr()"
# define CLEAR "Fail on clear()"
# define NOECHO "Fail on noecho()"
# define CBREAK "Fail on cbreak()"
# define KEYPAD "Fail on keypad()"
# define NODELAY "Fail on nodelay()"
# define MVADDCH "Fail on mvaddch()"

class library_ncurses: public IDisplayModule, public rotation
{
public:
	library_ncurses();
	~library_ncurses();
    void init(const int &, const int &);
    void stop(const int &, const int &, const int &);
    void catchkey(bool &, int &, int &);
    void display(int **, const int &, const int &) const;
	std::string const & getName() const;
protected:
  std::string const _name;
  int	my_rotation;
};

#endif /* !LIBRARY_NCURSES_HPP */

#include "Graphic_error.hpp"
#include "Common.hpp"
#include "Library_ncurses.hpp"

Graphic_error::Graphic_error(const int my_library, const std::string &error)
{
    const char * const lib[] = {"SDL", "OPENGL", "NCURSES", "MINILIBX"};
    this->library = lib[my_library];
    if (my_library == NCURSES)
    {
        endwin();
    }
    this->_msg = "[" + library + "] : " + error;
}

Graphic_error::~Graphic_error()
{

}

const char *Graphic_error::what() const throw()
{
    return (_msg.c_str());
}

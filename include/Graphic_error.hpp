#ifndef GRAPHIC_ERROR_HPP
# define GRAPHIC_ERROR_HPP

#include <iostream>

class Graphic_error: public std::exception
{
  public:
    Graphic_error(const int, const std::string &);
    ~Graphic_error() throw();
    const char *what() const throw();

  private:
    std::string _msg;
    std::string library;
    static const char * const lib[];
};

#endif /* !GRAPHIC_ERROR_HPP */

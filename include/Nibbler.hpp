#ifndef NIBBLER_HPP_
# define NIBBLER_HPP_

/* INCLUDE */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <list>
#include "Displaymodule.hpp"
#include "Usage_error.hpp"
#include "Common.hpp"

/* MACCRO */
# define FOOD	3
# define MAP_SIZE 16
# define SNAKE_BODY 1
# define SNAKE_HEAD 2
# define MAX_SIZE_X 50
# define MAX_SIZE_Y 50
# define MIN_SIZE_X 10
# define MIN_SIZE_Y 10

struct  s_coord
{
  int x;
  int y;
};

/* CLASS */
class nibbler
{
public:
	nibbler(int, int, const std::string &);
	~nibbler();
	void delete_tail();
    void add_tail();
	bool add_head(int, int);
	int  is_collision(int, int);
	void refreshmap();
	void gameloop();
 	int	 getXHead();
 	int	 getYHead();
  void generatefood();

protected:
  IDisplayModule *obj;
  int	x_direction;
  int	y_direction;
  std::list<s_coord> snake;
  int 	**map;
  int	width;
  int	height;
};

#endif /* !NIBBLER_HPP_*/

#include <unistd.h>
#include "Nibbler.hpp"
#include "Dlloader.hpp"

nibbler::nibbler(int width, int height, const std::string &str)
{
	int 	x = (width / 2) - 2;
	int		y = (height / 2);
	int		i = 0;

	this->height = height;
	this->width = width;
	this->map = new int *[width];
	for (i = 0; i < width; i++)
	{
		this->map[i] = new int [height];
	}
	i = 0;
	while (i < 3)
	{
		this->snake.push_back({x, y});
		x++;
		i++;
	}
	dlloader loader;

	this->obj = loader.getInstance("./" + str);
	this->x_direction = 1;
	this->y_direction = 0;
}

nibbler::~nibbler()
{

}

void nibbler::gameloop()
{
	bool game_over = false;
	bool escape = false;
	int	 x_head;
	int	 y_head;

	generatefood();
	obj->init(this->width, this->height);
	while (!game_over && !escape)
	{
		obj->catchkey(escape, this->x_direction, this->y_direction);
	 	x_head = getXHead() + this->x_direction;
		y_head = getYHead() + this->y_direction;
		if (!escape && ((game_over = add_head(x_head, y_head)) == false))
		{
		  	refreshmap();
		  	obj->display(this->map, this->width, this->height);
          	delete_tail();
		}
		usleep(99000);
	}
	obj->stop(this->width, this->height, this->snake.size());
}

int nibbler::is_collision(int x, int y)
{
  if ((x >= this->width) || (x < 0) || (y >= this->height) || (y < 0))
    return (1);
  for(std::list<s_coord>::iterator it = this->snake.begin(); it != this->snake.end(); it++)
    {
      if (it->x == x && it->y == y)
		{
	  		return (1);
		}
      else if ((it->x >= this->width) || (it->x < 0) || (it->y >= this->height) || (it->y < 0))
		{
			return (1);
		}
    }
    if (this->map[x][y] == FOOD)
      {
      	return (FOOD);
      }
    return (0);
}


void nibbler::refreshmap()
{
	int x;
	int y = 0;

	while (y < this->height)
	{
		x = 0;
		while (x < this->width)
		{
			if (this->map[x][y] != FOOD)
				this->map[x][y] = 0;
			x = x + 1;
		}
		y = y + 1;
	}
	for (std::list<s_coord>::iterator it = this->snake.begin(); it != this->snake.end(); it++)
	{
		if (it->x == getXHead() && it->y == getYHead())
			this->map[it->x][it->y] =  SNAKE_HEAD;
		else
			this->map[it->x][it->y] = SNAKE_BODY;
	}
}

void nibbler::generatefood()
{
	int x = -1;
	int y = -1;
	int coli = false;

	srand(time(NULL));
	while ((coli = is_collision(x, y)) == true)
	{
		x = rand() % this->width;
		y = rand() % this->height;
	}
	this->map[x][y] = FOOD;
}

void nibbler::delete_tail()
{
	this->snake.pop_front();
}

void	nibbler::add_tail()
{
  int	x_back;
  int	y_back;
  int	x_prevback;
  int	y_prevback;
  std::list<s_coord>::iterator	it;

  if (snake.size() >= 2)
    {
      it = this->snake.begin();
      x_back = this->snake.front().x;
      y_back = this->snake.front().y;
      std::advance(it, 1);
      x_prevback = (*it).x;
      y_prevback = (*it).y;
      x_back = x_back - x_prevback + x_back;
      y_back = y_back - y_prevback + y_back;
      if (x_back < this->width && x_back >= 0 && y_back < this->height && y_back >= 0)
		{
      		this->snake.push_front({x_back, y_back});
		}
    }
}

bool nibbler::add_head(int x, int y)
{
  int	collision;

  if ((collision = is_collision(x, y)) == 0)
    this->snake.push_back({x, y});
  else
    {
      if (collision == FOOD)
      {
      	this->snake.push_back({x, y});
		add_tail();
		generatefood();
      	return (false);
      }
	  return (true);
    }
  return (false);
}

int	nibbler::getXHead()
{
  if (snake.size() >= 1)
    {
      return (this->snake.back().x);
    }
  return (-1);
}

int	nibbler::getYHead()
{

  if (snake.size() >= 1)
    {
      return (this->snake.back().y);
    }
  return (-1);
}

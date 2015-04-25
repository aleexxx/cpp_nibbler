#include <stdio.h>
#include <unistd.h>
#include "Library_ncurses.hpp"
#include "Nibbler.hpp"
#include "Common.hpp"
#include "Graphic_error.hpp"

library_ncurses::library_ncurses(): _name("NCurses library")
{
  this->my_rotation = 0;
  std::cout << "Loading " << getName() << " ... " << std::endl;
}

library_ncurses::~library_ncurses()
{

}

void library_ncurses::init(const int &width, const int& height)
{
  if (initscr() == NULL)
  {
        throw Graphic_error(NCURSES, INIT);
  }
  if (height > 0)
       if (clear() == ERR)
            throw Graphic_error(NCURSES, CLEAR);
  if (width > 0)
     if (noecho() == ERR)
         throw Graphic_error(NCURSES, NOECHO);
  if (cbreak() == ERR)
      throw Graphic_error(NCURSES, CBREAK);
  if (keypad(stdscr, TRUE) == ERR)
    throw Graphic_error(NCURSES, KEYPAD);
  if (nodelay(stdscr, TRUE) == ERR)
    throw Graphic_error(NCURSES, NODELAY);
}

void library_ncurses::stop(const int &width, const int &height, const int &score)
{
  (void) width;
  (void) height;
  int row,col;
  clear();
  start_color();
  getmaxyx(stdscr,row,col);
  attron(COLOR_PAIR(1));
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  mvprintw((row/2) - 4,(col-strlen("                          ____      "))/2,"                          ____      ");
  mvprintw((row/2) - 3,(col-strlen(" ________________________\x2F x  \x5c___\x5c"))/2," ________________________\x2F x  \x5c___\x2F");
  mvprintw((row/2) - 2,(col-strlen("<_____________________________\x2F   \x5c "))/2,"<_\x5c_\x2F_\x5c_\x2F_\x5c_\x2F_\x5c_\x2F_\x5c_\x2F_\x5c_______\x2F   \x5c ");


  mvprintw(row/2,(col-strlen(" _______  _______  __   __  _______    _______  __   __  _______  ______   "))/2," _______  _______  __   __  _______    _______  __   __  _______  ______   ");
  mvprintw((row/2) + 1,(col-strlen("|       ||   _   ||  |_|  ||       |  |       ||  | |  ||       ||    _ |  "))/2,"|       ||   _   ||  |_|  ||       |  |       ||  | |  ||       ||    _ |  ");
  mvprintw((row/2) + 2,(col-strlen("|    ___||  |_|  ||       ||    ___|  |   _   ||  |_|  ||    ___||   | ||  "))/2,"|    ___||  |_|  ||       ||    ___|  |   _   ||  |_|  ||    ___||   | ||  ");
  mvprintw((row/2) + 3,(col-strlen("|   | __ |       ||       ||   |___   |  | |  ||       ||   |___ |   |_||_ "))/2,"|   | __ |       ||       ||   |___   |  | |  ||       ||   |___ |   |_||_ ");
  mvprintw((row/2) + 4,(col-strlen("|   ||  ||       ||       ||    ___|  |  |_|  ||       ||    ___||    __  |"))/2,"|   ||  ||       ||       ||    ___|  |  |_|  ||       ||    ___||    __  |");
  mvprintw((row/2) + 5,(col-strlen("|   |_| ||   _   || ||_|| ||   |___   |       | |     | |   |___ |   |  | |"))/2,"|   |_| ||   _   || ||_|| ||   |___   |       | |     | |   |___ |   |  | |");
  mvprintw((row/2) + 6,(col-strlen("|_______||__| |__||_|   |_||_______|  |_______|  |___|  |_______||___|  |_|"))/2,"|_______||__| |__||_|   |_||_______|  |_______|  |___|  |_______||___|  |_|");
mvprintw((row/2) + 7,(col-strlen(""))/2,"");
  mvprintw((row/2) + 9,(col-strlen("Score : 1\n"))/2,"Score : %d", score + 1);
  mvprintw(row + 100, col + 100, NULL, NULL);
 getch();

  sleep(4);
  endwin();
  std::cout << "GAME OVER" << std::endl;
  std::cout << "Your snake was " << score + 1 << " m long !" << std::endl;
}

void    library_ncurses::display(int **map, const int &width, const int &height) const
{
  int   x;
  int   y = 0;

  clear();
  while (y < height)
    {
      x = 0;
      while (x < width)
        {
          if (map[x][y] == SNAKE_BODY)
            {
    	      if (mvaddch(y, x, '#') == ERR)
                    throw Graphic_error(NCURSES, MVADDCH);
            }
         else if (map[x][y] == SNAKE_HEAD)
         {
             if (mvaddch(y, x, '#') == ERR)
                throw Graphic_error(NCURSES, MVADDCH);
         }
          else if (map[x][y] == FOOD)
            {
	           if (mvaddch(y, x, 'O') == ERR)
                    throw Graphic_error(NCURSES, MVADDCH);
            }
	  else
	    {
	      if (mvaddch(y, x, '.') == ERR)
            throw Graphic_error(NCURSES, MVADDCH);
	    }
          x = x + 1;
        }
      y = y + 1;
    }
  refresh();
}


void            library_ncurses::catchkey(bool &game_over, int &x, int &y)
{
  int ch = getch();

  if (ch == KEY_EXIT)
    game_over = true;
  if (ch == KEY_LEFT)
    {
      rotation::rotation_left(this->my_rotation, x, y);
    }
  if (ch == KEY_RIGHT)
    {
      rotation::rotation_right(this->my_rotation, x, y);
    }
}


std::string const &library_ncurses::getName() const
{
  return (this->_name);
}

extern "C" IDisplayModule *Instanciate()
{
  return (new library_ncurses());
}

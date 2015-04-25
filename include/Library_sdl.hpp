#ifndef LIBRARY_SDL_HPP_
# define LIBRARY_SDL_HPP_

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <unistd.h>
#include <stdio.h>
#include "Displaymodule.hpp"
#include "Rotation.hpp"
#include "Common.hpp"

class library_sdl: public IDisplayModule, public rotation
{
public:
  library_sdl();
  ~library_sdl();
  void init(const int &, const int &);
  void stop(const int &, const int &, const int &);
  void catchkey(bool &, int &, int &);
  void	display(int **, const int &, const int &) const;
  std::string const &getName() const;
protected:
  std::string const _name;
  int	my_rotation;
  SDL_Surface	*screen;
  SDL_Surface	*snake_element;
  SDL_Surface	*food_element;
  SDL_Surface   *snake_head;
  Mix_Music       *game_music;
  Mix_Music       *music_game_over;
  TTF_Font *police;
  Uint32	background;
};

#endif /* !LIBRARY_SDL_HPP_ */

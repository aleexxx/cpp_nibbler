#include "Library_sdl.hpp"
#include "Nibbler.hpp"
#include "Graphic_error.hpp"
#include "Common.hpp"

library_sdl::library_sdl(): _name("SDL library")
{
  this->my_rotation = 0;
  this->screen = NULL;
  std::cout << "Loading " << getName() << " ... " << std::endl;
}

library_sdl::~library_sdl()
{
}

void	library_sdl::init(const int &width, const int& height)
{
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    throw Graphic_error(SDL, SDL_GetError());
  if(TTF_Init() == -1)
     throw Graphic_error(SDL, TTF_GetError());
  if ((this->screen = SDL_SetVideoMode(width * SIZE_SQUARE, height * SIZE_SQUARE, 32, 0)) == NULL)
      throw Graphic_error(SDL, SDL_GetError());
  SDL_WM_SetCaption("The Best of Nibbler", NULL);
  this->background = SDL_MapRGB(this->screen->format, 255, 204, 0);
  if ((this->food_element = SDL_LoadBMP("ressource/food.bmp")) == NULL)
    throw Graphic_error(SDL, SDL_GetError());
  if ((this->snake_element = SDL_LoadBMP("ressource/snake_body.bmp")) == NULL)
    throw Graphic_error(SDL, SDL_GetError());
  if ((this->snake_head = SDL_LoadBMP("ressource/snake_head.bmp")) == NULL)
    throw Graphic_error(SDL, SDL_GetError());
  if (SDL_FillRect(this->screen, NULL, this->background) != 0)
      throw Graphic_error(SDL, SDL_GetError());
  if (SDL_Flip(this->screen) == -1)
      throw Graphic_error(SDL, SDL_GetError());
  if ((this->police = TTF_OpenFont("ressource/game_over.ttf", (width * SIZE_SQUARE) * 0.3)) == NULL)
      throw Graphic_error(SDL, TTF_GetError());
  if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
      throw Graphic_error(SDL, Mix_GetError());
  if ((this->game_music = Mix_LoadMUS("ressource/game_music.ogg")) == NULL)
    throw Graphic_error(SDL, Mix_GetError());
  if ((this->music_game_over = Mix_LoadMUS("ressource/game_over.ogg")) == NULL)
    throw Graphic_error(SDL, Mix_GetError());
  Mix_PlayMusic(this->game_music, -1);
}

void	library_sdl::stop(const int &width, const int &height, const int &score)
{
  SDL_Surface *text = NULL;
  SDL_Surface *text2 = NULL;
  SDL_Rect position;
  SDL_Color black;
  std::string str;

 Mix_PauseMusic();
  Mix_PlayMusic(this->music_game_over, -1);
  black.r = 255;
  black.g = 255;
  black.b = 255;
  str = "Score : " + std::to_string(score);
  if ((text = TTF_RenderText_Blended(police, "Game over !", black)) == NULL)
      throw Graphic_error(SDL, TTF_GetError());
  if ((text2 = TTF_RenderText_Blended(police, str.c_str(), black)) == NULL)
      throw Graphic_error(SDL, TTF_GetError());
  if ((SDL_FillRect(this->screen, NULL, SDL_MapRGB(this->screen->format, 0, 0, 0))) == -1)
      throw Graphic_error(SDL, SDL_GetError());
  position.x = (width * SIZE_SQUARE) / 2 - (width * SIZE_SQUARE) * 0.3;
  position.y = (height * SIZE_SQUARE) / 2  - (width * SIZE_SQUARE) * 0.2;
  if ((SDL_BlitSurface(text, NULL, this->screen, &position)) != 0)
      throw Graphic_error(SDL, SDL_GetError());
  position.y = position.y + (width * SIZE_SQUARE) * 0.2;
  if (SDL_BlitSurface(text2, NULL, this->screen, &position) != 0)
    throw Graphic_error(SDL, SDL_GetError());
  if (SDL_Flip(this->screen) == -1)
    throw Graphic_error(SDL, SDL_GetError());

  sleep(6);

  Mix_FreeMusic(this->game_music);
  Mix_FreeMusic(this->music_game_over);
  Mix_CloseAudio();
  TTF_CloseFont(police);
  TTF_Quit();
  SDL_FreeSurface(text);
  SDL_FreeSurface(text2);
  SDL_FreeSurface(this->food_element);
  SDL_FreeSurface(this->snake_element);
  SDL_FreeSurface(this->screen);
  SDL_Quit();
}

void	library_sdl::display(int **map, const int &width, const int &height) const
{
  int	x;
  int	y = 0;
  SDL_Rect	position;

  if (SDL_FillRect(this->screen, NULL, this->background) == -1)
    throw Graphic_error(SDL, SDL_GetError());
  while (y < height)
    {
      x = 0;
      while (x < width)
        {
	       position.y = SIZE_SQUARE * y;
	       position.x = SIZE_SQUARE * x;
    	  if (map[x][y] == SNAKE_BODY)
          {
    	      if (SDL_BlitSurface(this->snake_element, NULL, this->screen, &position) != 0)
                throw Graphic_error(SDL, SDL_GetError());
          }
          else if (map[x][y] == SNAKE_HEAD)
          {
              if (SDL_BlitSurface(this->snake_head, NULL, this->screen, &position) != 0)
                throw Graphic_error(SDL, SDL_GetError());
          }
    	  else if (map[x][y] == FOOD)
    	    {
    	      if (SDL_BlitSurface(this->food_element, NULL, this->screen, &position) != 0)
                throw Graphic_error(SDL, SDL_GetError());
    	    }
	         x = x + 1;
        }
      y = y + 1;
    }
  if (SDL_Flip(this->screen) == -1)
    throw Graphic_error(SDL, SDL_GetError());
}

void		library_sdl::catchkey(bool &game_over, int &x, int &y)
{
  SDL_Event	event;

  while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
        game_over = true;
      if (event.type == SDL_KEYDOWN)
        {
      	  if (event.key.keysym.sym == SDLK_ESCAPE)
             {
      	      game_over = true;
             }
      	  if (event.key.keysym.sym == SDLK_LEFT)
             {
      	      rotation::rotation_left(this->my_rotation, x, y);
             }
          if (event.key.keysym.sym == SDLK_RIGHT)
             {
      	      rotation::rotation_right(this->my_rotation, x, y);
      	     }
      	}
    }
}

std::string const &library_sdl::getName() const
{
  return (this->_name);
}

extern "C" IDisplayModule *Instanciate()
{
  return (new library_sdl());
}

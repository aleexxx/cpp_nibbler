#include "Library_opengl.hpp"
#include "Nibbler.hpp"
#include "Common.hpp"
#include "Graphic_error.hpp"

opengl::opengl(): _name("opengl.so")
{
    this->my_rotation = 0;
	std::cout << "Charging " << getName() << " ..." << std::endl;
}

opengl::~opengl()
{
}

void opengl::init(const int &width, const int &height)
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
        throw Graphic_error(OPENGL, SDL_GetError());
    SDL_WM_SetCaption("Old school snake", NULL);
    if (SDL_SetVideoMode(width * SIZE_SQUARE, height * SIZE_SQUARE, 32, SDL_OPENGL) == NULL)
        throw Graphic_error(OPENGL, SDL_GetError());
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    SDL_GL_SwapBuffers();
}

void opengl::stop(const int &width, const int &height, const int &score)
{
    (void) width;
    (void) height;

    std::cout << "Game over !" << std::endl;
    std::cout << "Score: " <<  score << std::endl;

}

void opengl::display(int **map, const int &width, const int &height) const
{
    int x;
    int y = 0;
    float j;
    float k;

    while (y < height)
    {
        x = 0;
        while (x < width)
        {
            j = 2 * x;
            j = j / width;
            j = j - 1;
            k = 2 * y + 0.2 * height;
            k = k / height;
            k = k - 1;
            k = k * -1;
            if (map[x][y] == SNAKE_BODY)
                glColor3ub(WHITE);
            else if (map[x][y] == SNAKE_HEAD)
                glColor3ub(WHITE);
            else if (map[x][y] == FOOD)
                glColor3ub(WHITE);
            else
                glColor3ub(0, 0, 0);
            glBegin(GL_QUADS);
            glVertex2d(j, k);
            glVertex2d(j, k + 0.2);
            glVertex2d(j + 0.2, k + 0.2);
            glVertex2d(j + 0.2, k);
            glEnd();
            x = x + 1;
        }
        y = y + 1;
    }
    glFlush();
    SDL_GL_SwapBuffers();
}

void opengl::catchkey(bool &game_over, int &x, int &y)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                game_over = true;
            }
            else if (event.key.keysym.sym == SDLK_LEFT)
            {
               rotation::rotation_left(this->my_rotation, x, y);
            }
            else if (event.key.keysym.sym == SDLK_RIGHT)
            {
               rotation::rotation_right(this->my_rotation, x, y);
            }
        }
    }
}

std::string const &opengl::getName() const
{
	return (this->_name);
}

extern "C" IDisplayModule *Instanciate()
{
  return (new opengl());
}

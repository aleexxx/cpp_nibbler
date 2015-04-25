##
## Makefile for nibbler in /home/page_a/rendu/cpp_nibbler
##
## Made by Alexandre PAGE
## Login   <page_a@epitech.net>
##
## Started on  Fri Mar 13 16:51:55 2015 Alexandre PAGE
## Last update Tue Mar 31 15:28:27 2015 Tony Kem
##

NAME		= nibbler

SRC_DIR		= src

SRCS		= $(SRC_DIR)/Nibbler.cpp \
			  		$(SRC_DIR)/main.cpp \
			  		$(SRC_DIR)/dlloader/Dlloader.cpp \
			  		$(SRC_DIR)/Usage_error.cpp \
					$(SRC_DIR)/Graphic_error.cpp

OBJ_DIR		= obj

OBJS		= $(SRCS:.cpp=.o)

RM			= rm -rf

MKDIR	  = mkdir -p

CC			= g++

CXXFLAGS	+= -W -Wall -Wextra -Werror -fPIC -std=c++11
CXXFLAGS	+= -I./include

LDFLAGS		= -ldl

OGL_FOLDER	= opengl

LIB 		= lib

OGL_NAME 	= $(LIB)/lib_nibbler_opengl.so

OGL_SRC		= $(SRC_DIR)/$(OGL_FOLDER)/Library_opengl.cpp \
			  			$(SRC_DIR)/Rotation.cpp \
						$(SRC_DIR)/Graphic_error.cpp

OGL_OBJ 	= $(OGL_SRC:.cpp=.o)

SDL_FOLDER	= sdl

SDL_NAME	= $(LIB)/lib_nibbler_sdl.so

SDL_SRC		= $(SRC_DIR)/$(SDL_FOLDER)/Library_sdl.cpp \
			  		   $(SRC_DIR)/Rotation.cpp \
					   $(SRC_DIR)/Graphic_error.cpp

SDL_OBJ		= $(SDL_SRC:.cpp=.o)

NCR_FOLDER  = ncurses

NCR_NAME	= $(LIB)/lib_nibbler_ncurses.so

NCR_SRC		= $(SRC_DIR)/$(NCR_FOLDER)/Library_ncurses.cpp \
			  			$(SRC_DIR)/Rotation.cpp \
						$(SRC_DIR)/Graphic_error.cpp

NCR_OBJ		= $(NCR_SRC:.cpp=.o)

all: $(NAME) $(SDL_NAME) $(OGL_NAME) $(NCR_NAME)

$(NAME): $(OBJS)
	$(MKDIR) $(LIB)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) -lncurses

$(OGL_NAME): $(OGL_OBJ)
	$(CC) -shared $(OGL_OBJ) -o $(OGL_NAME) -lGL -lGLU -lSDL

$(SDL_NAME): $(SDL_OBJ)
	$(CC) -shared $(SDL_OBJ) -o $(SDL_NAME) -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer

$(NCR_NAME): $(NCR_OBJ)
	$(CC) -shared $(NCR_OBJ) -o $(NCR_NAME) -lncurses

clean:
	$(RM) $(OBJS)
	$(RM) $(OGL_OBJ)
	$(RM) $(SDL_OBJ)
	$(RM) $(NCR_OBJ)
	$(RM) $(LIBX_OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIB)

re: fclean all

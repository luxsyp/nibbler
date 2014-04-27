##
## Makefile for  in /home/locque_d//rendu/proj/nibbler
##
## Made by damien locque
## Login   <locque_d@epitech.net>
##
## Started on  Tue Mar  8 14:27:01 2011 damien locque
## Last update Sun Mar 20 23:16:08 2011 damien locque
##

NAME_EXE	= ./bin/nibbler
SRCS_EXE	= ./srcs/main.cpp		\
		  ./srcs/Nibbler.cpp		\
		  ./srcs/Core.cpp		\
		  ./srcs/myException.cpp
OBJS_EXE	= $(SRCS_EXE:.cpp=.o)

NAME_NCURSE	= ./bin/lib_nibbler_Ncurse.so
SRCS_NCURSE	= ./srcs/myException.cpp	\
		  ./Ncurses/Ncurse.cpp
OBJS_NCURSE	= $(SRCS_NCURSE:.cpp=.o)

NAME_SFML	= ./bin/lib_nibbler_Sfml.so
SRCS_SFML	= ./srcs/myException.cpp	\
		  ./SFML/Sfml.cpp
OBJS_SFML	= $(SRCS_SFML:.cpp=.o)

NAME_OPENGL	= ./bin/lib_nibbler_Opengl.so
SRCS_OPENGL	= ./srcs/myException.cpp	\
		  ./Opengl/Opengl.cpp
OBJS_OPENGL	= $(SRCS_OPENGL:.cpp=.o)

RM		= rm -f
CXX		= g++
LDFLAGS		+= -ldl
CXXFLAGS	+= -fPIC -Wall -Wextra -Werror

all		: $(NAME_EXE) $(NAME_NCURSE) $(NAME_SFML) $(NAME_OPENGL)

$(NAME_EXE)	:$(OBJS_EXE)
		$(CXX) -o $(NAME_EXE) $(OBJS_EXE) $(LDFLAGS)

$(NAME_NCURSE)	: $(OBJS_NCURSE)
		$(CXX) -shared -o $(NAME_NCURSE) $(OBJS_NCURSE) -lncurses

$(NAME_SFML)	: $(OBJS_SFML)
		$(CXX) -shared -o $(NAME_SFML) $(OBJS_SFML) -lsfml-graphics -lsfml-window -lsfml-system

$(NAME_OPENGL)	: $(OBJS_OPENGL)
		$(CXX) -shared -o $(NAME_OPENGL) $(OBJS_OPENGL) -lSDL -lGL -lGLU

clean		:
		$(RM) $(OBJS_EXE) $(OBJS_NCURSE) $(OBJS_SFML) $(OBJS_OPENGL)

fclean		: clean
		$(RM) $(NAME_EXE) $(NAME_NCURSE) $(NAME_SFML) $(NAME_OPENGL)

re		: fclean all

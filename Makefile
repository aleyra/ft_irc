CC = c++

NAME := ircserv

CPPFLAGS := -Wall -Wextra -Werror -std=c++98

SRCS := main.cpp Server.cpp

OBJS := ${SRCS:.cpp=.o}

OBJDIR := $(addprefix objs/, $(OBJS))

INCLUDES := Server.hpp

INCDIR := $(addprefix includes/, $(INCLUDES))

all : $(NAME)

$(NAME) : $(OBJDIR)
	echo "\x1b[34m $1[Compiling $(NAME)]\x1b[0m"
	$(CC) $(OBJDIR) -o $(NAME) $(CPPFLAGS)
	echo "\x1b[34m $1[Done]\x1b[0m"

objs/%.o : srcs/%.cpp $(INCDIR) Makefile
	mkdir -p objs
	$(CC) -c $< -I includes $(CPPFLAGS) -o $@

clean :
	$(RM) $(OBJDIR)

fclean : clean
	$(RM) $(NAME) 

re : fclean all

.PHONY : all clean fclean re
.SILENT:

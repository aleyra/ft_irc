.PHONY: all clean fclean re bonus
# Name of file
NAME			=	ircserv

# Name directory
PATH_INC		=	includes
PATH_SRC        =	srcs
PATH_OBJ        =	objs
PATH_LOG        =	logs


# List of sources

SRCS_CMDS		=	error.cpp invite.cpp  list.cpp mode.cpp names.cpp \
					nick.cpp oper.cpp pass.cpp ping.cpp pong.cpp quit.cpp \
					topic.cpp user_cmd.cpp
SRCS_CLASS		=	Server.cpp channel.cpp user.cpp
SRCS_TOOLS		=	numeric_reply.cpp params.cpp make_full_command.cpp timeout.cpp
SRCS 			=	$(addprefix $(PATH_SRC)/cmds/, $(SRCS_CMDS)) \
					$(addprefix $(PATH_SRC)/class/, $(SRCS_CLASS)) \
					$(addprefix $(PATH_SRC)/tools/, $(SRCS_TOOLS)) \
					$(addprefix $(PATH_SRC)/, )  main.cpp #add files à la racine

OBJS			=	$(addprefix $(PATH_OBJ)/, $(notdir $(SRCS:.cpp=.o)))
ALL_INCS		=	channel.hpp cmds.hpp Server.hpp tools.hpp user.hpp
INCS			=	$(addprefix $(PATH_INC)/, $(ALL_INCS))

# Commands of compilation
COMP			=	c++
COMP_FLAG		=	-Wall -Wextra -Werror -std=c++98 -g3
COMP_ADD		=	-I $(PATH_INC)

# Others Command
RM				=	/bin/rm

# Color Code and template 
_YELLOW			=	\033[38;5;184m
_GREEN			=	\033[38;5;46m
_RESET			=	\033[0m
_INFO			=	[$(_YELLOW)INFO$(_RESET)]
_SUCCESS		=	[$(_GREEN)SUCCESS$(_RESET)]


all:	$(NAME)
		@ echo "$(_SUCCESS) Compilation done"

bonus : all

$(PATH_OBJ):
		mkdir -p $@

$(NAME):	$(OBJS)
		$(COMP) $(COMP_FLAG) $(OBJS) -o $(NAME)

$(PATH_OBJ)/%.o : $(PATH_SRC)/*/%.cpp  $(INCS) | $(PATH_OBJ)
		$(COMP) $(COMP_FLAG) $(COMP_ADD) -c $< -o $@
		@ echo "$(_INFO) Compilation of $*"

$(PATH_OBJ)/%.o : $(PATH_SRC)/%.cpp  $(INCS)
		$(COMP) $(COMP_FLAG) $(COMP_ADD) -c $< -o $@
		@ echo "$(_INFO) Compilation of $*"

clean:
		@ $(RM) -rf $(PATH_OBJ)
		@ echo "$(_INFO) Deleted files and directory"

fclean: clean
		@ $(RM) -rf $(NAME)

re: fclean all
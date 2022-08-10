.PHONY: all clean fclean re bonus
# Name of file
NAME		=	servirc

# Name directory
PATH_INC	=	includes
PATH_SRC	=	srcs
PATH_OBJ	=	objs
PATH_LOG	=	logs

# List of sources
SRCS_CMDS		= 	whois.cpp whowas.cpp
SRCS_CLASS		= 	channel.cpp user.cpp
SRCS			=	$(addprefix $(PATH_SRC)/cmds/, $(CMDS)) \
					$(addprefix $(PATH_SRC)/, )  main.cpp #add files à la racine

OBJS		=	$(addprefix $(PATH_OBJ)/, $(notdir $(SRCS:.c=.o)))
INCS		=	$(PATH_INC)/channel.hpp numeric_reply.hpp user.hpp

# Commands of compilation
COMP		=	c++
COMP_FLAG	=	-Wall -Wextra -Werror
COMP_ADD	=	-I$(PATH_INC) 

# Others Command
RM			=	/bin/rm

# Color Code and template code
_YELLOW		=	\033[38;5;184m
_GREEN		=	\033[38;5;46m
_RESET		=	\033[0m
_INFO		=	[$(_YELLOW)INFO$(_RESET)]
_SUCCESS	=	[$(_GREEN)SUCCESS$(_RESET)]

# Functions
all:	init $(NAME)
	@ echo "$(_SUCCESS) Compilation done"

init:
	 $(shell mkdir -p $(PATH_OBJ))

bonus :	all

$(NAME): 	$(OBJS) $(LIBFT)
			$(CC) $(COMP_FLAG) $(OBJS) $(RL_FLAG) $(LIBFT) -o $(NAME)

$(PATH_OBJ)/%.o : $(PATH_SRC)/*/%.cpp  $(INCS)
	@ $(COMP) $(COMP_FLAG) $(COMP_ADD) -c $< -o $@
	@ echo "$(_INFO) Compilation of $*"

$(PATH_OBJ)/%.o : $(PATH_SRC)/%.c  $(INCS)
	@ $(COMP) $(COMP_FLAG) $(COMP_ADD) -c $< -o $@
	@ echo "$(_INFO) Compilation of $*"

clean:
	@ $(RM) -rf $(PATH_OBJ)
	echo "$(_INFO) Deleted files and directory"

fclean: clean
	@ $(RM) -rf $(NAME)

re: fclean all

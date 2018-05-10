##
## EPITECH PROJECT, 2018
## NETiles
## File description:
## Makefile utils
##

SRC_DIR	?=	src/

SRCS	=	$(addprefix $(SRC_DIR),$(SOURCES))
OBJS	=	$(SRCS:.cpp=.o)

CPPFLAGS	+=	-W -Wall -Wextra
CPPFLAGS	+=	-Iinclude

LDFLAGS	+=	-lsfml-graphics
LDFLAGS	+=	-lsfml-network
LDFLAGS	+=	-lsfml-system
LDFLAGS	+=	-lsfml-window

################################################################################

SHELL	=	/bin/bash
PRINT	=	printf "$(PROJECT):\t" ; printf
CC	=	g++

RESET	=	\033[0m
RED	=	\033[0;31m
GREEN	=	\033[0;32m
YELLOW	=	\033[0;33m
BLUE	=	\033[0;34m
MAGENTA	=	\033[0;35m
CYAN	=	\033[1;36m

################################################################################

all: $(NAME)

debug: CPPFLAGS += -g3
debug: $(NAME)

$(NAME): prebuild $(OBJS)
	@ $(PRINT) "$(YELLOW)Building project binary$(RESET)\n"
	@ $(PRINT) "  [  ]  $(BLUE)%b$(RESET)\\r" $(NAME)
	@ $(CC) -o $(NAME) $(LDFLAGS) $(OBJS) && \
	  ($(PRINT) "  [$(GREEN)OK$(RESET)]  $(CYAN)%b$(RESET)\n" $(NAME) ; exit 0) || \
	  ($(PRINT) "  [$(RED)XX$(RESET)]  $(CYAN)%b$(RESET)\n" $(NAME) ; exit 1)

prebuild:
	@ $(PRINT) "$(YELLOW)%b$(RESET)\n" "Compiling source files"

clean:
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Deleting object files"
	@ $(RM) $(OBJS)
	@ printf "$(GREEN)Done$(RESET)\n"

fclean: clean
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Deleting $(NAME)"
	@ $(RM) $(NAME)
	@ printf "$(GREEN)Done$(RESET)\n"

re: fclean all
de: fclean debug

.cpp.o:
	@ $(PRINT) "  [  ]  $(CYAN)%b$(RESET)\\r" $<
	@ $(CC) -c $< -o $@ $(CPPFLAGS) && \
	  ($(PRINT) "  [$(GREEN)OK$(RESET)]  $(CYAN)%b$(RESET)\n" $<) || \
	  ($(PRINT) "  [$(RED)XX$(RESET)]  $(CYAN)%b$(RESET)\n" $< ; exit 1)

.PHONY: all debug $(NAME) prebuild clean fclean re de .c.o
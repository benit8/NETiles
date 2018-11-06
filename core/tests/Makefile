##
## EPITECH PROJECT, 2018
## Moon Landing
## File description:
## Makefile utils
##

RM	=	rm -f
CC	=	g++

################################################################################

NAME	=	a.out

SRCS	=	main.cpp			\
		../Application.cpp		\
		../EventHandler.cpp		\
		../FontLoader.cpp		\
		../StateManager.cpp		\
		../Window.cpp			\
		../GUI/GUI.cpp			\
		../GUI/Env.cpp			\
		../GUI/Widget.cpp		\
		../GUI/Box.cpp			\
		../GUI/Button.cpp

OBJS	=	$(SRCS:.cpp=.o)

################################################################################

CXXFLAGS	+=	-std=c++17
CXXFLAGS	+=	-I.
# CXXFLAGS	+=	-W -Wall -Wextra

LDFLAGS	+=	-lsfml-system		\
		-lsfml-window		\
		-lsfml-graphics

################################################################################

all: $(NAME)

debug: CXXFLAGS += -g3
debug: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
de: fclean debug

dump:
	@ echo "CXXFLAGS: [$(CXXFLAGS)]"
	@ echo "LDFLAGS: [$(LDFLAGS)]"

.PHONY: all debug $(NAME) clean fclean re de dump
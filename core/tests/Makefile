##
## EPITECH PROJECT, 2018
## Moon Landing
## File description:
## Makefile utils
##

NAME	?=	a.out
PROJECT	?=	$(NAME)

SRC_DIR	?=	./
SOURCES	?=	main.cpp			\
		../Application.cpp		\
		../EventHandler.cpp		\
		../FontLoader.cpp		\
		../StateManager.cpp		\
		../Window.cpp			\
		../GUI/GUI.cpp			\
		../GUI/Env.cpp			\
		../GUI/Object.cpp		\
		../GUI/Box.cpp

SRCS	=	$(addprefix $(SRC_DIR),$(SOURCES))
OBJS	=	$(SRCS:.cpp=.o)
DEPS	=	$(SRCS:.cpp=.dp)

GLOBAL_LIBS	?=	sfml-system		\
			sfml-window		\
			sfml-graphics
LOCAL_LIBS	?=
LIBS_DIR	?=	lib/
LIBS_PATHS	=	$(addprefix $(LIBS_DIR),$(LOCAL_LIBS))

INCLUDE_DIRS	?=	./

################################################################################

# CXXFLAGS	+=	-W -Wall -Wextra
CXXFLAGS	+=	$(addprefix -I,$(INCLUDE_DIRS))
CXXFLAGS	+=	$(patsubst %,-I%/include/,$(LIBS_PATHS))

LDFLAGS	+=	$(addprefix -l,$(GLOBAL_LIBS))
LDFLAGS	+=	-L$(LIBS_DIR)
LDFLAGS	+=	$(addprefix -l,$(LOCAL_LIBS))

################################################################################

SHELL	=	/bin/bash
PRINT	=	printf "$(PROJECT):\t" ; printf
RM	=	rm -f
CC	=	g++

RESET	=	\033[0m
RED	=	\033[0;31m
GREEN	=	\033[0;32m
YELLOW	=	\033[0;33m
BLUE	=	\033[0;34m
MAGENTA	=	\033[0;35m
CYAN	=	\033[1;36m

################################################################################

all: libs $(NAME)

debug: CXXFLAGS += -g3
debug: dlibs $(NAME)

libs:
	@ for dir in $(LIBS_PATHS); do make -sC $$dir; done

dlibs:
	@ for dir in $(LIBS_PATHS); do make -sC $$dir debug; done

$(NAME): prebuild $(OBJS)
	@ $(PRINT) "$(YELLOW)Building project binary$(RESET)\n"
	@ $(PRINT) "  [  ]  $(BLUE)%b$(RESET)\\r" $(NAME)
	@ $(CC) -o $(NAME) $(OBJS) $(LDFLAGS) && \
	  ($(PRINT) "  [$(GREEN)OK$(RESET)]  $(CYAN)%b$(RESET)\n" $(NAME) ; exit 0) || \
	  ($(PRINT) "  [$(RED)XX$(RESET)]  $(CYAN)%b$(RESET)\n" $(NAME) ; exit 1)

prebuild:
	@ $(PRINT) "$(YELLOW)%b$(RESET)\n" "Compiling source files"

clean:
	@ for dir in $(LIBS_PATHS); do make -sC $$dir clean; done
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Deleting object files"
	@ $(RM) $(OBJS) $(DEPS)
	@ printf "$(GREEN)Done$(RESET)\n"

fclean: clean
	@ for dir in $(LIBS_PATHS); do make -sC $$dir fclean; done
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Deleting $(NAME)"
	@ $(RM) $(NAME)
	@ printf "$(GREEN)Done$(RESET)\n"

re: fclean all
de: fclean debug

.cpp.o:
	@ $(PRINT) "  [  ]  $(CYAN)%b$(RESET)\\r" $<
	@ $(CC) $(CXXFLAGS) -MMD -MP -o $@ -MF $*.dp -c $< && \
	  ($(PRINT) "  [$(GREEN)OK$(RESET)]  $(CYAN)%b$(RESET)\n" $<) || \
	  ($(PRINT) "  [$(RED)XX$(RESET)]  $(CYAN)%b$(RESET)\n" $< ; exit 1)

%.dp: ;
-include *.dp

dump:
	@ echo "CXXFLAGS: [$(CXXFLAGS)]"
	@ echo "LDFLAGS: [$(LDFLAGS)]"

.PHONY: all debug libs dlibs $(NAME) prebuild clean fclean re de .cpp.o dump
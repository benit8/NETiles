##
## EPITECH PROJECT, 2018
## NETiles
## File description:
## Makefile
##

SERVER_DIR	=	Server/
CLIENT_DIR	=	Client/
EDITOR_DIR	=	Editor/

################################################################################

all: server client editor

server:
	@ make -sC $(SERVER_DIR)

client:
	@ make -sC $(CLIENT_DIR)

editor:
	@ make -sC $(EDITOR_DIR)

debug:
	@ make debug -sC $(SERVER_DIR)
	@ make debug -sC $(CLIENT_DIR)
	@ make debug -sC $(EDITOR_DIR)

clean:
	@ make clean -sC $(SERVER_DIR)
	@ make clean -sC $(CLIENT_DIR)
	@ make clean -sC $(EDITOR_DIR)

fclean:
	@ make fclean -sC $(SERVER_DIR)
	@ make fclean -sC $(CLIENT_DIR)
	@ make fclean -sC $(EDITOR_DIR)

re:
	@ make re -sC $(SERVER_DIR)
	@ make re -sC $(CLIENT_DIR)
	@ make re -sC $(EDITOR_DIR)

de:
	@ make de -sC $(SERVER_DIR)
	@ make de -sC $(CLIENT_DIR)
	@ make de -sC $(EDITOR_DIR)

.PHONY: all server client editor debug clean fclean re de
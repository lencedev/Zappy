##
## EPITECH PROJECT, 2023
## B-YEP-400-MPL-4-1-zappy-owen1.bolling
## File description:
## Makefile
##

AI = IA/
GUI = GUI/
SERVER = SERVER/

all: ai gui server

ai:
	@make -sC $(AI)

gui:
	@make -sC $(GUI)

server:
	@make -sC $(SERVER)

clean:
	@make clean -sC $(AI)
	@make clean -sC $(GUI)
	@make clean -sC $(SERVER)

fclean:
	@make fclean -sC $(AI)
	@make fclean -sC $(GUI)
	@make fclean -sC $(SERVER)

re: fclean all

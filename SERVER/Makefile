##
## EPITECH PROJECT, 2023
## MYTeams
## File description:
## Makefile
##

SRC_DIRS = ./src

BIN = ../zappy_server

SRCS := $(shell find $(SRC_DIRS) -name "*.c")
OBJS = $(SRCS:.c=.o)

CPPFLAGS = $(shell find ./include -type d | awk '{printf "-I%s ", $$0}')

CC = gcc -g

all : $(BIN)

$(BIN) : $(OBJS)
	@$(CC) $(OBJS) -o $(BIN) $(LDFLAGS) $(LDLIBS)

%.o :	%.c
	@echo "\e[92;1m[\e[36;1m⏳ \e[92;1m] \
\e[1;32mCompiling\e[1;35m $< \e[1;32m...\e[1;0m"
	@$(CC) -o $@ -c $< $(CFLAGS) $(CPPFLAGS)
	@echo "    \e[32;1m✔ \e[34m\"\e[1;35m$(@)\e[34m\" \
\e[1;32mSuccessfully compiled !"

re : fclean all

fclean : clean
	@ $(RM) -rf $(BIN)

clean :
	@ $(RM) -rf $(OBJS)
	@ $(RM) -rf *.gcda
	@ $(RM) -rf *.gcno

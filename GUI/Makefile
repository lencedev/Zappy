##
## EPITECH PROJECT, 2023
## raylib-test
## File description:
## Makefile
##

BIN = ../zappy_gui

SRC = src/main.cpp \
		src/Client.cpp \
		src/Food.cpp \
		src/Stone.cpp \
		src/Tile.cpp \
		src/Game.cpp \
		src/Team.cpp \
		src/Trantor.cpp \
		src/Text.cpp \
		src/Button.cpp \
		src/Canva.cpp \
		src/Menu.cpp \
		src/InputBox.cpp \
		src/CheckBox.cpp

OBJ = $(SRC:.cpp=.o)

CXX = g++

CXXFLAGS = $(shell find ./include -type d | awk '{printf "-I%s ", $$0}')
CXXFLAGS += -g3

LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) -o $(BIN) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(BIN)

re: fclean all

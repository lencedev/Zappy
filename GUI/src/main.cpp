/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** main
*/

#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "Client.hpp"
#include "Game.hpp"
#include "Menu.hpp"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define IN_MENU 0
#define IN_GAME 1

void mainLoop()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Zappy");
    SetTargetFPS(60);
    Camera camera = { 0 };
    camera.position = Vector3{ 5.5f, 6.0f, 5.5f };
    camera.target = Vector3{ 0.0f, 0.5f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 10.0f;
    camera.projection = CAMERA_ORTHOGRAPHIC;
    int gameState = IN_MENU;
    bool initOnce = true;
    Shader mainShader = LoadShader(0, "GUI/assets/shaders/toon_water.fs");

    GUI::Menu menu(camera, mainShader);
    menu.createMenus();

    GUI::Game game(camera, mainShader);

    ToggleFullscreen();
    while (!WindowShouldClose()) {
        switch (gameState) {
            case IN_MENU:
                initOnce = true;
                menu.drawMenu(gameState);
                gameState = menu.getGameState();
                break;
            case IN_GAME:
                if (initOnce) {
                    initOnce = false;
                    GUI::Client client(menu.getMenuPort(), menu.getMenuHost());
                    client.connectToServer();
                    game = client.createGameFromServer(camera, mainShader);
                    game.setShowFps(menu.getShowFPS());
                    game.initGame();
                }
                game.drawGame();
                break;
        }
    }
}

int main(int argc, char **argv)
{
    mainLoop();
    return 0;
}
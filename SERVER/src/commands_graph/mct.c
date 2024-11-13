/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** mct
*/

#include "../../includes/zappy.h"

char *mct_buffer(t_server *server)
{
    char *response = malloc(sizeof(char) * 100);
    for (int i = 0; i < 100; i++) response[i] = '\0';
    for (int y = 0; y < server->world.height; y++) {
        for (int x = 0; x < server->world.width; x++) {
            char *response_tmp = malloc(sizeof(char) * 100);
            sprintf(response_tmp, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
            server->world.tiles[y][x].inventory.food,
            server->world.tiles[y][x].inventory.linemate,
            server->world.tiles[y][x].inventory.deraumere,
            server->world.tiles[y][x].inventory.sibur,
            server->world.tiles[y][x].inventory.mendiane,
            server->world.tiles[y][x].inventory.phiras,
            server->world.tiles[y][x].inventory.thystame);
            response_tmp = strdup(response_tmp);
            response = my_strcat(response, response_tmp);
            free(response_tmp);
        }
    }
    return response;
}

void mct(t_server *server, int client_fd)
{
    char *response = malloc(sizeof(char) * 100);

    for (int y = 0; y < server->world.height; y++) {
        for (int x = 0; x < server->world.width; x++) {
            sprintf(response, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
            server->world.tiles[y][x].inventory.food,
            server->world.tiles[y][x].inventory.linemate,
            server->world.tiles[y][x].inventory.deraumere,
            server->world.tiles[y][x].inventory.sibur,
            server->world.tiles[y][x].inventory.mendiane,
            server->world.tiles[y][x].inventory.phiras,
            server->world.tiles[y][x].inventory.thystame);
            send(client_fd, response, strlen(response), 0);
        }
    }
}

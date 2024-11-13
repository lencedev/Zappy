/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** bct
*/

#include "../../includes/zappy.h"

static char **get_args(t_server *server, int client_fd)
{
    char *str = strdup(server->buffer);
    char **tab = split(str, " ");

    if (tab[1] == NULL || tab[2] == NULL) {
        send(client_fd, "sbp\n", 4, 0);
        return NULL;
    }
    return tab;
}

void bct(t_server *server, int client_fd)
{
    char *response = malloc(sizeof(char) * 100);
    char **tab = get_args(server, client_fd);

    if (tab == NULL) return;
    int x_int = atoi(tab[1]);
    int y_int = atoi(tab[2]);
    if (x_int < 0 || x_int >= server->world.width || y_int < 0 ||
    y_int >= server->world.height) {
        send(client_fd, "sbp\n", 4, 0);
        return;
    }
    sprintf(response, "bct %d %d %d %d %d %d %d %d %d\n", x_int, y_int,
    server->world.tiles[y_int][x_int].inventory.food,
    server->world.tiles[y_int][x_int].inventory.linemate,
    server->world.tiles[y_int][x_int].inventory.deraumere,
    server->world.tiles[y_int][x_int].inventory.sibur,
    server->world.tiles[y_int][x_int].inventory.mendiane,
    server->world.tiles[y_int][x_int].inventory.phiras,
    server->world.tiles[y_int][x_int].inventory.thystame);
    send(client_fd, response, strlen(response), 0);
}

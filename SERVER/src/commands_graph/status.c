/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** status
*/

#include "../../includes/zappy.h"

void print_map_in_x_y(t_server *server, int client_fd)
{
    char *response = malloc(sizeof(char) * 100);
    char *tmp = malloc(sizeof(char) * 100);

    for (int y = 0; y < server->world.height; y++) {
        for (int x = 0; x < server->world.width; x++) {
            sprintf(tmp, "%d", server->world.tiles[y][x].players ? \
server->world.tiles[y][x].players->orientation : 9);
            response = my_strcat(response, tmp);
        }
        response = my_strcat(response, "\n");
    }
    send(client_fd, response, strlen(response), 0);
}

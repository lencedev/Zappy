/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** msz
*/

#include "../../includes/zappy.h"

char *msz_buffer(t_server *server)
{
    char *response = malloc(sizeof(char) * 100);

    sprintf(response, "msz %d %d\n", server->world.width, server->world.height);
    return response;
}

void msz(t_server *server, int client_fd)
{
    char *response = malloc(sizeof(char) * 100);

    sprintf(response, "msz %d %d\n", server->world.width, server->world.height);
    send(client_fd, response, strlen(response), 0);
}

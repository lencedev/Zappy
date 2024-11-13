/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** sgt
*/

#include "../../includes/zappy.h"

char *sgt_buffer(t_server *server)
{
    char *response = malloc(sizeof(char) * 100);

    sprintf(response, "sgt %d\n", server->world.frequency);
    return response;
}

void sgt(t_server *server, int client_fd)
{
    char *response = malloc(sizeof(char) * 100);

    sprintf(response, "sgt %d\n", server->world.frequency);
    send(client_fd, response, strlen(response), 0);
}

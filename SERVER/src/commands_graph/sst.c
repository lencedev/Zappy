/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** sst
*/

#include "../../includes/zappy.h"

static char **get_args(t_server *server, int client_fd)
{
    char *str = strdup(server->buffer);
    char **tab = split(str, " ");

    if (tab[1] == NULL) {
        send(client_fd, "sbp\n", 4, 0);
        return NULL;
    }
    return tab;
}

void sst(t_server *server, int client_fd)
{
    char *response = malloc(sizeof(char) * 100);
    char **tab = get_args(server, client_fd);
    if (tab == NULL) return;
    char *freq = tab[1];

    server->world.frequency = atoi(freq);
    sprintf(response, "sst %d\n", server->world.frequency);
    send(client_fd, response, strlen(response), 0);
}

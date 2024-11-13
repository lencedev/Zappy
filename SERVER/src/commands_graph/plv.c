/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** plv
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

void plv(t_server *server, int client_fd)
{
    char *response = malloc(sizeof(char) * 100);
    char **tab = get_args(server, client_fd);
    if (tab == NULL) return;
    int player_id = atoi(tab[1]);
    t_player *player = get_player_by_id(server, player_id);

    if (player == NULL) {
        sprintf(response, "sbp\n");
        send(client_fd, response, strlen(response), 0);
        return;
    }
    sprintf(response, "plv %d %d\n", player_id, player->level);
    send(client_fd, response, strlen(response), 0);
}
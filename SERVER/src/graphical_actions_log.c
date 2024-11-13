/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** graphical_actions_log
*/

#include "../includes/zappy.h"

void pnw_buffer(t_server *server, t_player *player)
{
    char *buffer = malloc(sizeof(char) * 100);

    sprintf(buffer, "pnw %d %d %d %d %d %s\n", player->id_client, player->x,
        player->y, player->orientation, player->level, player->team_name);
    send_data_graphic(server, buffer);
}

void pdi_buffer(t_server *server, t_player *player)
{
    char *buffer = malloc(sizeof(char) * 100);

    if (player == NULL) return;
    if (player->id_client == -1) return;
    sprintf(buffer, "pdi %d\n", player->id_client);
    send_data_graphic(server, buffer);
}

void pgt_buffer(t_server *server, t_player *player, int ressource)
{
    char *buffer = malloc(sizeof(char) * 100);

    sprintf(buffer, "pgt %d %d\n", player->id_client, ressource);
    send_data_graphic(server, buffer);
}

void pdr_buffer(t_server *server, t_player *player, int ressource)
{
    char *buffer = malloc(sizeof(char) * 100);

    sprintf(buffer, "pdr %d %d\n", player->id_client, ressource);
    send_data_graphic(server, buffer);
}

void send_data_graphic(t_server *server, char *data)
{
    if (server->graphical_fd == -1)
        return;
    send(server->graphical_fd, data, strlen(data), 0);
}

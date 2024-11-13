/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** left
*/

#include "../../includes/zappy.h"

void left(t_server* server, int client_fd)
{
    t_player *player = get_player_by_fd(server, client_fd);

    if (player == NULL) {
        send(client_fd, "ko\n", 3, 0);
        return;
    }
    switch (player->orientation) {
        case NORTH: player->orientation = WEST; break;
        case EAST: player->orientation = NORTH; break;
        case SOUTH: player->orientation = EAST; break;
        case WEST: player->orientation = SOUTH; break;
    }
    send(client_fd, "ok\n", 3, 0);
}

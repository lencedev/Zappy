/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** right
*/

#include "../../includes/zappy.h"

void right(t_server* server, int client_fd)
{
    t_player *player = get_player_by_fd(server, client_fd);

    if (player == NULL) {
        send(client_fd, "ko\n", 3, 0);
        return;
    }
    printf("Player orientation: %d\n", player->orientation);
    switch (player->orientation) {
        case NORTH: player->orientation = EAST; break;
        case EAST: player->orientation = SOUTH; break;
        case SOUTH: player->orientation = WEST; break;
        case WEST: player->orientation = NORTH; break;
    }
    printf("Player orientation: %d\n", player->orientation);
    send(client_fd, "ok\n", 3, 0);
}

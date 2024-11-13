/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** forward
*/

#include "../../includes/zappy.h"

void add_player_tiles(t_server *server, t_player *player)
{
    t_tile *tile = &server->world.tiles[player->y][player->x];
    t_player *tmp = tile->players;

    if (tmp == NULL) {
        tile->players = player;
        return;
    }
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = player;
}

t_player *remove_player(t_player *players, t_player *player)
{
    t_player *tmp = players;

    if (tmp == NULL)
        return NULL;
    if (tmp == player) {
        players = tmp->next;
        return players;
    }
    while (tmp->next != player)
        tmp = tmp->next;
    tmp->next = player->next;
    return players;
}

void forward_2(t_server *server, t_player *player)
{
    switch (player->orientation) {
        case NORTH:
            player->y = (player->y - 1 + server->world.height) %
                server->world.height;
            break;
        case EAST:
            player->x = (player->x + 1) % server->world.width;
            break;
        case SOUTH:
            player->y = (player->y + 1) % server->world.height;
            break;
        case WEST:
            player->x = (player->x - 1 + server->world.width) %
                server->world.width;
            break;
    }
}

void forward(t_server* server, int client_fd)
{
    t_player *player = get_player_by_fd(server, client_fd);

    if (player == NULL) {
        send(client_fd, "ko\n", 3, 0);
        return;
    }
    server->world.tiles[player->y][player->x].players = NULL;
    forward_2(server, player);
    // add_player_tiles(server, player);
    send(client_fd, "ok\n", 3, 0);
}

/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** list
*/

#include "../includes/zappy.h"

t_player *get_player_by_id(t_server *server, int player_id)
{
    t_player *player = server->world.players;

    while (player != NULL) {
        if (player->id_client == player_id)
            return (player);
        player = player->next;
    }
    return (NULL);
}

t_player *get_player_by_fd(t_server *server, int fd)
{
    t_player *player = server->world.players;

    while (player != NULL) {
        if (player->fd == fd)
            return (player);
        player = player->next;
    }
    return (NULL);
}

void add_player_players(t_server *server, t_player *player)
{
    t_player *tmp = server->world.players;

    if (tmp == NULL) {
        server->world.players = player;
        server->world.players->next = NULL;
        return;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = player;
    player->next = NULL;
}

t_player *strdup_team(t_player *player)
{
    t_player *tmp = malloc(sizeof(t_player));
    tmp->id = player->id;
    tmp->fd = player->fd;
    tmp->team_name = strdup(player->team_name);
    tmp->level = player->level;
    tmp->inventory.food = player->inventory.food;
    tmp->inventory.linemate = player->inventory.linemate;
    tmp->inventory.deraumere = player->inventory.deraumere;
    tmp->inventory.sibur = player->inventory.sibur;
    tmp->inventory.mendiane = player->inventory.mendiane;
    tmp->inventory.phiras = player->inventory.phiras;
    tmp->inventory.thystame = player->inventory.thystame;
    tmp->orientation = player->orientation;
    tmp->x = player->x;
    tmp->y = player->y;
    tmp->is_freezed = player->is_freezed;
    tmp->next = NULL;
    return (tmp);
}

void add_player_teams(t_player **tmp, t_player *player)
{
    t_player *tmp2 = strdup_team(player);

    if (*tmp == NULL) {
        *tmp = tmp2;
        return;
    }
    while ((*tmp)->next != NULL)
        (*tmp) = (*tmp)->next;
    (*tmp)->next = tmp2;
    tmp2->next = NULL;
}

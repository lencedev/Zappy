/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** eggs
*/

#include "../includes/zappy.h"

void add_egg(t_server *server, t_player *player)
{
    t_team *team = get_team_by_name(server, player->team_name);
    t_egg *egg = NULL;

    server->world.tiles[player->y][player->x].egg = malloc(sizeof(t_egg));
    server->world.tiles[player->y][player->x].egg->x = player->x;
    server->world.tiles[player->y][player->x].egg->y = player->y;
    server->world.tiles[player->y][player->x].egg->team_name = strdup(
        player->team_name);
    server->world.tiles[player->y][player->x].egg->next = NULL;
    egg = server->world.tiles[player->y][player->x].egg;
    if (team->eggs == NULL)
        team->eggs = egg;
    else {
        t_egg *tmp = team->eggs;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = egg;
    }
    team->nb_eggs += 1;
}

void remove_egg(t_server *server, t_egg *egg)
{
    t_team *team = get_team_by_name(server, egg->team_name);
    t_egg *tmp = team->eggs;

    team->nb_eggs -= 1;
    if (tmp == egg) {
        team->eggs = tmp->next;
        free(tmp);
        return;
    }
    while (tmp->next != egg)
        tmp = tmp->next;
    tmp->next = egg->next;
    free(egg);
}

t_egg *get_egg_by_team_name(t_server *server, char *team_name)
{
    t_team *team = get_team_by_name(server, team_name);
    t_egg *tmp = team->eggs;

    while (tmp != NULL) {
        if (strcmp(tmp->team_name, team_name) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

void add_player_at_egg(t_server *server, t_player *player)
{
    t_egg *egg = get_egg_by_team_name(server, player->team_name);

    if (egg == NULL)
        return;
    player->x = egg->x;
    player->y = egg->y;
    player->orientation = rand() % 4 + 1;
    server->world.tiles[player->y][player->x].players = player;
    remove_egg(server, egg);
    printf("Player %d born at %d %d\n", player->id, player->x, player->y);
}

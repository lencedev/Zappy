/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** utils
*/

#include "../includes/zappy.h"

void clear_buffer(t_server *server)
{
    for (int i = 0; i < BUFFER_SIZE + 1; i++)
        server->buffer[i] = '\0';
}

char **split(char *str, char *delim)
{
    char **tab = malloc(sizeof(char *) * 100);
    char *token = strtok(str, delim);
    int i = 0;

    while (token != NULL) {
        tab[i] = token;
        token = strtok(NULL, delim);
        i++;
    }
    tab[i] = NULL;
    return tab;
}

void remove_player_players(t_server *server, t_player *player)
{
    t_player *tmp = server->world.players;
    t_player *prev = NULL;

    if (tmp != NULL && tmp->id == player->id) {
        server->world.players = tmp->next;
        free(tmp);
        return;
    }
    while (tmp != NULL && tmp->id != player->id) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return;
    prev->next = tmp->next;
    free(tmp);
}

void remove_player_from_team(t_team *team, t_player *player)
{
    t_player *tmp = team->players;
    t_player *prev = NULL;

    if (tmp != NULL && tmp->id == player->id) {
        team->players = tmp->next;
        free(tmp);
        return;
    }
    while (tmp != NULL && tmp->id != player->id) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp != NULL) {
        prev->next = tmp->next;
        free(tmp);
    }
}

void remove_player_teams(t_server *server, t_player *player)
{
    t_team *team = server->world.teams;

    while (team != NULL) {
        remove_player_from_team(team, player);
        team = team->next;
    }
}

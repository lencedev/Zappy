/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** print
*/

#include "../includes/zappy.h"

void print_players(t_player *players)
{
    t_player *tmp = players;

    while (tmp != NULL) {
        printf("\n------\n");
        printf("Player: %d\n", tmp->fd);
        printf("Player Id: %d\n", tmp->id);
        printf("Player Team: %s\n", tmp->team_name);
        printf("Player Level: %d\n", tmp->level);
        printf("------\n");
        tmp = tmp->next;
    }
}

void print_teams(t_team *teams)
{
    t_team *tmp = teams;

    while (tmp != NULL) {
        printf("\n------[+]-----\n");
        printf("Team: %s\n", tmp->name);
        printf("Team Members: %d\n", tmp->num_members);
        printf("Players in the teams :\n");
        print_players(tmp->players);
        printf("\n------[+]-----\n");
        tmp = tmp->next;
    }
}

void calculate_resources(t_server *server, int *total_resources)
{
    int total_tiles = server->world.width * server->world.height;
    total_resources[0] = (int)(0.5 * total_tiles);
    total_resources[1] = (int)(0.3 * total_tiles);
    total_resources[2] = (int)(0.15 * total_tiles);
    total_resources[3] = (int)(0.1 * total_tiles);
    total_resources[4] = (int)(0.1 * total_tiles);
    total_resources[5] = (int)(0.08 * total_tiles);
    total_resources[6] = (int)(0.05 * total_tiles);
}

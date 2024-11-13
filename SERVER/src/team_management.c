/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** team_management
*/

#include "../includes/zappy.h"

void add_team(t_server* server, char* team_name)
{
    t_team* team = malloc(sizeof(t_team));
    team->name = team_name;
    team->max_members = 0;
    team->num_members = 0;
    team->players = NULL;
    team->eggs = NULL;
    team->next = server->world.teams;
    server->world.teams = team;
}

void set_max_members(t_server* server, int max_members)
{
    t_team* current_team = server->world.teams;
    while (current_team != NULL) {
        current_team->max_members = max_members;
        current_team = current_team->next;
    }
}

void parse_teams(t_server* server, char* argv[], int* index)
{
    while (argv[*index] && argv[*index][0] != '-') {
        add_team(server, argv[*index]);
        (*index)++;
    }
}

t_team *get_team_by_name(t_server *server, char *team_name)
{
    t_team *tmp = server->world.teams;

    while (tmp != NULL) {
        if (strcmp(tmp->name, team_name) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

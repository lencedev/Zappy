/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** tna
*/

#include "../../includes/zappy.h"

static void clear_buff(char *buffer)
{
    for (int i = 0; i < 100; i++)
        buffer[i] = '\0';
}

char *tna_buffer(t_server *server)
{
    char *response = malloc(sizeof(char) * 100);
    char *response_buffer = malloc(sizeof(char) * 100);
    t_team *team_tmp = server->world.teams;

    clear_buff(response_buffer);
    if (team_tmp == NULL) {
        sprintf(response, "ko\n");
        return response;
    }
    for (; team_tmp; team_tmp = team_tmp->next) {
        if (strcmp(team_tmp->name, "GRAPHIC") == 0)
            continue;
        sprintf(response, "tna %s\n", team_tmp->name);
        response_buffer = strcat(response_buffer, response);
    }
    return response_buffer;
}

void tna(t_server *server, int client_fd)
{
    char *response = malloc(sizeof(char) * 100);
    t_team *team_tmp = server->world.teams;

    if (team_tmp == NULL) {
        send(client_fd, "ko\n", 3, 0);
        return;
    }
    for (; team_tmp; team_tmp = team_tmp->next) {
        if (strcmp(team_tmp->name, "GRAPHIC") == 0)
            continue;
        sprintf(response, "tna %s\n", team_tmp->name);
        send(client_fd, response, strlen(response), 0);
    }
}

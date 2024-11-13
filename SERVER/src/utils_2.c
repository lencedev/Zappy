/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** utils_2
*/

#include "../includes/zappy.h"

char *my_strcat(const char *s1, const char *s2)
{
    char *res = malloc(strlen(s1) + strlen(s2) + 1);
    int a = 0;

    for (int i = 0; s1[i]; i++)
        res[a++] = s1[i];
    for (int i = 0; s2[i]; i++)
        res[a++] = s2[i];
    res[a] = '\0';
    return res;
}

char *get_ressource_name(int ressource)
{
    if (ressource == 0)
        return "food";
    if (ressource == 1)
        return "linemate";
    if (ressource == 2)
        return "deraumere";
    if (ressource == 3)
        return "sibur";
    if (ressource == 4)
        return "mendiane";
    if (ressource == 5)
        return "phiras";
    if (ressource == 6)
        return "thystame";
    return NULL;
}

int execute_command2(t_server *server, int client_fd, char *command_exec, int i)
{
    if (COMMANDS_AI[i].exec_time == 0) {
        COMMANDS_AI[i].func(server, client_fd);
        return 1;
    }
    t_player *player = get_player_by_fd(server, client_fd);
    add_actions(player, strdup(server->buffer),
    COMMANDS_AI[i].exec_time, COMMANDS_AI[i].func);
    return 1;
}

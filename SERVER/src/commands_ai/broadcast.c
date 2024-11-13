/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** broadcast
*/

#include "../../includes/zappy.h"

char *my_revstr(char *str)
{
    int i = 0;
    int j = strlen(str) - 1;
    char tmp;

    while (i < j) {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i++;
        j--;
    }
    return str;
}

char *itoa(int nb)
{
    char *str = malloc(sizeof(char) * 10);
    int i = 0;

    if (nb == 0) {
        str[0] = '0';
        str[1] = '\0';
        return str;
    }
    while (nb > 0) {
        str[i] = (nb % 10) + '0';
        nb /= 10;
        i++;
    }
    str[i] = '\0';
    return my_revstr(str);
}

static char *get_arg(t_server *server)
{
    char *str = strdup(server->ia_buffer);
    char **tab = split(str, " ");

    if (tab[1] == NULL) {
        return NULL;
    }
    return tab[1];
}

void broadcast(t_server* server, int client_fd)
{
    t_player* player = get_player_by_fd(server, client_fd);
    t_player* current_player = server->world.players;
    char* message = get_arg(server);
    char *tmp = strdup("");

    tmp = my_strcat(tmp, "message ");
    tmp = my_strcat(tmp, itoa(player->x));
    tmp = my_strcat(tmp, ":");
    tmp = my_strcat(tmp, itoa(player->y));
    tmp = my_strcat(tmp, " ");
    tmp = my_strcat(tmp, message);
    tmp = my_strcat(tmp, "\n");
    message = strdup(tmp);
    while (current_player != NULL) {
        if (current_player->id != player->id)
            send(current_player->fd, message, strlen(message), 0);
        current_player = current_player->next;
    }
}

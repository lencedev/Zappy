/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** incantation
*/

#include "../../includes/zappy.h"
#include <string.h>

char *my_itoa(int nb)
{
    int i = 0;
    int j = 0;
    char *str = malloc(sizeof(char) * 10);

    if (nb == 0) return ("0");
    while (nb > 0) {
        str[i] = nb % 10 + 48;
        nb = nb / 10;
        i++;
    }
    str[i] = '\0';
    i--;
    while (j < i) {
        str[j] = str[j] + str[i];
        str[i] = str[j] - str[i];
        str[j] = str[j] - str[i];
        j++;
        i--;
    }
    return (str);
}

void delete_waiting(t_server* s, t_player *p)
{
    t_team *t = get_team_by_name(s, p->team_name);
    t_player *tmp = t->players;

    while (tmp) {
        if (tmp->is_waiting == true) {
            tmp->is_waiting = false;
            return;
        }
        tmp = tmp->next;
    }
}

void incantation(t_server* server, int client_fd)
{
    t_player *p = get_player_by_fd(server, client_fd);
    char *buffer_send = malloc(sizeof(char) * 100);

    if (p == NULL) {
        send(client_fd, "ko\n", 3, 0);
        return;
    }
    p->is_freezed = true;
    p->level++;
    send(client_fd, "Elevation underway\n", 19, 0);
    sprintf(buffer_send, "Current level: %d\n", p->level);
    send(client_fd, buffer_send, strlen(buffer_send), 0);
}

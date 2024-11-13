/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** wait
*/

#include "../../includes/zappy.h"

void wait(t_server* s, int client_fd)
{
    t_player *p = get_player_by_fd(s, client_fd);
    t_player *tmp = s->world.players;

    while (tmp) {
        if (tmp->level == p->level && tmp->is_waiting == true) {
            send(client_fd, "ko\n", 3, 0);
            return;
        }
        tmp = tmp->next;
    }
    p->is_waiting = true;
    send(client_fd, "ok\n", 3, 0);
}

void is_waiting(t_server* s, int client_fd)
{
    t_player *p = get_player_by_fd(s, client_fd);
    t_player *tmp = s->world.players;

    if (p == NULL) {
        send(client_fd, "ko\n", 3, 0);
        return;
    }
    while (tmp) {
        if (tmp->level == p->level && tmp->is_waiting == true) {
            send(client_fd, "ok\n", 3, 0);
            return;
        }
        tmp = tmp->next;
    }
    send(client_fd, "ko\n", 3, 0);
}

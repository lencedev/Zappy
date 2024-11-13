/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** fork
*/

#include "../../includes/zappy.h"

void fork_ai(t_server* server, int client_fd)
{
    t_player *player = get_player_by_fd(server, client_fd);

    if (player == NULL) {
        send(client_fd, "ko\n", 3, 0);
        return;
    }
    add_egg(server, player);
    send(client_fd, "ok\n", 3, 0);
}

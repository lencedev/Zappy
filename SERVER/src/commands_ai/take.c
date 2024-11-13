/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** take
*/

#include "../../includes/zappy.h"

static char *get_arg(t_server *server)
{
    char *str = strdup(server->ia_buffer);
    char **tab = split(str, " ");

    if (tab[1] == NULL) {
        return NULL;
    }
    return tab[1];
}

int compare_3(t_server* s, t_player *player, char *ressource, int client_fd)
{
    if (strcmp(ressource, "phiras") == 0 &&
s->world.tiles[player->y][player->x].inventory.phiras > 0) {
        s->world.tiles[player->y][player->x].inventory.phiras -= 1;
        player->inventory.phiras += 1;
        send(client_fd, "ok\n", 3, 0);
        pgt_buffer(s, player, 4);
        return 1;
    }
    if (strcmp(ressource, "deraumere") == 0 &&
s->world.tiles[player->y][player->x].inventory.deraumere > 0) {
        s->world.tiles[player->y][player->x].inventory.deraumere -= 1;
        player->inventory.deraumere += 1;
        send(client_fd, "ok\n", 3, 0);
        pgt_buffer(s, player, 2);
        return 1;
    }
    return 0;
}

int compare_2(t_server* s, t_player *player, char *ressource, int client_fd)
{
    if (strcmp(ressource, "sibur") == 0 &&
s->world.tiles[player->y][player->x].inventory.sibur > 0) {
        s->world.tiles[player->y][player->x].inventory.sibur -= 1;
        player->inventory.sibur += 1;
        send(client_fd, "ok\n", 3, 0);
        pgt_buffer(s, player, 3);
        return 1;
    }
    if (strcmp(ressource, "mendiane") == 0 &&
s->world.tiles[player->y][player->x].inventory.mendiane > 0) {
        s->world.tiles[player->y][player->x].inventory.mendiane -= 1;
        player->inventory.mendiane += 1;
        send(client_fd, "ok\n", 3, 0);
        pgt_buffer(s, player, 5);
        return 1;
    }
    return 0;
}

int compare(t_server* s, t_player *player, char *ressource, int client_fd)
{
    if (strcmp(ressource, "food") == 0 &&
s->world.tiles[player->y][player->x].inventory.food > 0) {
        s->world.tiles[player->y][player->x].inventory.food -= 1;
        player->inventory.food += 1;
        send(client_fd, "ok\n", 3, 0);
        pgt_buffer(s, player, 0);
        return 1;
    }
    if (strcmp(ressource, "linemate") == 0 &&
s->world.tiles[player->y][player->x].inventory.linemate > 0) {
        s->world.tiles[player->y][player->x].inventory.linemate -= 1;
        player->inventory.linemate += 1;
        send(client_fd, "ok\n", 3, 0);
        pgt_buffer(s, player, 1);
        return 1;
    }
    return 0;
}

void take(t_server* s, int client_fd)
{
    t_player *player = get_player_by_fd(s, client_fd);
    char *ressource = get_arg(s);

    if (player == NULL || ressource == NULL) {
        send(client_fd, "ko\n", 3, 0);
        return;
    }
    if (compare(s, player, ressource, client_fd) == 1) return;
    if (compare_2(s, player, ressource, client_fd) == 1) return;
    if (compare_3(s, player, ressource, client_fd) == 1) return;
    if (strcmp(ressource, "thystame") == 0 &&
s->world.tiles[player->y][player->x].inventory.thystame > 0) {
        s->world.tiles[player->y][player->x].inventory.thystame -= 1;
        player->inventory.thystame += 1;
        send(client_fd, "ok\n", 3, 0);
        pgt_buffer(s, player, 6);
        return;
    }
    send(client_fd, "ko\n", 3, 0);
}

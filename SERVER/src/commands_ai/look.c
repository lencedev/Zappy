/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** look
*/

#include "../../includes/zappy.h"

t_tile *get_tile_direc(t_server *s, t_player *player, int i, int j)
{
    int x, y;
    switch (player->orientation) {
        case NORTH:
            y = player->y - i;
            x = player->x + j;
        case EAST:
            y = player->y + j;
            x = player->x + i;
        case SOUTH:
            y = player->y + i;
            x = player->x - j;
        case WEST:
            y = player->y - j;
            x = player->x - i;
    }
    if (y < 0) y = s->world.height + y;
    if (x < 0) x = s->world.width + x;
    return &s->world.tiles[y % s->world.height][x % s->world.width];
}

int count_players_on_tile(t_tile *tile)
{
    int count = 0;
    t_player *player = tile->players;
    while (player) {
        count++;
        player = player->next;
    }
    return count;
}

char *get_tile_content(t_tile *tile)
{
    char buff[BUFFER_SIZE];
    char *tmp = buff;
    int nb_players = count_players_on_tile(tile);
    int nb_eggs = tile->egg ? 1 : 0;
    for (int i = 0; i < nb_players; i++) {
        tmp += sprintf(tmp, "player ");
    }
    if (nb_eggs > 0) tmp += sprintf(tmp, "egg ");
    if (tile->inventory.food > 0) tmp += sprintf(tmp, "food ");
    if (tile->inventory.linemate > 0) tmp += sprintf(tmp, "linemate ");
    if (tile->inventory.deraumere > 0) tmp += sprintf(tmp, "deraumere ");
    if (tile->inventory.sibur > 0) tmp += sprintf(tmp, "sibur ");
    if (tile->inventory.mendiane > 0) tmp += sprintf(tmp, "mendiane ");
    if (tile->inventory.phiras > 0) tmp += sprintf(tmp, "phiras ");
    if (tile->inventory.thystame > 0) tmp += sprintf(tmp, "thystame ");
    if (tmp != buff) {
        tmp--;
        *tmp = '\0';
    }
    return strdup(buff);
}

void look(t_server* server, int client_fd)
{
    char buff[BUFFER_SIZE * 81];
    char *items = buff;
    t_player *player = get_player_by_fd(server, client_fd);
    if (!player) return;
    items += sprintf(items, "[");
    for (int i = 0; i <= player->level; i++) {
        for (int j = 0; j < (2 * i) + 1; j++) {
            t_tile *tile = get_tile_direc(server, player, i, j - i);
            char *tile_content = get_tile_content(tile);
            items += sprintf(items, "%s,", tile_content);
            free(tile_content);
        }
    }
    items--;
    *items = '\0';
    items += sprintf(items, "]\n");
    send(client_fd, buff, strlen(buff), 0);
}

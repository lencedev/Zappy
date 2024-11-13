/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** inventory
*/

#include "../../includes/zappy.h"

void inventory(t_server* server, int client_fd)
{
    t_player *player = get_player_by_fd(server, client_fd);
    char *inventory = malloc(sizeof(char) * 100);

    if (player == NULL) {
        send(client_fd, "ko\n", 3, 0);
        return;
    }
    sprintf(inventory, "[food %d, linemate %d, deraumere %d, sibur %d, \
mendiane %d, phiras %d, thystame %d]\n", player->inventory.food,
    player->inventory.linemate, player->inventory.deraumere,
    player->inventory.sibur, player->inventory.mendiane,
    player->inventory.phiras, player->inventory.thystame);
    send(client_fd, inventory, strlen(inventory), 0);
    free(inventory);
}

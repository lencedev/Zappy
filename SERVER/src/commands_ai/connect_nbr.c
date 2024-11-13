/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** connect_nbr
*/

#include "../../includes/zappy.h"

static char *my_int_to_str(int nb)
{
    char *str = malloc(sizeof(char) * 10);
    sprintf(str, "%d\n", nb);
    return str;
}

void connect_nbr(t_server* server, int client_fd)
{
    t_player *player = get_player_by_fd(server, client_fd);
    t_team *team = get_team_by_name(server, player->team_name);
    char *free_slots_str = my_int_to_str(team->nb_eggs);

    send(client_fd, free_slots_str, strlen(free_slots_str), 0);
    free(free_slots_str);
    return;
}

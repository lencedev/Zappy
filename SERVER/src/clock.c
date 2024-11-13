/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** clock
*/

#include "../includes/zappy.h"

void action_player_server_follow(t_server *server, t_player *tmp)
{
    t_actions *tmp_actions = tmp->actions;
    t_actions *next_actions = NULL;

    while (tmp_actions != NULL) {
        if (tmp_actions->exec_time == 0) {
            next_actions = tmp_actions->next;
            server->ia_buffer = strdup(tmp_actions->command);
            tmp_actions->func(server, tmp->fd);
            remove_actions(tmp, tmp_actions->id);
            tmp_actions = next_actions;
        } else {
            tmp_actions->exec_time -= 1;
            tmp_actions = tmp_actions->next;
        }
    }
}

static void action_player_server(t_server *server)
{
    if (server->unit_time % 20 == 0) {
        spawn_resources(server);
        printf("resources spawned\n");
    }
    t_player *tmp = server->world.players;
    while (tmp != NULL) {
        action_player_server_follow(server, tmp);
        tmp = tmp->next;
    }
    server->unit_time++;
}

void is_win(t_server *server, t_player *tmp_p)
{
    if (tmp_p->level == 6) {
        char *tmp = strdup("seg ");
        tmp = my_strcat(tmp, tmp_p->team_name);
        tmp = my_strcat(tmp, "\n");
        send(server->graphical_fd, tmp, strlen(tmp), 0);
        printf("Player %d won\n", tmp_p->id_client);
        close(tmp_p->fd);
        server->client_fds[tmp_p->id_client] = 0;
        remove_player_teams(server, tmp_p);
        remove_player_players(server, tmp_p);
        return;
    }
}

void action_clock_management(t_server *server)
{
    t_player *tmp_p = server->world.players;

    while (tmp_p != NULL) {
        if (tmp_p->inventory.food == 0 && tmp_p->id != -2) {
            pdi_buffer(server, tmp_p);
            printf("Player %d died\n", tmp_p->id_client);
            send(tmp_p->fd, "dead\n", 5, 0);
            close(tmp_p->fd);
            server->client_fds[tmp_p->id_client] = 0;
            remove_player_teams(server, tmp_p);
            remove_player_players(server, tmp_p);
            return;
        }
        if (server->unit_time % 126 == 0)
            tmp_p->inventory.food -= 1;
        is_win(server, tmp_p);
        tmp_p = tmp_p->next;
    }
    action_player_server(server);
}

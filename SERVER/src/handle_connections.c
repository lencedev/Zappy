/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** handle_connections
*/

#include "../includes/zappy.h"

int new_connections(t_server *server, int *max_fd)
{
    int client_fd = accept(server->socket_fd,
(struct sockaddr*)&(server->client_addr),&(server->addrlen));

    if (client_fd < 0) {
        perror("accept");
        exit(84);
    }
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->client_fds[i] == -1) {
            server->client_fds[i] = client_fd;
            break;
        }
    }
    if (client_fd > (*max_fd)) {
        (*max_fd) = client_fd;
    }
    return client_fd;
}

void init_player(t_server *server, int client_fd)
{
    t_player *player = malloc(sizeof(t_player));

    player->id = -1;
    player->actions = NULL;
    player->is_waiting = false;
    player->fd = client_fd;
    player->level = 1;
    player->x = 0;
    player->y = 0;
    player->inventory.food = 10;
    player->inventory.linemate = 0;
    player->inventory.deraumere = 0;
    player->inventory.sibur = 0;
    player->inventory.mendiane = 0;
    player->inventory.phiras = 0;
    player->inventory.thystame = 0;
    player->orientation = rand() % 4 + 1;
    player->is_freezed = false;
    player->next = NULL;
    add_player_players(server, player);
}

int handle_incomming_connections(t_server *server, int *max_fd)
{
    if (FD_ISSET(server->socket_fd, &(server->readfds))) {
        int client_fd = new_connections(server, max_fd);
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(server->client_addr).sin_addr,
client_ip, INET_ADDRSTRLEN);
        printf("New client connected: %s:%d\n", client_ip,
ntohs(server->client_addr.sin_port));
        init_player(server, client_fd);
        send(client_fd, "WELCOME\n", 8, 0);
    }
    return 0;
}

int select_reset(t_server *server)
{
    FD_ZERO(&(server->readfds));
    FD_SET(server->socket_fd, &(server->readfds));
    for (int i = 0; i < MAX_CLIENTS; i++) {
        int client_fd = server->client_fds[i];
        if (client_fd != 0 && client_fd != -1) {
            FD_SET(client_fd, &(server->readfds));
        }
    }
    return 0;
}

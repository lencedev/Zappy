/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** select
*/

#include "../includes/zappy.h"

void handle_client_disconnection(t_server *server, int i)
{
    int client_fd = server->client_fds[i];
    printf("Client disconnected\n");
    close(client_fd);
    server->client_fds[i] = 0;
    t_player *player = get_player_by_fd(server, client_fd);
    if (player != NULL) {
        remove_player_teams(server, player);
        remove_player_players(server, player);
    }
}

void handle_read_buffer(t_server *server, int i)
{
    int client_fd = server->client_fds[i];
    for (int i = 0; server->buffer[i]; i++) {
        if (server->buffer[i] == '\n') {
            server->tmp_buffer = my_strcat(server->tmp_buffer, server->buffer);
            server->buffer = strdup(server->tmp_buffer);
            // printf("\n---\nReceived: %s---\n", server->buffer);
            handle_command(server, client_fd);
            free(server->buffer);
            server->buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
            clear_buffer(server);
            server->tmp_buffer = strdup("");
            return;
        }
    }
    send(client_fd, "ko\n", 2, 0);
    server->tmp_buffer = my_strcat(server->tmp_buffer, server->buffer);
    free(server->buffer);
    server->buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
}

int handle_clients_data(t_server *server, int i)
{
    int client_fd = server->client_fds[i];
    if (FD_ISSET(client_fd, &(server->readfds))) {
        int n = read(client_fd, server->buffer, BUFFER_SIZE - 1);
        if (n < 0)
            exit(84);
        if (n == 0) {
            handle_client_disconnection(server, i);
            return 0;
        }
        handle_read_buffer(server, i);
    }
    return 0;
}

int handle_activity(t_server *server, int *max_fd)
{
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    server->activity = select((*max_fd) + 1,
&(server->readfds), NULL, NULL, &timeout);

    if (server->activity < 0) {
        printf("Select error\n");
        return 0;
    }
    return 0;
}

int handle_select(t_server *server)
{
    int max_fd = 0;
    struct timeval now, last_action_time, d;

    setup_server(server);
    max_fd = server->socket_fd;
    printf("Server started on port %d\n", server->port);
    gettimeofday(&last_action_time, NULL);
    while (1) {
        handle_activity(server, &max_fd);
        handle_incomming_connections(server, &max_fd);
        for (int i = 0; i < MAX_CLIENTS; i++) handle_clients_data(server, i);
        gettimeofday(&now, NULL);
        timersub(&now, &last_action_time, &d);
        if (d.tv_sec > 0 || d.tv_usec >= 1000000 / server->world.frequency) {
            action_clock_management(server);
            last_action_time = now;
        }
        select_reset(server);
    }
    return 0;
}

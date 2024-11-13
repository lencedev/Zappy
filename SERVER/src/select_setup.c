/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** select_setup
*/

#include "../includes/zappy.h"

void allocate_tiles(t_server *server)
{
    server->world.tiles = malloc(sizeof(t_tile *) * server->world.height);
    for (int i = 0; i < server->world.height; i++) {
        server->world.tiles[i] = malloc(sizeof(t_tile) * server->world.width);
    }
}

void setup_tiles(t_server *server)
{
    for (int i = 0; i < server->world.height; i++) {
        for (int j = 0; j < server->world.width; j++) {
            server->world.tiles[i][j].x = j;
            server->world.tiles[i][j].y = i;
            server->world.tiles[i][j].inventory.food = 0;
            server->world.tiles[i][j].inventory.linemate = 0;
            server->world.tiles[i][j].inventory.deraumere = 0;
            server->world.tiles[i][j].inventory.sibur = 0;
            server->world.tiles[i][j].inventory.mendiane = 0;
            server->world.tiles[i][j].inventory.phiras = 0;
            server->world.tiles[i][j].inventory.thystame = 0;
            server->world.tiles[i][j].players = NULL;
            server->world.tiles[i][j].egg = NULL;
        }
    }
}

void put_one_egg_each_team_random_tile(t_server* server)
{
    t_team* current_team = server->world.teams;
    int x;
    int y;

    while (current_team != NULL) {
        x = rand() % server->world.width;
        y = rand() % server->world.height;
        server->world.tiles[y][x].egg = malloc(sizeof(t_egg));
        server->world.tiles[y][x].egg->x = x;
        server->world.tiles[y][x].egg->y = y;
        server->world.tiles[y][x].egg->team_name = strdup(current_team->name);
        server->world.tiles[y][x].egg->next = NULL;
        current_team->nb_eggs = 1;
        current_team->eggs = server->world.tiles[y][x].egg;
        current_team = current_team->next;
    }
}

void setup_values(t_server *server)
{
    server->addrlen = sizeof(server->client_addr);
    server->activity = 0;
    allocate_tiles(server);
    setup_tiles(server);
    put_one_egg_each_team_random_tile(server);
    for (int i = 0; i < MAX_CLIENTS; i++)
        server->client_fds[i] = -1;
    server->tmp_buffer = strdup("");
    server->buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    for (int i = 0; i < BUFFER_SIZE + 1; i++)
        server->buffer[i] = '\0';
    server->unit_time = 0;
    server->graphical_fd = -1;
}

void setup_server(t_server *server)
{
    setup_values(server);
    if ((server->socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(84);
    }
    memset(&(server->server_addr), 0, sizeof(server->server_addr));
    server->server_addr.sin_family = AF_INET;
    server->server_addr.sin_addr.s_addr = INADDR_ANY;
    server->server_addr.sin_port = htons(server->port);
    if (bind(server->socket_fd, (struct sockaddr*)&server->server_addr,
sizeof(server->server_addr)) < 0)
        exit(84);
    if (listen(server->socket_fd, 11) < 0)
        exit(84);
    FD_ZERO(&(server->readfds));
    FD_SET(server->socket_fd, &(server->readfds));
}

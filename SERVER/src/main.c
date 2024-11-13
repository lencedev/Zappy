/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** main
*/

#include "../includes/zappy.h"
#include <stdio.h>
#include <unistd.h>

t_server* init_server(void)
{
    t_server* server = malloc(sizeof(t_server));
    server->world.width = 10;
    server->world.height = 10;
    server->world.frequency = 0;
    server->world.eggs = NULL;
    server->world.tiles = NULL;
    server->world.teams = NULL;
    server->world.players = NULL;
    server->world.nb_global_clients = 2;
    return server;
}

void parse_single_arg(t_server* server, int opt)
{
    switch (opt) {
        case 'p':
            server->port = atoi(optarg);
            break;
        case 'x':
            server->world.width = atoi(optarg);
            break;
        case 'y':
            server->world.height = atoi(optarg);
            break;
        case 'c':
            set_max_members(server, atoi(optarg));
            break;
        case 'f':
            server->world.frequency = atoi(optarg);
            break;
        default:
            fprintf(stderr, "Invalid option.\n");
            exit(EXIT_FAILURE);
    }
}

t_server* parse_args(int argc, char* argv[])
{
    int opt;
    bool is_parsing_teams = false;
    t_server* server = init_server();

    for (int i = 0; i < argc; i++) {
        if (is_parsing_teams && argv[i][0] != '-') {
            parse_teams(server, argv, &i);
            is_parsing_teams = false;
        }
        if (argv[i][0] == '-') {
            opt = getopt(argc, argv, "p:x:y:c:f:n");
            opt == 'n' ? is_parsing_teams = true : \
parse_single_arg(server, opt);
        }
    }
    return server;
}

int validate_server(t_server* server)
{
    if (server->port <= 0 || server->world.width <= 0 ||
server->world.height <= 0 || server->world.frequency <= 0) {
        fprintf(stderr, "Invalid parameters. Please check \
your command line arguments.\n");
        printf("USAGE: ./zappy_server -p port -x width -y \
height -n name1 name2 ... -c clientsNb -f freq\n");
        return 0;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    t_server* server = parse_args(argc, argv);

    if (!validate_server(server)) {
        exit(EXIT_FAILURE);
    }
    printf("Server port: %d\n", server->port);
    printf("World width: %d\n", server->world.width);
    printf("World height: %d\n", server->world.height);
    printf("World frequency: %d\n", server->world.frequency);
    printf("Teams:\n");
    add_team(server, "GRAPHIC");
    t_team* current_team = server->world.teams;
    while (current_team != NULL) {
        printf("\t%s\n", current_team->name);
        current_team = current_team->next;
    }
    handle_select(server);
    return 0;
}

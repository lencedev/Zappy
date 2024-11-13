/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** commands
*/

#include "../includes/zappy.h"

static void send_data(t_server *server, int client_fd, t_team* current_team,
t_player *player)
{
    int avaiable_p = current_team->max_members - current_team->num_members;
    char *x_y = malloc(sizeof(char) * 15);
    sprintf(x_y, "%d\n%d %d\n", avaiable_p,
server->world.width, server->world.height);
    send(client_fd, x_y, strlen(x_y), 0);
    pnw_buffer(server, player);
}

int graphic_connection(t_server *server, int client_fd, char *command)
{
    t_player *player = get_player_by_fd(server, client_fd);
    char *command_buffer = strdup("");

    if (strcmp(command, "GRAPHIC") == 0) {
        printf("Graphic Connection\n");
        player->team_name = strdup("GRAPHIC");
        player->id = -2;
        player->id_client = -1;
        command_buffer = my_strcat(command_buffer, msz_buffer(server));
        command_buffer = my_strcat(command_buffer, tna_buffer(server));
        command_buffer = my_strcat(command_buffer, mct_buffer(server));
        command_buffer = my_strcat(command_buffer, sgt_buffer(server));
        server->graphical_fd = client_fd;
        send(client_fd, command_buffer, strlen(command_buffer), 0);
        return 1;
    }
    return 0;
}

int new_player(t_server *server, int client_fd, char *command, t_player *player)
{
    if (graphic_connection(server, client_fd, command) == 1) return 1;
    if (player->id != -1) return 0;
    t_team* current_team = server->world.teams;
    while (current_team != NULL) {
        if (strcmp(current_team->name, command) == 0 && current_team->nb_eggs \
> 0 && current_team->num_members < current_team->max_members) {
            player->team_name = strdup(command);
            player->id = current_team->num_members;
            player->id_client = server->world.nb_global_clients;
            current_team->num_members++;
            add_player_teams(&current_team->players, player);
            add_player_at_egg(server, player);
            send_data(server, client_fd, current_team, player);
            server->world.nb_global_clients++;
            return 1;
        }
        current_team = current_team->next;
    }
    send(client_fd, "ko\n", 3, 0);
    return 1;
}

int execute_command(t_server *server, int client_fd, char *command_exec)
{
    for (int i = 0; COMMANDS_GRAPH[i].command != NULL; i++) {
        if (strcmp(command_exec, COMMANDS_GRAPH[i].command) == 0) {
            COMMANDS_GRAPH[i].func(server, client_fd);
            return 1;
        }
    }
    for (int i = 0; COMMANDS_AI[i].command != NULL; i++) {
        if (strcmp(command_exec, COMMANDS_AI[i].command) == 0)
            return execute_command2(server, client_fd, command_exec, i);
    }
    return 0;
}

int handle_command(t_server *server, int client_fd)
{
    char *command = strtok(server->buffer, "\n");
    t_player *player = get_player_by_fd(server, client_fd);

    for (int i = 0; i < strlen(command); i++)
        if (command[i] == '\r' || command[i] == '\n')
            command[i] = '\0';
    if (new_player(server, client_fd, command, player) == 1) return 0;
    char *command_exec = split(strdup(server->buffer), " ")[0];
    if (player == NULL) return 0;
    if (execute_command(server, client_fd, command_exec) == 1) return 0;
    send(client_fd, "suc\n", 4, 0);
    return 0;
}

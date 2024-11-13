/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** zappy
*/

#ifndef ZAPPY_H_
    #define ZAPPY_H_

    #define MAX_CLIENTS 30
    #define BUFFER_SIZE 1024

    #include <stdint.h>
    #include <stdbool.h>
    #include <sys/types.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <getopt.h>
    #include <string.h>
    #include <unistd.h>
    #include <time.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/select.h>
    #include <sys/time.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "network.h"
    #include "command.h"
    #include "list.h"

    enum orientation {
        NORTH = 1,
        EAST = 2,
        SOUTH = 3,
        WEST = 4
    };

    typedef struct s_inventory {
        int food;
        int linemate;
        int deraumere;
        int sibur;
        int mendiane;
        int phiras;
        int thystame;
    } t_inventory;

    typedef struct s_actions {
        int id;
        char *command;
        void (*func)(t_server *, int);
        int exec_time;
        struct s_actions *next;
    } t_actions;

    typedef struct s_player {
        int id;
        int id_client;
        char *team_name;
        int life_unit;
        struct s_actions *actions;
        int fd;
        int x;
        int y;
        int level;
        enum orientation orientation;
        t_inventory inventory;
        bool is_alive;
        bool is_freezed;
        bool is_waiting;
        time_t death_time;
        struct s_player* next;
    } t_player;

    typedef struct s_egg {
        int x;
        int y;
        char* team_name;
        struct s_egg* next;
    } t_egg;

    typedef struct s_team {
        char* name;
        int max_members;
        int num_members;
        int nb_eggs;
        t_player* players;
        t_egg* eggs;
        struct s_team* next;
    } t_team;

    typedef struct s_tile {
        int x;
        int y;
        t_inventory inventory;
        t_player* players;
        t_egg *egg;
    } t_tile;

    typedef struct s_world {
        int width;
        int height;
        t_tile** tiles;
        t_team* teams;
        t_player* players;
        t_egg* eggs;
        int frequency;
        int nb_global_clients;
    } t_world;

    typedef struct s_server {
        int unit_time;
        int socket_fd;
        int graphical_fd;
        uint16_t port;
        int activity;
        char *buffer;
        char *ia_buffer;
        char *tmp_buffer;
        int client_fds[MAX_CLIENTS];
        struct sockaddr_in server_addr;
        struct sockaddr_in client_addr;
        fd_set readfds;
        socklen_t addrlen;
        t_world world;
    } t_server;

    typedef struct {
        int i;
        int j;
    } resource_distribution;

    void add_team(t_server* server, char* team_name);
    void set_max_members(t_server* server, int max_members);
    void parse_teams(t_server* server, char* argv[], int* index);
    t_team *get_team_by_name(t_server *server, char *team_name);
    void clear_buffer(t_server *server);
    char **split(char *str, char *delim);
    void print_teams(t_team *teams);
    void action_clock_management(t_server *server);
    char *get_ressource_name(int ressource);
    char *my_itoa(int nb);
    void spawn_resources(t_server *server);
    char *get_ressource_name(int ressource);
    char *my_strcat(const char *s1, const char *s2);

    void add_actions(t_player *player, char *command, int exec_time,
    void (*func)(t_server *, int));
    void remove_actions(t_player *player, int id);

    void add_egg(t_server *server, t_player *player);
    void remove_egg(t_server *server, t_egg *egg);
    t_egg *get_egg_by_team_name(t_server *server, char *team_name);
    void add_player_at_egg(t_server *server, t_player *player);

    void send_data_graphic(t_server *server, char *data);
    void pnw_buffer(t_server *server, t_player *player);
    void pdi_buffer(t_server *server, t_player *player);
    void pdr_buffer(t_server *server, t_player *player, int ressource);
    void pgt_buffer(t_server *server, t_player *player, int ressource);
    int execute_command2(t_server *server, int client_fd,
        char *command_exec, int i);
    void calculate_resources(t_server *server, int *total_resources);

#endif /* !ZAPPY_H_ */

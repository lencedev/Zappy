/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** command
*/

#ifndef COMMAND_H_
    #define COMMAND_H_

    typedef struct s_command {
        char *command;
        void (*func)(t_server *, int);
        int exec_time;
    } t_command;

    void forward(t_server* server, int client_fd);
    void right(t_server* server, int client_fd);
    void left(t_server* server, int client_fd);
    void look(t_server* server, int client_fd); // !
    void inventory(t_server* server, int client_fd);
    void broadcast(t_server* server, int client_fd); // !
    void connect_nbr(t_server* server, int client_fd); // !
    void fork_ai(t_server* server, int client_fd); // !
    void eject(t_server* server, int client_fd); // !
    void take(t_server* server, int client_fd); // !
    void wait(t_server* s, int client_fd);
    void is_waiting(t_server* s, int client_fd);
    void set(t_server* server, int client_fd); // !
    void incantation(t_server* server, int client_fd); // !

    static const t_command COMMANDS_AI[] = {
        {"Forward", &forward, 7},
        {"Right", &right, 7},
        {"Left", &left, 7},
        {"Look", &look, 7},
        {"Inventory", &inventory, 1},
        {"Broadcast", &broadcast, 7},
        {"Connect_nbr", &connect_nbr, 0},
        {"Fork", &fork_ai, 42},
        {"Eject", &eject, 7},
        {"Take", &take, 7},
        {"Waiting", &wait, 0},
        {"is_waiting", &is_waiting, 0},
        {"Set", &set, 7},
        {"Incantation", &incantation, 300},
        {NULL, NULL}
    };

    void msz(t_server* server, int client_fd);
    void bct(t_server* server, int client_fd);
    void mct(t_server* server, int client_fd);
    void tna(t_server* server, int client_fd);
    void ppo(t_server* server, int client_fd);
    void plv(t_server* server, int client_fd);
    void pin(t_server* server, int client_fd);
    void sgt(t_server* server, int client_fd);
    void sst(t_server* server, int client_fd);
    char *tna_buffer(t_server *server);
    char *sgt_buffer(t_server *server);
    char *mct_buffer(t_server *server);
    char *msz_buffer(t_server *server);


    void print_map_in_x_y(t_server *server, int client_fd);

    static const t_command COMMANDS_GRAPH[] = {
        {"msz", &msz},
        {"bct", &bct},
        {"mct", &mct},
        {"tna", &tna},
        {"ppo", &ppo},
        {"plv", &plv},
        {"pin", &pin},
        {"sgt", &sgt},
        {"sst", &sst},
        {"status", &print_map_in_x_y},
        {NULL, NULL}
    };

    int handle_command(t_server *server, int client_fd);

#endif /* !COMMAND_H_ */

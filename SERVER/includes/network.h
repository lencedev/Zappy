/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** network
*/

typedef struct s_server t_server;

#ifndef NETWORK_H_
    #define NETWORK_H_

    int handle_select(t_server *server);
    int handle_incomming_connections(t_server *server, int *max_fd);
    int select_reset(t_server *server);
    char *my_strcat(const char *s1, const char *s2);
    void setup_server(t_server *server);
    void setup_values(t_server *server);
    void setup_tiles(t_server *server);
    void allocate_tiles(t_server *server);
    void handle_read_buffer(t_server *server, int i);

#endif /* !NETWORK_H_ */

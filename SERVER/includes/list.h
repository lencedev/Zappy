/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** list
*/

typedef struct s_player t_player;

#ifndef LIST_H_
    #define LIST_H_

    t_player *get_player_by_id(t_server *server, int player_id);
    t_player *get_player_by_fd(t_server *server, int fd);
    void add_player_teams(t_player **tmp, t_player *player);
    void add_player_players(t_server *server, t_player *player);
    void remove_player_players(t_server *server, t_player *player);
    void remove_player_teams(t_server *server, t_player *player);

#endif /* !LIST_H_ */

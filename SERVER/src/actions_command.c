/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** actions_command
*/

#include "../includes/zappy.h"

void add_actions(t_player *player, char *command, int exec_time,
void (*func)(t_server *, int))
{
    t_actions *new_action = malloc(sizeof(t_actions));
    t_actions *temp = player->actions;

    new_action->id = rand() % 100 + 1;
    new_action->command = strdup(command);
    new_action->func = func;
    new_action->exec_time = exec_time;
    new_action->next = NULL;
    if (player->actions == NULL) {
        player->actions = new_action;
        return;
    }
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new_action;
}

void remove_actions(t_player *player, int id)
{
    t_actions *temp = player->actions;
    t_actions *prev = NULL;

    if (temp != NULL && temp->id == id) {
        player->actions = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
    free(temp);
}

/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** ressources
*/

#include "../includes/zappy.h"

static void distribute_kth_resource(t_server *server, int *total_resources,
resource_distribution resources, int k)
{
    int grid_size = server->world.width * server->world.height;

    if (rand() % grid_size >= total_resources[k])
        return;

    ((int*)(&(server->world.tiles[resources.i][resources.j].inventory)))[k]++;
    total_resources[k]--;
}

static void distribute_resources_on_tile(t_server *server, int *total_resources,
int i, int j)
{
    resource_distribution resources;
    resources.i = i;
    resources.j = j;
    for (int k = 0; k < 7; k++)
        if (total_resources[k] > 0)
            distribute_kth_resource(server, total_resources, resources, k);
}

void distribute_resources(t_server *server, int *total_resources)
{
    srand(time(0));

    for (int i = 0; i < server->world.width; i++)
        for (int j = 0; j < server->world.height; j++)
            distribute_resources_on_tile(server, total_resources, i, j);
}

int stop_ressource(t_server *server)
{
    int total_food = 0;
    for (int i = 0; i < server->world.width; i++)
        for (int j = 0; j < server->world.height; j++)
            total_food += server->world.tiles[i][j].inventory.food;
    if (total_food > server->world.width * server->world.height * 0.5)
        return 1;
    return 0;
}

void spawn_resources(t_server *server)
{
    int total_resources[7];
    if (stop_ressource(server) == 1) return;
    calculate_resources(server, total_resources);
    distribute_resources(server, total_resources);
}

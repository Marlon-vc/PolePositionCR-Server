#ifndef POLEPOSITIONCR_SERVER_SERVER_H
#define POLEPOSITIONCR_SERVER_SERVER_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include "../json/cJSON.h"
#include "../structures/car_linked_list.h"
#include "../structures/player_linked_list.h"

struct car head_s;
struct car red_car;
struct car blue_car;
struct car purple_car;
struct car white_car;
node_t * head;

node_p_t * playerList;

void loadCarList();

void loadPlayerList();

void set_new_player(cJSON *data);

void add_player(cJSON *pos, cJSON *playerX, cJSON *carColor, cJSON *lives);

void remove_player(cJSON *carColor);

void update_player(cJSON *pos, cJSON *playerX, cJSON *carColor, cJSON *lives);

cJSON *get_available_cars();

cJSON *get_players_list();

void set_available_cars(cJSON *carColor);

int init_config();

cJSON *create_track();

int start();

void prueba();

int server_running;

#endif //POLEPOSITIONCR_SERVER_SERVER_H

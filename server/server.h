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
#include "../structures/live_linked_list.h"
#include "../structures/hole_linked_list.h"
#include "../structures/turbo_linked_list.h"

struct car head_s;
struct car red_car;
struct car blue_car;
struct car purple_car;
struct car white_car;
node_t * carsList;
node_p_t * playerList;
node_l_t * livesList;
node_h_t * holeList;
node_tu_t * turboList;



void load_car_list();

void load_player_list();

void load_lives_list();

void load_hole_list();

void load_turbo_list();

void add_player(cJSON *pos, cJSON *playerX, cJSON *carColor, cJSON *lives, cJSON *points);

void remove_player(cJSON *carColor);

void update_player(cJSON *pos, cJSON *playerX, cJSON *carColor, cJSON *lives, cJSON *points);

void add_hole(cJSON *id, cJSON *posX, cJSON *posY);

void add_live(cJSON *id, cJSON *posX, cJSON *posY);

void remove_live(cJSON *id, cJSON *car_color);

void add_turbo(cJSON *id, cJSON *posX, cJSON *posY);

void remove_turbo(cJSON *id, cJSON *car_color);

cJSON *get_available_cars();

cJSON *get_players_list();

void set_available_cars(cJSON *carColor);

int init_config();

cJSON *create_track();

void set_new_player(cJSON *data);

int start();

void prueba();

int server_running;

#endif //POLEPOSITIONCR_SERVER_SERVER_H

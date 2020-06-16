//
// Created by pvill on 15/6/2020.
//

#ifndef POLEPOSITIONCR_SERVER_PLAYER_LINKED_LIST_H
#define POLEPOSITIONCR_SERVER_PLAYER_LINKED_LIST_H

#include <stdlib.h>

#include <stdio.h>
#include <string.h>

struct player {
    int id;
    int pos;
    int playerX;
    int lives;
    char car_color[80];
};

typedef struct node_p {
    struct player value;
    struct node_p * next;
}node_p_t;

void insert_end_p(node_p_t * head, struct player value); // agrega un elemento al final

void insert_p(node_p_t * head, struct player value); // agrega al inicio

int remove_first_p(node_p_t * head);

int remove_last_p(node_p_t * head);

int remove_at_p(node_p_t * head, int n);

void print_list_p(node_p_t * head);

#endif //POLEPOSITIONCR_SERVER_PLAYER_LINKED_LIST_H

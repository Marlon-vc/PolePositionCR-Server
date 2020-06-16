//
// Created by pvill on 16/6/2020.
//

#ifndef POLEPOSITIONCR_SERVER_LIVE_LINKED_LIST_H
#define POLEPOSITIONCR_SERVER_LIVE_LINKED_LIST_H

#include <stdlib.h>

#include <stdio.h>
#include <string.h>

struct live {
    int id;
    int posX;
    int posY;
};

typedef struct node_l {
    struct live value;
    struct node_l * next;
}node_l_t;

void insert_end_l(node_l_t * head, struct live value);

int remove_first_l(node_l_t * head);

int remove_at_l(node_l_t * head, int n);

void modify_live(node_l_t * head, int posX, int posY, int id);

int find_live_pos(node_l_t * head, int id);

void print_list_l(node_l_t * head);

#endif //POLEPOSITIONCR_SERVER_LIVE_LINKED_LIST_H

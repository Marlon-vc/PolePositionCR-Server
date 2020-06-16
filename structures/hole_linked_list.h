//
// Created by pvill on 16/6/2020.
//

#ifndef POLEPOSITIONCR_SERVER_HOLE_LINKED_LIST_H
#define POLEPOSITIONCR_SERVER_HOLE_LINKED_LIST_H

#include <stdlib.h>

#include <stdio.h>
#include <string.h>

struct hole {
    int id;
    int posX;
    int posY;
};

typedef struct node_h {
    struct hole value;
    struct node_h * next;
}node_h_t;

void insert_end_h(node_h_t * head, struct hole value);

int remove_first_h(node_h_t * head);

int remove_at_h(node_h_t * head, int n);

void modify_hole(node_h_t * head, int posX, int posY, int id);

int find_hole_pos(node_h_t * head, int id);

void print_list_h(node_h_t * head);

#endif //POLEPOSITIONCR_SERVER_HOLE_LINKED_LIST_H

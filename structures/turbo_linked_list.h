//
// Created by pvill on 16/6/2020.
//

#ifndef POLEPOSITIONCR_SERVER_TURBO_LINKED_LIST_H
#define POLEPOSITIONCR_SERVER_TURBO_LINKED_LIST_H

#include <stdlib.h>

#include <stdio.h>
#include <string.h>

struct turbo {
    int id;
    int posX;
    int posY;
};

typedef struct node_tu {
    struct turbo value;
    struct node_tu * next;
}node_tu_t;

void insert_end_t(node_tu_t * head, struct turbo value);

int remove_first_t(node_tu_t * head);

int remove_at_t(node_tu_t * head, int n);

void modify_turbo(node_tu_t * head, int posX, int posY, int id);

int find_turbo_pos(node_tu_t * head, int id);

void print_list_t(node_tu_t * head);

#endif //POLEPOSITIONCR_SERVER_TURBO_LINKED_LIST_H

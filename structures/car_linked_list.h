//
// Created by pvill on 15/6/2020.
//

#ifndef POLEPOSITIONCR_SERVER_CAR_LINKED_LIST_H
#define POLEPOSITIONCR_SERVER_CAR_LINKED_LIST_H

#include <stdlib.h>

#include <stdio.h>
#include <string.h>

struct car {
    char color[80];
    int available;
};

typedef struct node {
    struct car valor ;
    struct node * next;
} node_t;


void insert_end(node_t * head, struct car valor); // agrega un elemento al final

void insert(node_t * head, struct car valor); // agrega al inicio

char * remove_first(node_t * head);

char * remove_last(node_t * head);

char * remove_at(node_t * head, int n);

void print_list(node_t * head);

void modify_availability(node_t * head, char * carColor, int newAvailability);

#endif //POLEPOSITIONCR_SERVER_CAR_LINKED_LIST_H
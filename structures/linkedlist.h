//
// Created by pvill on 15/6/2020.
//

#ifndef POLEPOSITIONCR_SERVER_LINKEDLIST_H
#define POLEPOSITIONCR_SERVER_LINKEDLIST_H

#include <stdlib.h>

#include <stdio.h>
#include <string.h>

struct value {
    char color[80];
    int available;
};

typedef struct node {
    struct value valor ;
    struct node * next;
} node_t;


void insert_end(node_t * head, struct value valor); // agrega un elemento al final

void insert(node_t * head, struct value valor); // agrega al inicio

char * remove_first(node_t * head);

char * remove_last(node_t * head);

char * remove_at(node_t * head, int n);

void print_list(node_t * head);

void modify_availability(node_t * head, char * carColor, int newAvailability);

#endif //POLEPOSITIONCR_SERVER_LINKEDLIST_H

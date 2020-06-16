//
// Created by pvill on 15/6/2020.
//

#include "linkedlist.h"


void insert_end(node_t * head, struct car valor) {
    node_t *tmp = head;

    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = (node_t *) malloc(sizeof(node_t));
    tmp->next->valor = valor;
    tmp->next->next = NULL;
}

void insert(node_t * head, struct car valor) {
    node_t * new_node;
    new_node = (node_t *) malloc(sizeof(node_t));

    new_node->valor = valor;
    new_node->next = head->next;
    head->next = new_node;
}

char * remove_first(node_t * head) {
    char retVal[80] = "";
    node_t * nextNode = NULL;

    if (head == NULL)
        return "";

    nextNode = head->next->next;
    strcpy(retVal, head->next->valor.color);
    free(head->next);
    head->next = nextNode;

    return retVal;
}

char * remove_last(node_t * head) {
    char retVal[80] = "";
    node_t * tmp = head;
    while (tmp->next->next != NULL) {
        tmp = tmp->next;
    }
    strcpy(retVal, tmp->next->valor.color);
    free(tmp->next);
    tmp->next = NULL;

    return retVal;
}

char * remove_at(node_t * head, int n) {
    int i = 0;
    char retVal[80] = "";
    node_t * current = head;
    node_t * tmp = NULL;

    if (n == 0)
        return remove_first(head);
    current = current->next;
    for (i = 0; i < n-1; i++) {
        if (current->next == NULL)
            return "";
        current = current->next;
    }
    tmp = current->next;
    strcpy(retVal, tmp->valor.color);
    current->next = tmp->next;
    free(tmp);

    return retVal;
}

void modify_availability(node_t * head, char * carColor, int newAvailability) {
    node_t * tmp = head;
    while (tmp != NULL) {
        char *color = tmp->valor.color;
        if (strcmp(color, carColor) == 0) {
            tmp->valor.available = newAvailability;
            return;
        }
        tmp = tmp->next;
    }
}

void print_list(node_t * head) {
    node_t * tmp = head;
    tmp= tmp->next;
    int i = 0;
    if (tmp == NULL)
        printf("[ ]");
    while (tmp != NULL) {
        if (i == 0){
            printf("[");
        }
        if (tmp->next == NULL) {
            printf("%s %i]", tmp->valor.color, tmp->valor.available);
        } else {
            printf("%s %i, ", tmp->valor.color, tmp->valor.available);
        }
        tmp = tmp->next;
        i++;
    }
}
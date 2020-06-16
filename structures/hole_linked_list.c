//
// Created by pvill on 16/6/2020.
//

#include "hole_linked_list.h"

void insert_end_h(node_h_t * head, struct hole value) {
    node_h_t * tmp = head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = (node_h_t *) malloc(sizeof(node_h_t));
    tmp->next->value = value;
    tmp->next->next = NULL;
}

int remove_first_h(node_h_t * head) {
    int retVal;
    node_h_t * nextNode = NULL;

    if (head == NULL)
        return -1;

    nextNode = head->next->next;
    retVal = head->next->value.id;
    free(head->next);
    head->next = nextNode;

    return retVal;
}

int remove_at_h(node_h_t * head, int n) {
    int i = 0;
    int retVal;
    node_h_t * current = head;
    node_h_t * tmp = NULL;

    if (n == 0)
        return remove_first_h(head);
//    current = current->next;
    for (i = 0; i < n-1; i++) {
        if (current->next == NULL)
            return -1;
        current = current->next;
    }
    tmp = current->next;
    retVal = head->next->value.id;
    current->next = tmp->next;
    free(tmp);

    return retVal;
}

void modify_hole(node_h_t * head, int posX, int posY, int id) {
    node_h_t * tmp = head;
    while (tmp != NULL) {
        if (tmp->value.id == id) {
            tmp->value.posX = posX;
            tmp->value.posY = posY;
            break;
        }
        tmp = tmp->next;
    }
}

int find_hole_pos(node_h_t * head, int id) {
    int pos = 0;
    node_h_t *tmp = head;
    while (tmp != NULL) {
        if (tmp->value.id == id) {
            return pos;
        }
        pos++;
        tmp = tmp->next;
    }
    return -1;
}

void print_list_h(node_h_t * head) {
    node_h_t * tmp = head;
    tmp= tmp->next;
    int i = 0;
    if (tmp == NULL)
        printf("[ ]");
    while (tmp != NULL) {
        if (i == 0){
            printf("[");
        }
        if (tmp->next == NULL) {
            printf("id:%i posX:%i posY:%i]", tmp->value.id, tmp->value.posX, tmp->value.posY);
        } else {
            printf("id:%i posX:%i posY:%i, ", tmp->value.id, tmp->value.posX, tmp->value.posY);
        }
        tmp = tmp->next;
        i++;
    }
}
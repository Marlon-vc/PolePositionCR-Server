//
// Created by pvill on 16/6/2020.
//

#include "hole_linked_list.h"

/**
 * Implementación de función para insertar un elemento al final de la lista
 * @param head Puntero al primer elemento de la lista
 * @param value Valor a agregar a la lista
 */
void insert_end_h(node_h_t * head, struct hole value) {
    node_h_t * tmp = head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = (node_h_t *) malloc(sizeof(node_h_t));
    tmp->next->value = value;
    tmp->next->next = NULL;
}

/**
 * Implementación de función eliminar el primer elemento de la lista
 * @param head Puntero al primer elemento de la lista
 * @return Retorna el identificador del hueco eliminado
 */
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

/**
 * Implementación de función para eliminar el último elemento de la lista
 * @param head Puntero al primer elemento de la lista
 * @return Retorna el identificador del hueco eliminado
 */
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

/**
 * Implementación de la función para modificar la información de un hueco
 * @param head Puntero al primer elemento de la lista
 * @param posX Nueva posición del hueco en el eje X
 * @param posY Nueva posición del hueco en el eje Y
 * @param id Identificador del hueco a modificar
 */
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

/**
 * Implementación de función para buscar el índice de un hueco en la lista
 * @param head Puntero al primer elemento de la lista
 * @param id Identificador del hueco a buscar
 * @return Retorna la posición del hueco en la lista
 */
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

/**
 * Implementación de la función para imprimir la lista
 * @param head Puntero al primer elemento de la lista
 */
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
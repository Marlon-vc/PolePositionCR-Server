//
// Created by pvill on 16/6/2020.
//

#include "turbo_linked_list.h"

/**
 * Implementación de función para insertar un elemento al final de la lista
 * @param head Puntero al primer elemento de la lista
 * @param value Valor a agregar a la lista
 */
void insert_end_t(node_tu_t * head, struct turbo value) {
    node_tu_t * tmp = head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = (node_tu_t *) malloc(sizeof(node_tu_t));
    tmp->next->value = value;
    tmp->next->next = NULL;
}

/**
 * Implementación de función eliminar el primer elemento de la lista
 * @param head Puntero al primer elemento de la lista
 * @return Retorna el identificador del elemento eliminado
 */
int remove_first_t(node_tu_t * head) {
    int retVal;
    node_tu_t * nextNode = NULL;

    if (head == NULL)
        return -1;

    nextNode = head->next->next;
    retVal = head->next->value.id;
    free(head->next);
    head->next = nextNode;

    return retVal;
}

/**
 * Implementación de función para eliminar un elemento en cierta posición
 * @param head Puntero al primer elemento de la lista
 * @param n Índice del elemento a eliminar
 * @return Retorna el identificador del elemento eliminado
 */
int remove_at_t(node_tu_t * head, int n) {
    int i = 0;
    int retVal;
    node_tu_t * current = head;
    node_tu_t * tmp = NULL;

    if (n == 0)
        return remove_first_t(head);
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
 * Implementación de función para modificar los valores de un turbo
 * @param head Puntero al primer elemento de la lista
 * @param posX Posición en el eje X del turbo
 * @param posY Posición en el eje Y del turbo
 * @param id Identificador del turbo a modificar
 */
void modify_turbo(node_tu_t * head, int id, int got) {
    node_tu_t * tmp = head;
    while (tmp != NULL) {
        if (tmp->value.id == id) {
//            tmp->value.posX = posX;
//            tmp->value.posY = posY;
            tmp->value.got = got;
            break;
        }
        tmp = tmp->next;
    }
}

/**
 * Implementación de función para buscar la posición de un elemento de la lista
 * @param head Puntero al primer elemento de la lista
 * @param id Identificador del elemento a buscar
 * @return Retorna la posición del elemento
 */
int find_turbo_pos(node_tu_t * head, int id) {
    int pos = 0;
    node_tu_t *tmp = head;
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
void print_list_t(node_tu_t * head) {
    node_tu_t * tmp = head;
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
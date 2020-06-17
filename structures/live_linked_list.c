//
// Created by pvill on 16/6/2020.
//

#include "live_linked_list.h"

/**
 * Implementación de función para insertar un elemento al final de la lista
 * @param head Puntero al primer elemento de la lista
 * @param value Valor a agregar a la lista
 */
void insert_end_l(node_l_t * head, struct live value) {
    node_l_t * tmp = head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = (node_l_t *) malloc(sizeof(node_l_t));
    tmp->next->value = value;
    tmp->next->next = NULL;
}

/**
 * Implementación de función eliminar el primer elemento de la lista
 * @param head Puntero al primer elemento de la lista
 * @return Retorna el identificador de la vida eliminada
 */
int remove_first_l(node_l_t * head) {
    int retVal;
    node_l_t * nextNode = NULL;

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
 * @return Retorna el identificador de la vida eliminada
 */
int remove_at_l(node_l_t * head, int n) {
    int i = 0;
    int retVal;
    node_l_t * current = head;
    node_l_t * tmp = NULL;

    if (n == 0)
        return remove_first_l(head);
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
 * Implementación de la función para modificar la información de una vida
 * @param head Puntero al primer elemento de la lista
 * @param posX Nueva posición de la vida en el eje X
 * @param posY Nueva posición de la vida en el eje Y
 * @param id Identificador de la vida a modificar
 */
void modify_live(node_l_t * head, int posX, int posY, int id) {
    node_l_t * tmp = head;
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
 * Implementación de función para buscar el índice de una vida en la lista
 * @param head Puntero al primer elemento de la lista
 * @param id Identificador de la vida a buscar
 * @return Retorna la posición de la vida en la lista
 */
int find_live_pos(node_l_t * head, int id) {
    int pos = 0;
    node_l_t *tmp = head;
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
void print_list_l(node_l_t * head) {
    node_l_t * tmp = head;
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
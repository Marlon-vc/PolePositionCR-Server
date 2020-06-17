//
// Created by pvill on 15/6/2020.
//

#include "car_linked_list.h"

/**
 * Implementación de función para insertar un elemento al final de la lista
 * @param head Puntero al primer elemento de la lista
 * @param valor Valor a agregar a la lista
 */
void insert_end(node_t * head, struct car valor) {
    node_t *tmp = head;

    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = (node_t *) malloc(sizeof(node_t));
    tmp->next->valor = valor;
    tmp->next->next = NULL;
}

/**
 * Implementación de función para insertar un elemento al inicio de la lista
 * @param head Puntero al primer elemento de la lista
 * @param valor Valor a agregar a la lista
 */
void insert(node_t * head, struct car valor) {
    node_t * new_node;
    new_node = (node_t *) malloc(sizeof(node_t));

    new_node->valor = valor;
    new_node->next = head->next;
    head->next = new_node;
}

/**
 * Implementación de función eliminar el primer elemento de la lista
 * @param head Puntero al primer elemento de la lista
 * @return Retorna el color del carro eliminado
 */
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

/**
 * Implementación de función para eliminar el último elemento de la lista
 * @param head Puntero al primer elemento de la lista
 * @return Retorna el color del carro eliminado
 */
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

/**
 * Implementación de función para eliminar un elemento en cierta posición
 * @param head Puntero al primer elemento de la lista
 * @param n Índice del elemento a eliminar
 * @return Retorna el color del carro eliminado
 */
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

/**
 * Implementación para modificar la disponibilidad de un auto
 * @param head Puntero al primer elemento de la lista
 * @param carColor Color del carro del elemento a modificar
 * @param newAvailability Nueva disponibilidad del auto
 */
void modify_availability(node_t * head, char * carColor, int newAvailability) {
    node_t * tmp = head;
    while (tmp != NULL) {
        if (strcmp(tmp->valor.color, carColor) == 0) {
            tmp->valor.available = newAvailability;
            break;
        }
        tmp = tmp->next;
    }
}

/**
 * Implementación de la función para imprimir la lista
 * @param head Puntero al primer elemento de la lista
 */
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
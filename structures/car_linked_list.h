//
// Created by pvill on 15/6/2020.
//

#ifndef POLEPOSITIONCR_SERVER_CAR_LINKED_LIST_H
#define POLEPOSITIONCR_SERVER_CAR_LINKED_LIST_H

#include <stdlib.h>

#include <stdio.h>
#include <string.h>

/**
 * Estructura del carro
 */
struct car {
    char color[80];
    int available;
};

/**
 * Nodo de la lista de Carros
 */
typedef struct node {
    struct car valor ;
    struct node * next;
} node_t;

/**
 * Definición de función para insertar un elemento al final de la lista
 * @param head Puntero al primer elemento de la lista
 * @param valor Valor a agregar a la lista
 */
void insert_end(node_t * head, struct car valor); // agrega un elemento al final

/**
 * Definición de función para insertar un elemento al inicio de la lista
 * @param head Puntero al primer elemento de la lista
 * @param valor Valor a agregar a la lista
 */
void insert(node_t * head, struct car valor); // agrega al inicio

/**
 * Definición de función eliminar el primer elemento de la lista
 * @param head Puntero al primer elemento de la lista
 * @return Retorna el color del carro eliminado
 */
char * remove_first(node_t * head);

/**
 * Definición de función para eliminar el último elemento de la lista
 * @param head Puntero al primer elemento de la lista
 * @return Retorna el color del carro eliminado
 */
char * remove_last(node_t * head);

/**
 * Definición de función para eliminar un elemento en cierta posición
 * @param head Puntero al primer elemento de la lista
 * @param n Índice del elemento a eliminar
 * @return Retorna el color del carro eliminado
 */
char * remove_at(node_t * head, int n);

/**
 * Definición de función para modificar la disponibilidad de un auto
 * @param head Puntero al primer elemento de la lista
 * @param carColor Color del carro del elemento a modificar
 * @param newAvailability Nueva disponibilidad del auto
 */
void modify_availability(node_t * head, char * carColor, int newAvailability);

/**
 * Definición de la función para imprimir la lista
 * @param head Puntero al primer elemento de la lista
 */
void print_list(node_t * head);
#endif //POLEPOSITIONCR_SERVER_CAR_LINKED_LIST_H

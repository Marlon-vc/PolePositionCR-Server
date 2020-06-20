//
// Created by pvill on 16/6/2020.
//

#ifndef POLEPOSITIONCR_SERVER_TURBO_LINKED_LIST_H
#define POLEPOSITIONCR_SERVER_TURBO_LINKED_LIST_H

#include <stdlib.h>

#include <stdio.h>
#include <string.h>

/**
 * Estructura del turbo
 */
struct turbo {
    int id;
    int posX;
    int posY;
    int taken;
};

/**
 * Nodo de la lista de turbos
 */
typedef struct node_tu {
    struct turbo value;
    struct node_tu * next;
}node_tu_t;

/**
 * Definición de función para insertar un elemento al final de la lista
 * @param head Puntero al primer elemento de la lista
 * @param value Valor a agregar a la lista
 */
void insert_end_t(node_tu_t * head, struct turbo value);

/**
 * Definición de función eliminar el primer elemento de la lista
 * @param head Puntero al primer elemento de la lista
 * @return Retorna el identificador del elemento eliminado
 */
int remove_first_t(node_tu_t * head);

/**
 * Definición de función para eliminar un elemento en cierta posición
 * @param head Puntero al primer elemento de la lista
 * @param n Índice del elemento a eliminar
 * @return Retorna el identificador del elemento eliminado
 */
int remove_at_t(node_tu_t * head, int n);

/**
 * Definición de función para modificar los valores de un turbo
 * @param head Puntero al primer elemento de la lista
 * @param posX Posición en el eje X del turbo
 * @param posY Posición en el eje Y del turbo
 * @param id Identificador del turbo a modificar
 */
void modify_turbo(node_tu_t * head, int id, int got);


/**
 * Definición de función para buscar la posición de un elemento de la lista
 * @param head Puntero al primer elemento de la lista
 * @param id Identificador del elemento a buscar
 * @return Retorna la posición del elemento
 */
int find_turbo_pos(node_tu_t * head, int id);

/**
 * Definición de la función para imprimir la lista
 * @param head Puntero al primer elemento de la lista
 */
void print_list_t(node_tu_t * head);

#endif //POLEPOSITIONCR_SERVER_TURBO_LINKED_LIST_H

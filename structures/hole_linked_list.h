//
// Created by pvill on 16/6/2020.
//

#ifndef POLEPOSITIONCR_SERVER_HOLE_LINKED_LIST_H
#define POLEPOSITIONCR_SERVER_HOLE_LINKED_LIST_H

#include <stdlib.h>

#include <stdio.h>
#include <string.h>

/**
 * Estructura del hueco
 */
struct hole {
    int id;
    int posX;
    int posY;
};

/**
 * Nodo de la lista de huecos
 */
typedef struct node_h {
    struct hole value;
    struct node_h * next;
}node_h_t;

/**
 * Definición de función para insertar un elemento al final de la lista
 * @param head Puntero al primer elemento de la lista
 * @param value Valor a agregar a la lista
 */
void insert_end_h(node_h_t * head, struct hole value);

/**
 * Definición de función eliminar el primer elemento de la lista
 * @param head Puntero al primer elemento de la lista
 * @return Retorna el identificador del jugador eliminado
 */
int remove_first_h(node_h_t * head);

/**
 * Definición de función para eliminar un elemento en cierta posición
 * @param head Puntero al primer elemento de la lista
 * @param n Índice del elemento a eliminar
 * @return Retorna el identificador del hueco eliminado
 */
int remove_at_h(node_h_t * head, int n);

/**
 * Definición de la función para modificar la información de un hueco
 * @param head Puntero al primer elemento de la lista
 * @param posX Nueva posición del hueco en el eje X
 * @param posY Nueva posición del hueco en el eje Y
 * @param id Identificador del hueco a modificar
 */
void modify_hole(node_h_t * head, int posX, int posY, int id);

/**
 * Definición de función para buscar el índice de un hueco en la lista
 * @param head Puntero al primer elemento de la lista
 * @param id Identificador del hueco a buscar
 * @return Retorna la posición del hueco en la lista
 */
int find_hole_pos(node_h_t * head, int id);

/**
 * Definición de la función para imprimir la lista
 * @param head Puntero al primer elemento de la lista
 */
void print_list_h(node_h_t * head);

#endif //POLEPOSITIONCR_SERVER_HOLE_LINKED_LIST_H

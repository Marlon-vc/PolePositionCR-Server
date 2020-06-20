//
// Created by pvill on 16/6/2020.
//

#ifndef POLEPOSITIONCR_SERVER_LIVE_LINKED_LIST_H
#define POLEPOSITIONCR_SERVER_LIVE_LINKED_LIST_H

#include <stdlib.h>

#include <stdio.h>
#include <string.h>

/**
 * Estructura de la vida
 */
struct live {
    int id;
    int posX;
    int posY;
    int taken;
};

/**
 * Nodo de la lista de vidas
 */
typedef struct node_l {
    struct live value;
    struct node_l * next;
}node_l_t;

/**
 * Definición de función para insertar un elemento al final de la lista
 * @param head Puntero al primer elemento de la lista
 * @param value Valor a agregar a la lista
 */
void insert_end_l(node_l_t * head, struct live value);

/**
 * Definición de función eliminar el primer elemento de la lista
 * @param head Puntero al primer elemento de la lista
 * @return Retorna el identificador de la vida eliminada
 */
int remove_first_l(node_l_t * head);

/**
 * Definición de función para eliminar un elemento en cierta posición
 * @param head Puntero al primer elemento de la lista
 * @param n Índice del elemento a eliminar
 * @return Retorna el identificador de la vida eliminada
 */
int remove_at_l(node_l_t * head, int n);

/**
 * Definición de la función para modificar la información de una vida
 * @param head Puntero al primer elemento de la lista
 * @param posX Nueva posición de la vida en el eje X
 * @param posY Nueva posición de la vida en el eje Y
 * @param id Identificador de la vida a modificar
 */
void modify_live(node_l_t * head, int posX, int posY, int id);

/**
 * Definición de función para buscar el índice de una vida en la lista
 * @param head Puntero al primer elemento de la lista
 * @param id Identificador de la vida a buscar
 * @return Retorna la posición de la vida en la lista
 */
int find_live_pos(node_l_t * head, int id);

/**
 * Definición de la función para imprimir la lista
 * @param head Puntero al primer elemento de la lista
 */
void print_list_l(node_l_t * head);

#endif //POLEPOSITIONCR_SERVER_LIVE_LINKED_LIST_H

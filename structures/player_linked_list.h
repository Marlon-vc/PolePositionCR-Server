//
// Created by pvill on 15/6/2020.
//

#ifndef POLEPOSITIONCR_SERVER_PLAYER_LINKED_LIST_H
#define POLEPOSITIONCR_SERVER_PLAYER_LINKED_LIST_H

#include <stdlib.h>

#include <stdio.h>
#include <string.h>

/**
 * Estructura del jugador
 */
struct player {
    int id;
    int pos;
    int playerX;
    int lives;
    char car_color[80];
    int points;
};

/**
 * Nodo de la lista de jugadores
 */
typedef struct node_p {
    struct player value;
    struct node_p * next;
}node_p_t;

/**
 * Definición de función para insertar un elemento al final de la lista
 * @param head Puntero al primer elemento de la lista
 * @param value Valor a agregar a la lista
 */
void insert_end_p(node_p_t * head, struct player value); // agrega un elemento al final

/**
 * Definición de función para insertar un elemento al inicio de la lista
 * @param head Puntero al primer elemento de la lista
 * @param value Valor a agregar a la lista
 */
void insert_p(node_p_t * head, struct player value); // agrega al inicio

/**
 * Definición de función eliminar el primer elemento de la lista
 * @param head Puntero al primer elemento de la lista
 * @return Retorna el identificador del jugador eliminado
 */
int remove_first_p(node_p_t * head);

/**
 * Definición de función para eliminar el último elemento de la lista
 * @param head Puntero al primer elemento de la lista
 * @return Retorna el identificador del jugador eliminado
 */
int remove_last_p(node_p_t * head);

/**
 * Definición de función para eliminar un elemento en cierta posición
 * @param head Puntero al primer elemento de la lista
 * @param n Índice del elemento a eliminar
 * @return Retorna el identificador del jugador eliminado
 */
int remove_at_p(node_p_t * head, int n);

/**
 * Definición de función para modificar la información de un jugador
 * @param head Puntero al primer elemento de la lista
 * @param pos Nueva posición del jugador en la pista
 * @param playerX Nueva posición del jugador en el eje X
 * @param lives Vidas a aumentar del jugador, positivo si de desea aumentar, negativo si se desea disminuir
 * @param car_color Color del carro del jugador a modificar
 * @param points Puntos a aumentar del jugador, positivo si de desea aumentar, negativo si se desea disminuir
 */
void modify_player(node_p_t * head, int pos, int playerX, int lives, char * car_color, int points);

/**
 * Definición de función para buscar el índice de un jugador en la lista
 * @param head Puntero al primer elemento de la lista
 * @param car_color Color del carro del jugador a buscar
 * @return Retorna la posición del jugador
 */
int find_player_pos(node_p_t * head, char * car_color);

/**
 * Definición de función para aumentar los puntos de un jugador
 * @param head Puntero al primer elemento de la lista
 * @param car_color Color del carro del jugador al que se le quiere aumentar los puntos
 * @param points Puntos a aumentar
 */
void increase_points(node_p_t * head, char * car_color, int points);

/**
 * Definición de función para aumentar la vida de los jugadores
 * @param head Puntero al primer elemento de la lista
 * @param car_color Color del carro del jugador a aumentar la vida
 */
void increase_live(node_p_t * head, char * car_color);

/**
 * Definicion de funcion para obtener las vidas de un jugador
 * @param head
 * @param car_color
 * @return
 */
int get_player_live (node_p_t * head, char * car_color);

/**
 * Definición de la función para imprimir la lista
 * @param head Puntero al primer elemento de la lista
 */
void print_list_p(node_p_t * head);

#endif //POLEPOSITIONCR_SERVER_PLAYER_LINKED_LIST_H

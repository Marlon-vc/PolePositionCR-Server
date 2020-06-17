//
// Created by pvill on 15/6/2020.
//
#include "player_linked_list.h"

/**
 * Implementación de función para insertar un elemento al final de la lista
 * @param head Puntero al primer elemento de la lista
 * @param value Valor a agregar a la lista
 */
void insert_end_p(node_p_t * head, struct player value) {
    node_p_t *tmp = head;

    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = (node_p_t *) malloc(sizeof(node_p_t));
    tmp->next->value = value;
    tmp->next->next = NULL;
}

/**
 * Implementación de función para insertar un elemento al inicio de la lista
 * @param head Puntero al primer elemento de la lista
 * @param value Valor a agregar a la lista
 */
void insert_p(node_p_t * head, struct player value) {
    node_p_t * new_node;
    new_node = (node_p_t *) malloc(sizeof(node_p_t));

    new_node->value = value;
    new_node->next = head->next;
    head->next = new_node;
}

/**
 * Implementación de función eliminar el primer elemento de la lista
 * @param head Puntero al primer elemento de la lista
 * @return Retorna el identificador del jugador eliminado
 */
int remove_first_p(node_p_t * head) {
    int retVal;
    node_p_t * nextNode = NULL;

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
 * @return Retorna el identificador del jugador eliminado
 */
int remove_last_p(node_p_t * head) {
    int retVal;
    node_p_t * tmp = head;
    while (tmp->next->next != NULL) {
        tmp = tmp->next;
    }
    retVal = head->next->value.id;
    free(tmp->next);
    tmp->next = NULL;
    return retVal;
}

/**
 * Implementación de función para eliminar un elemento en cierta posición
 * @param head Puntero al primer elemento de la lista
 * @param n Índice del elemento a eliminar
 * @return Retorna el identificador del jugador eliminado
 */
int remove_at_p(node_p_t * head, int n) {
    int i = 0;
    int retVal;
    node_p_t * current = head;
    node_p_t * tmp = NULL;

    if (n == 0)
        return remove_first_p(head);
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
 * Implementación de función para modificar la información de un jugador
 * @param head Puntero al primer elemento de la lista
 * @param pos Nueva posición del jugador en la pista
 * @param playerX Nueva posición del jugador en el eje X
 * @param lives Vidas a aumentar del jugador
 * @param car_color Color del carro del jugador a modificar
 * @param points Puntos a aumentar del jugador //TODO actualizar metodo para que los actualice
 */
void modify_player(node_p_t * head, int pos, int playerX, int lives, char * car_color, int points) {
    node_p_t * tmp = head;
    while (tmp != NULL) {
        if (strcmp(car_color, tmp->value.car_color) == 0) {
            tmp->value.pos = pos;
            tmp->value.playerX = playerX;
            //tmp->value.lives = lives;
            //tmp->value.points = points;
            break;
        }
        tmp = tmp->next;
    }
}

/**
 * Implementación de función para buscar el índice de un jugador en la lista
 * @param head Puntero al primer elemento de la lista
 * @param car_color Color del carro del jugador a buscar
 * @return Retorna la posición del jugador
 */
int find_player_pos(node_p_t * head, char * car_color) {
    int pos = 0;
    node_p_t *tmp = head;
    while (tmp != NULL) {
        if (strcmp(car_color, tmp->value.car_color) == 0) {
            return pos;
        }
        pos++;
        tmp = tmp->next;
    }
    return -1;
}

/**
 * Implementación de función para aumentar los puntos de un jugador
 * @param head Puntero al primer elemento de la lista
 * @param car_color Color del carro del jugador al que se le quiere aumentar los puntos
 * @param points Puntos a aumentar
 */
void increase_points(node_p_t * head, char * car_color, int points) {
    node_p_t * tmp = head;
    while (tmp != NULL) {
        if (strcmp(car_color, tmp->value.car_color) == 0) {
            tmp->value.points += points;
            break;
        }
        tmp = tmp->next;
    }
}

/**
 * Implementación de función para aumentar la vida de los jugadores
 * @param head Puntero al primer elemento de la lista
 * @param car_color Color del carro del jugador a aumentar la vida
 */
void increase_live(node_p_t * head, char * car_color) {
    node_p_t * tmp = head;
    while (tmp != NULL) {
        if (strcmp(car_color, tmp->value.car_color) == 0) {
            tmp->value.lives += 1;
            break;
        }
        tmp = tmp->next;
    }
}

/**
 * Implementación de la función para imprimir la lista
 * @param head Puntero al primer elemento de la lista
 */
void print_list_p(node_p_t * head) {
    node_p_t * tmp = head;
    tmp= tmp->next;
    int i = 0;
    if (tmp == NULL)
        printf("[ ]");
    while (tmp != NULL) {
        if (i == 0){
            printf("[");
        }
        if (tmp->next == NULL) {
            printf("id:%i pos:%i playerX:%i lives:%i car color:%s points:%i]", tmp->value.id, tmp->value.pos, tmp->value.playerX,
                    tmp->value.lives, tmp->value.car_color, tmp->value.points);
        } else {
            printf("id:%i pos:%i playerX:%i lives:%i car color:%s, points:%i, ", tmp->value.id, tmp->value.pos, tmp->value.playerX,
                    tmp->value.lives, tmp->value.car_color, tmp->value.points);
        }
        tmp = tmp->next;
        i++;
    }
}


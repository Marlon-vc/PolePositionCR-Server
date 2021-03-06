#ifndef POLEPOSITIONCR_SERVER_GAME_FUNCTIONS_H
#define POLEPOSITIONCR_SERVER_GAME_FUNCTIONS_H

#include <time.h>
#include "../json/cJSON.h"
#include "../structures/car_linked_list.h"
#include "../structures/player_linked_list.h"
#include "../structures/live_linked_list.h"
#include "../structures/hole_linked_list.h"
#include "../structures/turbo_linked_list.h"

/**
 * Definción de las estructuras car, que van a representar los carros en el servidor
 */
struct car head_s;
struct car red_car;
struct car blue_car;
struct car purple_car;
struct car white_car;

/**
 * Definición de las listas donde se van a almacenar los sprites y los jugadores
 */
node_t * carsList;
node_p_t * playerList;
node_l_t * livesList;
node_h_t * holeList;
node_tu_t * turboList;

/**
 * Variable que define si el servidor se está ejecutando
 */
int server_running;

/**
 * Definición de la función para inicializar la lista de carros
 */
void load_car_list();

/**
 * Definición de la función para inicializar la lista de jugadores
 */
void load_player_list();

/**
 * Definición de la función para inicializar la lista de vidas
 */
void load_lives_list();

/**
 * Definición de la función para inicializar la lista de huecos
 */
void load_hole_list();

/**
 * Definición de la función para inicializar la lista de turbos
 */
void load_turbo_list();

/**
 * Definición de la función para crear aleatoriamente los huecos, los turbos y las vidas
 */
void create_sprites();

/**
 * Definición de función para obtener las vidas de la pista
 * @return JSON Array con las vidas
 */
cJSON * get_lives();

/**
 * Definición de función para obtener los huecos de la pista
 * @return JSON Array con los huecos
 */
cJSON * get_holes();

/**
 * Definición de función para obtener los turbos de la pista
 * @return JSON Array con los turbos
 */
cJSON * get_turbos();

/**
 * Definición de la función para agregar un jugador a la lista de jugadores
 * @param pos Posición del jugador a lo largo de la pista
 * @param playerX Posición del jugador en el eje X
 * @param carColor Color del carro que utiliza el jugador
 * @param lives Vidas iniciales del jugador
 * @param points Puntos iniciales del jugador
 */
void add_player(cJSON *pos, cJSON *playerX, cJSON *carColor, cJSON *lives, cJSON *points);

/**
 * Definición del método para colocar las listas de sprites en un Json
 * @return Json con las listas de sprites
 */
cJSON * load_sprites();

/**
 * Definición de la función para obtener los datos del JSON
 * @param data Datos que vienen del cliente sobre el nuevo jugador
 */
void set_new_player(cJSON *data);

/**
 * Definición de la función para eliminar un jugador de la lista y poner el
 * carro disponible
 * @param carColor Color del carro del jugador a eliminar
 */
void remove_player(cJSON *carColor);

/**
 * Definición de la función para actualizar los datos de un jugador
 * @param pos Nueva posición del jugador en la pista
 * @param playerX Nueva posición del jugador en el eje X
 * @param carColor Color del carro del jugador a actualizar
 * @param lives Vidas actuales del jugador
 * @param points Puntos actuales del jugador
 */
void update_player(cJSON *pos, cJSON *playerX, cJSON *carColor, cJSON *lives, cJSON *points);

/**
 * Definicion de la funcion para obtener las vidas del jugador actual
 * @param car_color
 */
int get_player_lives(cJSON *car_color);

/**
 * Definición de función para agregar un hueco a la lista
 * @param id Identificador del hueco
 * @param posX Posición del hueco en X
 * @param posY Posición del hueco en la pista
 */
void add_hole(cJSON *id, cJSON *posX, cJSON *posY);

/**
 * Definición de función para agregar una nueva vida a la lista
 * @param id id Identificador del hueco
 * @param posX Posición del hueco en X
 * @param posY Posición del hueco en la pista
 */
void add_live(cJSON *id, cJSON *posX, cJSON *posY, cJSON *taken);

/**
 * Definición de función para eliminar una vida de la lista y agregarle una vida al jugador
 * @param id Identificador de la vida a eliminar
 * @param car_color Color del carro del jugador que va a utilizar la vida
 */
void remove_live(cJSON *id, cJSON *car_color);

/**
 * Definición de función para agregar un nuevo turbo a la lista
 * @param id id Identificador del turbo
 * @param posX Posición del turbo en X
 * @param posY Posición del turbo en la pista
 */
void add_turbo(cJSON *id, cJSON *posX, cJSON *posY);

/**
 * Definición de función para eliminar un turbo de la lista y aumentar la velocidad del jugador
 * @param id Identificador del turbo
 * @param car_color Color del carro del jugador que tomó el turbo
 */
void remove_turbo(cJSON *id, cJSON *car_color);

/**
 * Definición de función para obtener una lista con los carros disponibles
 * @return Retorna un JSON con los carros disponibles
 */
cJSON *get_available_cars();

/**
 * Definición de función que coloca un carro como no disponible
 * @param carColor Color del carro al que se le va a cambiar la disponibilidad
 */
void set_available_cars(cJSON *carColor);

/**
 * Definición de función para obtener una lista con los jugadores actuales
 * @return Retorna un JSON con los jugadores actuales
 */
cJSON *get_players_list();

/**
 * Definición de función para generar la pista de carreras
 * @return Retorna un JSON con la pista de carreras
 */
cJSON *create_track();

/**
 * Método para obtener la información del juego
 * @param response Respuesta que se le va a enviar al cliente
 */
void get_game_info(cJSON *response);

/**
 * Método para actualizar los datos del jugador
 * @param data Json con los nuevos datos
 */
void update_player_info(cJSON *data);

/**
 * Método para actualizar el estado del turbo
 * @param data Json con la nueva información
 */
void update_turbo(cJSON *data);

/**
 * Método para actualizar el estado de las vidas
 * @param data Json con los nuevos datos
 */
void update_live(cJSON *data);

/**
 * Método para colocar todos los turbos como disponibles
 */
void reset_turbos();

/**
 * Método para colocar todas las vidas como disponibles
 */
void reset_lives();

/**
 * Método para obtener los puntos del jugador
 * @param color Color del carro del jugador
 * @return Entero con los puntos
 */
int get_player_points(cJSON *color);

#endif //POLEPOSITIONCR_SERVER_GAME_FUNCTIONS_H

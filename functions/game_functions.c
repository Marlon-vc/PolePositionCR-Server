#include "game_functions.h"
#include "../constants.h"

/**
 * Implementación de la función para crear una curva en la pista según los parámetros dados
 * @param intensity: Intensidad de la curva.
 * @param from: Desde que rango inicia la curva.
 * @param to: Hasta que rango termina la curva.
 * @return Un objeto JSON que representa una curva.
 */
cJSON *make_curve(double intensity, int from, int to) {
    cJSON *curve = cJSON_CreateObject();
    cJSON_AddNumberToObject(curve, "intensity", intensity);
    cJSON_AddNumberToObject(curve, "from", from);
    cJSON_AddNumberToObject(curve, "to", to);
    return curve;
}

/**
 * Implementación de la función para generar la pista de carreras.
 * @return Retorna un JSON con la pista de carreras.
 */
cJSON *create_track() {
    cJSON *track = cJSON_CreateObject();
    cJSON_AddNumberToObject(track, "length", TRACK_LENGTH);
    cJSON *curves = cJSON_CreateArray();

    cJSON_AddItemToArray(curves, make_curve(5.2, 300, 450));
    cJSON_AddItemToArray(curves, make_curve(-2.7, 500, 600));
    cJSON_AddItemToArray(curves, make_curve(1.5, 700, 900));
    cJSON_AddItemToArray(curves, make_curve(-4.2, 900, 1000));
    cJSON_AddItemToArray(curves, make_curve(1.2, 1000, 1500));

    cJSON_AddItemToObject(track, "curves", curves);

    return track;
}

/**
 * Implementación de la función para inicializar la lista de carros
 */
void load_car_list() {
    char *null_head = "";
    char *rojo = "Rojo";
    char *azul ="Azul";
    char *morado = "Morado";
    char *blanco = "Blanco";

    strcpy(head_s.color, null_head);
    head_s.available = -1;
    strcpy(red_car.color, rojo);
    red_car.available = 1;
    strcpy(blue_car.color, azul);
    blue_car.available = 1;
    strcpy(purple_car.color, morado);
    purple_car.available = 1;
    strcpy(white_car.color, blanco);
    strcpy(white_car.color, blanco);
    white_car.available = 1;

    carsList = NULL;
    carsList = (node_t *) malloc(sizeof(node_t));
    carsList->valor = head_s;
    carsList->next = NULL;

    insert_end(carsList, red_car);
    insert_end(carsList, blue_car);
    insert_end(carsList, purple_car);
    insert_end(carsList, white_car);
}

/**
 * Implementación de la función para inicializar la lista de jugadores
 */
void load_player_list() {
    struct player player0;
    player0.id = -1;
    strcpy(player0.car_color, "");
    player0.lives = -1;
    player0.playerX = -1;
    player0.pos = -1;

    playerList = NULL;
    playerList = (node_p_t *) malloc(sizeof(node_p_t));
    playerList->value = player0;
    playerList->next = NULL;
}

/**
 * Implementación de la función para inicializar la lista de vidas
 */
void load_lives_list() {
    struct live l0 = {-1, -1, -1};

    livesList = NULL;
    livesList = (node_l_t *) malloc(sizeof(node_l_t));
    livesList->value = l0;
    livesList->next = NULL;
}

/**
 * Implementación de la función para inicializar la lista de huecos
 */
void load_hole_list() {
    struct hole h0 = {-1, -1, -1};

    holeList = NULL;
    holeList = (node_h_t *) malloc(sizeof(node_h_t));
    holeList->value = h0;
    holeList->next = NULL;
}

/**
 * Implementación de la función para inicializar la lista de turbos
 */
void load_turbo_list() {
    struct turbo t0 = {-1, -1, -1};

    turboList = NULL;
    turboList = (node_tu_t *) malloc(sizeof(node_tu_t));
    turboList->value = t0;
    turboList->next = NULL;
}

void create_sprites() {
    //srand(time(0));
    srand(time(0) * 12897236);

    // Crear huecos

    for (int i = 0; i < HOLES; i++) {
        int posX = (rand() % (TRACK_LENGTH - START + 1)) + START;
        int posY = (rand() % (MAX_SIDE_LEFT + 1 - MIN_SIDE_RIGHT)) + MIN_SIDE_RIGHT;
        struct hole new_hole = {i, posX, posY};
        insert_end_h(holeList, new_hole);
    }

    // Crear vidas

    for (int i = 0; i < LIVE; i++) {
        int posX = (rand() % (TRACK_LENGTH - START + 1)) + START;
        int posY = (rand() % (MAX_SIDE_LEFT + 1 - MIN_SIDE_RIGHT)) + MIN_SIDE_RIGHT;
        struct live new_live = {i, posX, posY};
        insert_end_l(livesList, new_live);
    }

    // Crear turbos

    for (int i = 0; i < TURBO; i++) {
        int posX = (rand() % (TRACK_LENGTH - START + 1)) + START;
        int posY = (rand() % (MAX_SIDE_LEFT + 1 - MIN_SIDE_RIGHT)) + MIN_SIDE_RIGHT;
        struct turbo new_turbo = {i, posX, posY};
        insert_end_t(turboList, new_turbo);
    }
}

/**
 * Implementación de función para obtener las vidas de la pista
 * @return JSON Array con las vidas
 */
cJSON * get_lives() {
    node_l_t *tmp = livesList;
    tmp = tmp->next;
    cJSON *lives = cJSON_CreateArray();
    while (tmp != NULL) {
        cJSON *live = cJSON_CreateObject();
        cJSON_AddNumberToObject(live, "id", tmp->value.id);
        cJSON_AddNumberToObject(live, "posX", tmp->value.posX);
        cJSON_AddNumberToObject(live, "posY", tmp->value.posY);
        cJSON_AddItemToArray(lives, live);

        tmp = tmp->next;
    }
    return lives;
}

/**
 * Implementación de función para obtener los turbos de la pista
 * @return JSON Array con los turbos
 */
cJSON * get_turbos() {
    node_tu_t *tmp = turboList;
    tmp = tmp->next;
    cJSON *turbos = cJSON_CreateArray();
    while (tmp != NULL) {
        cJSON *turbo = cJSON_CreateObject();
        cJSON_AddNumberToObject(turbo, "id", tmp->value.id);
        cJSON_AddNumberToObject(turbo, "posX", tmp->value.posX);
        cJSON_AddNumberToObject(turbo, "posY", tmp->value.posY);
        cJSON_AddItemToArray(turbos, turbo);

        tmp = tmp->next;
    }
    return turbos;

}

/**
 * Implementación de función para obtener los huecos de la pista
 * @return JSON Array con los huecos
 */
cJSON * get_holes() {
    node_h_t *tmp = holeList;
    tmp = tmp->next;
    cJSON *holes = cJSON_CreateArray();
    while(tmp != NULL) {
        cJSON *hole = cJSON_CreateObject();
        cJSON_AddNumberToObject(hole, "id", tmp->value.id);
        cJSON_AddNumberToObject(hole, "posX", tmp->value.posX);
        cJSON_AddNumberToObject(hole, "posY", tmp->value.posY);
        cJSON_AddItemToArray(holes, hole);

        tmp = tmp->next;
    }
    return holes;
}

/**
 * Implementación de la función para agregar un jugador a la lista de jugadores
 * @param pos Posición del jugador a lo largo de la pista
 * @param playerX Posición del jugador en el eje X
 * @param carColor Color del carro que utiliza el jugador
 * @param lives Vidas iniciales del jugador
 * @param points Puntos iniciales del jugador
 */
void add_player(cJSON *pos, cJSON *playerX, cJSON *carColor, cJSON *lives, cJSON *points) {
    struct player player1;
    player1.id = 1;
    player1.pos = pos->valueint;
    player1.lives = lives->valueint;
    player1.playerX = playerX->valueint;
    strcpy(player1.car_color, carColor->valuestring);
    player1.points = points->valueint;
    insert_end_p(playerList, player1);
}

/**
 * Implementación de la función para obtener los datos del JSON
 * @param data Datos que vienen del cliente sobre el nuevo jugador
 */
void set_new_player(cJSON *data) {
    cJSON *pos = cJSON_GetObjectItemCaseSensitive(data, "pos");
    cJSON *playerX= cJSON_GetObjectItemCaseSensitive(data, "playerX");
    cJSON *carColor= cJSON_GetObjectItemCaseSensitive(data, "carColor");
    cJSON *lives= cJSON_GetObjectItemCaseSensitive(data, "lives");
    cJSON *points = cJSON_GetObjectItemCaseSensitive(data, "points");
    add_player(pos, playerX, carColor, lives, points);
    print_list_p(playerList);
    printf("\n");
}

/**
 * Implementación de la función para eliminar un jugador de la lista y poner el
 * carro disponible
 * @param carColor Color del carro del jugador a eliminar
 */
void remove_player(cJSON *carColor) {
    int pos = find_player_pos(playerList, carColor->valuestring);
    remove_at_p(playerList, pos);
    modify_availability(carsList, carColor->valuestring, 1);
}

/**
 * Implementación de la función para actualizar los datos de un jugador
 * @param pos Nueva posición del jugador en la pista
 * @param playerX Nueva posición del jugador en el eje X
 * @param carColor Color del carro del jugador a actualizar
 * @param lives Vidas a aumentar del jugador
 * @param points Puntos a aumentar del jugador //TODO actualizar metodo
 */
void update_player(cJSON *pos, cJSON *playerX, cJSON *carColor, cJSON *lives, cJSON *points) {
    modify_player(playerList, pos->valueint, playerX->valueint, lives->valueint, carColor->valuestring,
                  points->valueint);
}

/**
 * Implementación de la función para agregar un hueco a la lista
 * @param id Identificador del hueco
 * @param posX Posición del hueco en X
 * @param posY Posición del hueco en la pista
 */
void add_hole(cJSON *id, cJSON *posX, cJSON *posY) {
    struct hole structhole = {
            id->valueint,
            posX->valueint,
            posY->valueint
    };
    insert_end_h(holeList, structhole);
}

/**
 * Implementación de función para agregar una nueva vida a la lista
 * @param id id Identificador del hueco
 * @param posX Posición del hueco en X
 * @param posY Posición del hueco en la pista
 */
void add_live(cJSON *id, cJSON *posX, cJSON *posY) {
    struct live structlive = {
            id->valueint,
            posX->valueint,
            posY->valueint
    };
    insert_end_l(livesList, structlive);
}

/**
 * Implementación de función para eliminar una vida de la lista y agregarle una vida al jugador,
 * así como aumentar sus puntos
 * @param id Identificador de la vida a eliminar
 * @param car_color Color del carro del jugador que va a utilizar la vida
 */
void remove_live(cJSON *id, cJSON *car_color) {
    int pos = find_live_pos(livesList, id->valueint);
    remove_at_l(livesList, pos);
    increase_points(playerList, car_color->valuestring, 3);
    increase_live(playerList, car_color->valuestring);
}

/**
 * Implementación de función para agregar un nuevo turbo a la lista
 * @param id id Identificador del turbo
 * @param posX Posición del turbo en X
 * @param posY Posición del turbo en la pista
 */
void add_turbo(cJSON *id, cJSON *posX, cJSON *posY) {
    struct turbo structturbo = {
            id->valueint,
            posX->valueint,
            posY->valueint
    };
    insert_end_t(turboList, structturbo);
}

/**
 * Implementación de función para eliminar un turbo de la lista y aumentar la velocidad del jugador,
 * así como sus puntos
 * @param id Identificador del turbo
 * @param car_color Color del carro del jugador que tomó el turbo
 */
void remove_turbo(cJSON *id, cJSON *car_color) {
    int pos = find_turbo_pos(turboList, id->valueint);
    remove_at_t(turboList, pos);
    increase_points(playerList, car_color->valuestring, 2);
    // TODO aumentar la velocidad a 180 km/h
}

/**
 * Implementación de función para obtener una lista con los carros disponibles
 * @return Retorna un JSON con los carros disponibles
 */
cJSON *get_available_cars() {
    node_t * tmp = carsList;
    cJSON *cars = cJSON_CreateObject();
    cJSON *array_of_cars = cJSON_CreateArray();
    while (tmp != NULL) {
        if (tmp->valor.available == 1) {
            cJSON_AddItemToArray(array_of_cars, cJSON_CreateString(tmp->valor.color));
        }
        tmp = tmp->next;
    }
    cJSON_AddItemToObject(cars, "array_cars", array_of_cars);
    return cars;
}

/**
 * Implementación de función que coloca un carro como no disponible
 * @param carColor Color del carro al que se le va a cambiar la disponibilidad
 */
void set_available_cars(cJSON *carColor) {
    if (cJSON_IsString(carColor) && (carColor->valuestring != NULL)) {
        printf("[Car color] %s.\n", carColor->valuestring);
    }
    modify_availability(carsList, carColor->valuestring, 0);
}

/**
 * Implementación de función para obtener una lista con los jugadores actuales
 * @return Retorna un JSON con los jugadores actuales
 */
cJSON *get_players_list() {
    node_p_t *tmp = playerList;
    tmp = tmp->next;
    cJSON *players = cJSON_CreateArray();
    while (tmp != NULL) {
        cJSON *player = cJSON_CreateObject();
        cJSON_AddNumberToObject(player, "lives", tmp->value.lives);
        cJSON_AddNumberToObject(player, "playerX", tmp->value.playerX);
        cJSON_AddNumberToObject(player, "pos", tmp->value.pos);
        cJSON_AddStringToObject(player, "carColor", tmp->value.car_color);

        cJSON_AddItemToArray(players, player);
        tmp = tmp->next;
    }

    return players;
}

/**
 * todo comentar
 * @param response
 */
void get_game_info(cJSON *response) {
    cJSON *track = create_track();
    cJSON *holes = get_holes();
    cJSON *lives = get_lives();
    cJSON *turbos = get_turbos();

    cJSON_AddItemToObject(response, "track", track);
    cJSON_AddItemToObject(response, "holes", holes);
    cJSON_AddItemToObject(response, "lives", lives);
    cJSON_AddItemToObject(response, "turbos", turbos);
}

/**
 * todo comentar
 * @param data
 */
void update_player_info(cJSON *data) {
    cJSON *pos = cJSON_GetObjectItemCaseSensitive(data, "pos");
    cJSON *playerX = cJSON_GetObjectItemCaseSensitive(data, "playerX");
    cJSON *carColor = cJSON_GetObjectItemCaseSensitive(data, "carColor");
    cJSON *lives = cJSON_GetObjectItemCaseSensitive(data, "lives");
    cJSON *points = cJSON_GetObjectItemCaseSensitive(data, "points");

    update_player(pos, playerX, carColor, lives, points);
}

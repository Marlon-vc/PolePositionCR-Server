#include "server.h"
#include "../constants.h"

/**
 * TODO documentar
 * @return
 */
int init_config() {
    int opt = 1;

    printf("[Info] Creating connection socket ");
    fflush(NULL);
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("...failed\n");
        return -1;
    }
    printf("...done\n");

    printf("[Info] Setting socket configuration ");
    fflush(NULL);
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("...failed\n");
        return -1;
    }
    printf("...done\n");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(SERVER_PORT);

    printf("[Info] Binding server to address ");
    fflush(NULL);
    int status = bind(server_fd, (struct sockaddr *) &address, sizeof(address));
    if (status < 0) {
        perror("...failed\n");
        return -1;
    }
    printf("...done\n");

    printf("[Info] Listening to connections on port %i ", SERVER_PORT);
    fflush(NULL);
    if (listen(server_fd, 3) < 0) {
        perror("...failed\n");
        return -1;
    }
    printf("...done\n");

    return 0;
}

/**
 * todo docuemntar
 * @param intensity
 * @param from
 * @param to
 * @return
 */
cJSON *make_curve(double intensity, int from, int to) {
    cJSON *curve = cJSON_CreateObject();
    cJSON_AddNumberToObject(curve, "intensity", intensity);
    cJSON_AddNumberToObject(curve, "from", from);
    cJSON_AddNumberToObject(curve, "to", to);

    return curve;
}

/**
 * todo docuemntar
 * @return
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
    strcpy(head_s.color, "");
    head_s.available = -1;
    strcpy(red_car.color, "Rojo");
    red_car.available = 1;
    strcpy(blue_car.color, "Azul");
    blue_car.available = 1;
    strcpy(purple_car.color, "Morado");
    purple_car.available = 1;
    strcpy(white_car.color, "Blanco");
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

void prueba() {
    struct player p1 = {0, 0, 0, 3, "Rojo", 0};
    struct player p2 = {0, 0, 0, 3, "Azul", 0};
    struct player p3 = {0, 0, 0, 3, "Morado", 0};
    struct player p4 = {0, 0, 0, 3, "Blanco", 0};

    insert_end_p(playerList, p1);
    insert_end_p(playerList, p2);
    insert_end_p(playerList, p3);
    insert_end_p(playerList, p4);
    printf("\n");
    print_list_p(playerList);
    printf("\n");
    increase_live(playerList, "Rojo");
    increase_points(playerList, "Rojo", 20);
    print_list_p(playerList);
    printf("\n");
//    struct hole h1 = {0, 20, 30};
//    struct hole h2 = {1, 50, 40};
//    struct hole h3 = {2, 40, 60};
//
//    struct live l1 = {0, 10, 50};
//    struct live l2 = {1, 20, 40};
//    struct live l3 = {2, 30, 30};
//
//    struct turbo t1 = {0, 90, 40};
//    struct turbo t2 = {1, 100, 0};
//    struct turbo t3 = {2, 30, 20};
//
//    insert_end_h(holeList, h1);
//    insert_end_h(holeList, h2);
//    insert_end_h(holeList, h3);
//
//    insert_end_l(livesList, l1);
//    insert_end_l(livesList, l2);
//    insert_end_l(livesList, l3);
//
//    insert_end_t(turboList, t1);
//    insert_end_t(turboList, t2);
//    insert_end_t(turboList, t3);
//
//    printf("\n");
//    print_list_h(holeList);
//    printf("\n");
//    int pos = find_hole_pos(holeList, 1);
//    printf("pos to delete %i \n", pos);
//    remove_at_h(holeList, pos);
//    print_list_h(holeList);
//    printf("\n");
//
//    printf("\n");
//    print_list_l(livesList);
//    printf("\n");
//    int pos1 = find_live_pos(livesList, 2);
//    printf("pos to delete %i \n", pos1);
//    remove_at_l(livesList, pos1);
//    print_list_l(livesList);
//    printf("\n");
//
//    printf("\n");
//    print_list_t(turboList);
//    printf("\n");
//    int pos2 = find_turbo_pos(turboList, 0);
//    printf("pos to delete %i \n", pos2);
//    remove_at_t(turboList, pos2);
//    print_list_t(turboList);
//    printf("\n");

}

/**
 * TODO documentar
 * @return
 */
int start() {
    server_running = 1;
    load_car_list(); //Cargar la lista de carros
    load_player_list();
    load_hole_list();
    load_lives_list();
    load_turbo_list();
//    prueba();

    int init_status = init_config();
    if (init_status < 0) {
        perror("[Error] Failed to initialize server.\n");
        return -1;
    }

    char buffer[BUFFER_SIZE] = {0};


    while (server_running == 1) {
//    for (int i = 0; i < 1000; i++) {
        printf("[Info] Waiting for connection.\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addr_len)) < 0) {
            perror("[Warning] Failed to accept incoming connection.\n");
            memset(buffer, 0, sizeof(buffer));
            continue;
        }

        val_read = read(new_socket, buffer, BUFFER_SIZE);
        cJSON *json =  cJSON_Parse(buffer);
        if (json == NULL) {
            printf("[Error] Could not parse client data.\n");
            const char *error_ptr = cJSON_GetErrorPtr();
            if (error_ptr != NULL) {
                fprintf(stderr, "Error before %s.\n", error_ptr);
            }
            continue;
        }

        action = cJSON_GetObjectItemCaseSensitive(json, "action");
        if (cJSON_IsString(action) && (action->valuestring != NULL)) {
            printf("[Action] %s.\n", action->valuestring);
        }

        cJSON *response = cJSON_CreateObject();

        //Se verifica la acción a realizar
        if (strcmp(action->valuestring, "create_game") == 0) {
            printf("[Info] Requesting game creation.\n");
            //TODO inicializar juego.
            cJSON_AddStringToObject(response, "status", "success");

        } else if (strcmp(action->valuestring, "get_track") == 0) {
            printf("[Info] Requesting track state.\n");
            cJSON *track = create_track();
            cJSON_AddItemToObject(response, "track", track);
            cJSON_AddStringToObject(response, "status", "success");

        } else if (strcmp(action->valuestring, "update_game") == 0) {
            printf("[Info] Requesting game update.\n");
            //TODO: actualizar el estado de los jugadores en los demás clientes.
            cJSON_AddStringToObject(response, "status", "success");

        } else if (strcmp(action->valuestring, "update_player") == 0) {
            printf("[Info] Requesting player state update.\n");
            cJSON *pos = cJSON_GetObjectItemCaseSensitive(json, "pos");
            cJSON *playerX = cJSON_GetObjectItemCaseSensitive(json, "playerX");
            cJSON *carColor = cJSON_GetObjectItemCaseSensitive(json, "carColor");
            cJSON *lives = cJSON_GetObjectItemCaseSensitive(json, "lives");
            cJSON *points = cJSON_GetObjectItemCaseSensitive(json, "points");
            update_player(pos, playerX, carColor, lives, points);
            cJSON_AddStringToObject(response, "status", "success");

        } else if (strcmp(action->valuestring, "get_cars") == 0) {
            printf("[Info] Requesting cars update.\n");
            cJSON_AddItemToObject(response, "cars", get_available_cars());
            cJSON_AddStringToObject(response, "status", "success");

        } else if (strcmp(action->valuestring, "set_cars") == 0) {
            printf("[Info] Setting cars update.\n");
            cJSON *color = cJSON_GetObjectItemCaseSensitive(json, "carColor");
            set_available_cars(color);

        } else if (strcmp(action->valuestring, "add_player") == 0) {
            printf("[Info] Setting new player.\n");
            set_new_player(json);

        }else if (strcmp(action->valuestring, "get_players") == 0) {
            printf("[Info] Requesting players list.\n");
            cJSON_AddItemToObject(response, "players", get_players_list());
            cJSON_AddStringToObject(response, "status", "success");

        }else {
            printf("[Warning] Unknown client action request.\n");
            cJSON_AddStringToObject(response, "status", "unknown_action");

        }

        char *response_string = cJSON_Print(response);
        if (response_string == NULL) {
            perror("[Error] Failed to convert response to string.\n");
            cJSON_Delete(response);
            cJSON_Delete(json);
            continue;

        }

        send(new_socket, response_string, strlen(response_string), 0);
        cJSON_Delete(response);
        cJSON_Delete(json);
        fflush(NULL);
        memset(buffer, 0, sizeof(buffer));
    }

    printf("[Info] Shutting down server.\n");
    return 0;
}



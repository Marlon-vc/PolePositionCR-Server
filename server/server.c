#include "server.h"
#include "../constants.h"


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

cJSON *make_curve(double intensity, int from, int to) {
    cJSON *curve = cJSON_CreateObject();
    cJSON_AddNumberToObject(curve, "intensity", intensity);
    cJSON_AddNumberToObject(curve, "from", from);
    cJSON_AddNumberToObject(curve, "to", to);

    return curve;
}

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

void loadCarList() {
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

    head = NULL;
    head = (node_t *) malloc(sizeof(node_t));
    head->valor = head_s;
    head->next = NULL;

    insert_end(head, red_car);
    insert_end(head, blue_car);
    insert_end(head, purple_car);
    insert_end(head, white_car);
}

void loadPlayerList() {
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

void add_player(cJSON *pos, cJSON *playerX, cJSON *carColor, cJSON *lives) {
    struct player player1;
    player1.id = 1;
    player1.pos = pos->valueint;
    player1.lives = lives->valueint;
    player1.playerX = playerX->valueint;
    strcpy(player1.car_color, carColor->valuestring);
    insert_end_p(playerList, player1);
}

void remove_player(cJSON *carColor) {
    int pos = find_player_pos(playerList, carColor->valuestring);
    remove_at_p(playerList, pos);
    modify_availability(head, carColor->valuestring, 1);
}

void update_player(cJSON *pos, cJSON *playerX, cJSON *carColor, cJSON *lives) {
    modify_player(playerList, pos->valueint, playerX->valueint, lives->valueint, carColor->valuestring);
}

cJSON *get_available_cars() {
    node_t * tmp = head;
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

void set_available_cars(cJSON *carColor) {
    if (cJSON_IsString(carColor) && (carColor->valuestring != NULL)) {
        printf("[Car color] %s.\n", carColor->valuestring);
    }
    modify_availability(head, carColor->valuestring, 0);
}

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
    struct player p1;
    struct player p2;
    struct player p3;
    struct player p4;

    p1.playerX = 0;
    p1.pos = 0;
    p1.id = 0;
    p1.lives = 3;
    strcpy(p1.car_color, "Rojo");

    p2.playerX = 0;
    p2.pos = 0;
    p2.id = 0;
    p2.lives = 3;
    strcpy(p2.car_color, "Azul");

    p3.playerX = 0;
    p3.pos = 0;
    p3.id = 0;
    p3.lives = 3;
    strcpy(p3.car_color, "Morado");

    p4.playerX = 0;
    p4.pos = 0;
    p4.id = 0;
    p4.lives = 3;
    strcpy(p4.car_color, "Blanco");

    insert_end_p(playerList, p1);
    insert_end_p(playerList, p2);
    insert_end_p(playerList, p3);
    insert_end_p(playerList, p4);
    printf("\n");
    print_list_p(playerList);
    printf("\n");
    int pos = find_player_pos(playerList, "Morado");
    printf("pos to delete %i \n", pos);
    remove_at_p(playerList, pos);
    print_list_p(playerList);
    printf("\n");


}

int start() {
    loadCarList(); //Cargar la lista de carros
    loadPlayerList();
//    prueba();

    int init_status = init_config();
    if (init_status < 0) {
        perror("[Error] Failed to initialize server.\n");
        return -1;
    }

    char buffer[2048] = {0};

    for (int i = 0; i < 1000; i++) {
        printf("[Info] Waiting for connection.\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addr_len)) < 0) {
            perror("[Warning] Failed to accept incoming connection.\n");
            continue;
        }

        val_read = read(new_socket, buffer, 2048);
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

        } else if (strcmp(action->valuestring, "update_state") == 0) {
            printf("[Info] Requesting state update.\n");
            //TODO: actualizar estado?
            cJSON_AddStringToObject(response, "status", "success");

        } else if (strcmp(action->valuestring, "get_cars") == 0) {
            printf("[Info] Requesting cars update.\n");
            cJSON_AddStringToObject(response, "status", "success");
            cJSON_AddItemToObject(response, "cars", get_available_cars());
        } else if (strcmp(action->valuestring, "set_cars") == 0) {
            printf("[Info] Setting cars update.\n");
            cJSON *color = cJSON_GetObjectItemCaseSensitive(json, "carColor");
            set_available_cars(color);
        } else if (strcmp(action->valuestring, "add_player") == 0) {
            printf("[Info] Setting new player.\n");
            cJSON *pos = cJSON_GetObjectItemCaseSensitive(json, "pos");
            cJSON *playerX= cJSON_GetObjectItemCaseSensitive(json, "playerX");
            cJSON *carColor= cJSON_GetObjectItemCaseSensitive(json, "carColor");
            cJSON *lives= cJSON_GetObjectItemCaseSensitive(json, "lives");
            add_player(pos, playerX, carColor, lives);
            print_list_p(playerList);
            printf("\n");
        }else if (strcmp(action->valuestring, "get_players") == 0) {
            printf("[Info] Requesting players list.\n");
            cJSON_AddStringToObject(response, "status", "success");
            cJSON_AddItemToObject(response, "players", get_players_list());
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
    }

    printf("[Info] Shutting down server.\n");
    return 0;
}



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
        printf("[Action] %s.\n", carColor->valuestring);
    }
    node_t *tmp = head;
    while (tmp != NULL) {
        if (strcmp(carColor->valuestring, tmp->valor.color) == 0) {
            tmp->valor.available = 0;
        }
        tmp = tmp->next;
    }
    print_list(head);

}

int start() {
    loadCarList(); //Cargar la lista de carros

    int init_status = init_config();
    if (init_status < 0) {
        perror("[Error] Failed to initialize server.\n");
        return -1;
    }

    char buffer[2048] = {0};

    for (int i = 0; i < 100; i++) {
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
        } else {
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



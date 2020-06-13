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

    //TODO: realizar las curvas de la pista (rango de líneas).
    cJSON_AddItemToArray(curves, make_curve(5.2, 300, 450));
    cJSON_AddItemToArray(curves, make_curve(-2.7, 500, 600));
    cJSON_AddItemToArray(curves, make_curve(1.5, 700, 900));
    cJSON_AddItemToArray(curves, make_curve(-4.2, 900, 1000));
    cJSON_AddItemToArray(curves, make_curve(1.2, 1000, 1500));

    cJSON_AddItemToObject(track, "curves", curves);

    return track;
}

int start() {
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
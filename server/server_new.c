#include "server_new.h"

/**
 * Método para inicializar el socket del servidor
 * @return Retorna un código de estado
 */
int init_config() {
    BOOL opt_val = FALSE;
    int opt_len = sizeof(BOOL);

    printf("[Info] Initializing Winsock ");
    fflush(NULL);
    if (WSAStartup(MAKEWORD( 2, 2), &wsa) != 0) {
        fprintf(stderr, "...failed.\nCode: %d\n", WSAGetLastError());
        return -1;
    }
    printf("...done.\n");

    printf("[Info] Creating socket ");
    fflush(NULL);
    if ((server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        fprintf(stderr, "...failed.\nCode: %d\n", WSAGetLastError());
        return -1;
    }
    printf("...done.\n");

    printf("[Info] Configuring socket ");
    fflush(NULL);
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char *) &opt_val, opt_len) == SOCKET_ERROR) {
        fprintf(stderr, "...failed.\nCode: %d\n", WSAGetLastError());
        return -1;
    }
    printf("...done.\n");

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(SERVER_PORT);

    printf("[Info] Binding socket to address ");
    fflush(NULL);
    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == SOCKET_ERROR) {
        fprintf(stderr, "...failed.\nCode: %d\n", WSAGetLastError());
    }
    printf("...done.\n");

    printf("[Info] Setting socket to listen mode ");
    fflush(NULL);
    listen(server_socket, 3);
    printf("...done.\n");

    return 0;
}

/**
 * Método principal del servidor
 * @return Retorna un código de estado
 */
int start() {
    server_running= 1;
    game_finished = 0;

    int init_status = init_config();
    if (init_status < 0) {
        perror("[Error] Could not set initial configuration\n");
        return -1;
    }

    load_car_list();
    load_player_list();
    load_hole_list();
    load_lives_list();
    load_turbo_list();
    create_sprites();

    char buffer[BUFFER_SIZE] = {0};

    int c = sizeof(struct sockaddr_in);
    int conCount = 0;

    while (server_running == 1) {
        printf("[Info] Waiting for connection\n");
        if ((client_socket = accept(server_socket, (struct sockaddr *) &client_address, &c)) == INVALID_SOCKET) {
            perror("[Warning] Failed to accept incoming connection\n");
            fprintf(stderr, "Error ocurred at connection #%i\n", conCount+1);
            memset(&buffer, 0, sizeof(buffer));
            continue;
        }
        conCount++;

        recv(client_socket, buffer, BUFFER_SIZE, 0);
        cJSON *json = cJSON_Parse(buffer);
        if (json == NULL) {
            perror("[Error] Could not parse client data\n");
            const char *error_ptr = cJSON_GetErrorPtr();
            if (error_ptr != NULL) {
                fprintf(stderr, "Error before: %s", error_ptr);
            }
            continue;
        }

        cJSON *action = cJSON_GetObjectItemCaseSensitive(json, "action");
        if (cJSON_IsString(action) && (action->valuestring != NULL)) {
            printf("[Action] %s\n", action->valuestring);
        }

        cJSON *response = cJSON_CreateObject();

        if (strcmp(action->valuestring, "get_game_info") == 0) {
            get_game_info(response);
            cJSON_AddStringToObject(response, "status", "success");

        } else if (strcmp(action->valuestring, "update_player") == 0) {
            update_player_info(json);
            cJSON_AddStringToObject(response, "status", "success");

        } else if (strcmp(action->valuestring, "get_turbos") == 0) {
            cJSON_AddItemToObject(response, "turbos", get_turbos());
            cJSON_AddStringToObject(response, "status", "success");

        } else if (strcmp(action->valuestring, "update_turbo") == 0) {
            update_turbo(json);
            cJSON_AddStringToObject(response, "status", "success");

        } else if (strcmp(action->valuestring, "get_lives") == 0) {
            cJSON_AddItemToObject(response, "lives", get_lives());
            cJSON_AddStringToObject(response, "status", "success");

        } else if (strcmp(action->valuestring, "update_live") == 0) {
            update_live(json);
            cJSON_AddStringToObject(response, "status", "success");

        } else if (strcmp(action->valuestring, "reset_lives") == 0) {
            reset_lives();
            cJSON_AddStringToObject(response, "status", "success");

        } else if (strcmp(action->valuestring, "get_cars") == 0) {
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

        } else if (strcmp(action->valuestring, "reset_turbos") == 0) {
            reset_turbos();
            cJSON_AddStringToObject(response, "status", "success");

        } else if (strcmp(action->valuestring, "exit") == 0) {
            printf("[Info] Exit.\n");
            cJSON *color = cJSON_GetObjectItemCaseSensitive(json, "car_color");
            remove_player(color);
        } else if (strcmp(action->valuestring, "get_player_lives") == 0) {
            printf("[Info] Requesting actual player lives");
            cJSON *color = cJSON_GetObjectItemCaseSensitive(json, "car_color");
            cJSON_AddNumberToObject(response, "lives", get_player_lives(color));

        }else if ((strcmp(action->valuestring, "get_points") == 0)) {
            printf("[Info] Requesting actual player points");
            cJSON *color = cJSON_GetObjectItemCaseSensitive(json, "car_color");
            cJSON_AddNumberToObject(response, "points", get_player_points(color));

        } else if (strcmp(action->valuestring, "finish_game") == 0) {
            game_finished = 1;
            cJSON_AddStringToObject(response, "status", "success");

        } else if (strcmp(action->valuestring, "is_game_finished") == 0) {
            cJSON_AddNumberToObject(response, "game_state", game_finished);
            cJSON_AddStringToObject(response, "status", "success");

        } else {
            perror("[Warning] Unknown client action request\n");
            cJSON_AddStringToObject(response, "status", "unknown_action");
        }

        char *response_string = cJSON_Print(response);
        if (response_string == NULL) {
            perror("[Error] Failed to convert response to string.\n");
            cJSON_Delete(response);
            cJSON_Delete(json);
            continue;

        }

        send(client_socket, response_string, strlen(response_string), 0);

        cJSON_Delete(json);
        cJSON_Delete(response);
        closesocket(client_socket);
        memset(&buffer, 0, sizeof(buffer));
    }

    printf("[Info] Shutting down server.\n");
    closesocket(server_socket);
    WSACleanup();
    return 0;
}
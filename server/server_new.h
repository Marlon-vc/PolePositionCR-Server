#ifndef POLEPOSITIONCR_SERVER_SERVER_NEW_H
#define POLEPOSITIONCR_SERVER_SERVER_NEW_H

#include <stdio.h>
#include <winsock2.h>

#include "../constants.h"
#include "../functions/game_functions.h"

#pragma comment(lib, "ws2_32.lib") //Winsock

WSADATA wsa;
SOCKET server_socket, client_socket;
struct sockaddr_in server_address, client_address;

int server_running;
int game_finished;

int start();
int init_config();

#endif //POLEPOSITIONCR_SERVER_SERVER_NEW_H

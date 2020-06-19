//
// Created by Marlo on 09/06/2020.
//

#ifndef POLEPOSITIONCR_SERVER_CONSTANTS_H
#define POLEPOSITIONCR_SERVER_CONSTANTS_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define SERVER_PORT 8080
#define TRACK_LENGTH 1800
#define START 100
#define MIN_SIDE_RIGHT -1000
#define MAX_SIDE_LEFT 1000
#define HOLES 20
#define LIVE 8
#define TURBO 10
#define BUFFER_SIZE 4096
const cJSON *action = NULL;

int server_fd, new_socket, val_read;
struct sockaddr_in address;
int addr_len;

#endif //POLEPOSITIONCR_SERVER_CONSTANTS_H

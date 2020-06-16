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
#define BUFFER_SIZE 4096
const cJSON *action = NULL;

int server_fd, new_socket, val_read;
struct sockaddr_in address;
int addr_len;

#endif //POLEPOSITIONCR_SERVER_CONSTANTS_H

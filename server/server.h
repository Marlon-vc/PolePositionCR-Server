#ifndef POLEPOSITIONCR_SERVER_SERVER_H
#define POLEPOSITIONCR_SERVER_SERVER_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include "../json/cJSON.h"

int init_config();

cJSON *create_track();

int start();

#endif //POLEPOSITIONCR_SERVER_SERVER_H

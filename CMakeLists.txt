cmake_minimum_required(VERSION 3.16)
project(PolePositionCR_Server C)

set(CMAKE_C_STANDARD 99)

add_executable(PolePositionCR_Server main.c constants.h json/cJSON.h json/cJSON.c server/server.c server/server.h structures/linkedlist.h structures/linkedlist.c)

add_executable(PolePositionCR_Client client.c)
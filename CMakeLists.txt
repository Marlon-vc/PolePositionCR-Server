cmake_minimum_required(VERSION 3.16)
project(PolePositionCR_Server C)

set(CMAKE_C_STANDARD 99)

add_executable(PolepositionCR_Server main.c server/server_new.c server/server_new.h json/cJSON.h json/cJSON.c functions/game_functions.c functions/game_functions.h structures/car_linked_list.h structures/car_linked_list.c structures/player_linked_list.h structures/player_linked_list.c structures/hole_linked_list.c structures/hole_linked_list.h structures/live_linked_list.h structures/live_linked_list.c structures/turbo_linked_list.c structures/turbo_linked_list.h)

add_executable(PolePositionCR_Client client.c)
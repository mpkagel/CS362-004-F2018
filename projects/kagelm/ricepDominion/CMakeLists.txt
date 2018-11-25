cmake_minimum_required(VERSION 3.12)
project(dominion)

set(CMAKE_C_FLAGS "-std=c99")

include_directories(.)

add_library(rngs.o rngs.h rngs.c)

add_library(dominion.o dominion.c rngs.o)

add_executable(playdom playdom.c dominion.c rngs.h rngs.c)

add_executable(badTestDrawCard badTestDrawCard.c dominion.o rngs.o)

add_executable(testBuyCard testBuyCard.c dominion.c rngs.h rngs.c)

add_test(testAll dominion.o testSuite.c dominion.o rngs.o)

add_library(interface.o interface.h interface.c)

add_library(player player.c dominion.o rngs.o interface.o)

target_link_libraries(playdom m)

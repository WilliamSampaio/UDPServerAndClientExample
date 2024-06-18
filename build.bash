#!/usr/bin/env bash
g++ -Wall -Werror server.cpp -o server.out
g++ -Wall -Werror client.cpp -o client.out
./server.out
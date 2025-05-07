#pragma once
#include <stdio.h>

typedef struct StationNode StationNode;
typedef struct PlatformNode PlatformNode;
typedef struct Passenger Passenger;
typedef struct Platform Platform;
typedef struct Ticket Ticket;
typedef struct Day Day;

void moveCursor(int row, int col);

void printAsciiArtAtLocation(int row, int col, const char* str);

Ticket* creatTicket();

Passenger* createPassenger();

StationNode* addStation(StationNode* list, const char* station);

Platform* createPlatform(int num);

void fillPassengerQueue(Day* day);

int countPlatformList(PlatformNode* p);

Day nextDay(Day day);
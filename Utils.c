#include "Utils.h"
#include "Data.h"
#include <stdlib.h>

static const char* paint[6] = {
	"       _____                 . . . . . o o o o o",
	"     __|[_]|__ ___________ _______    ____      o",
	"    |[] [] []| [] [] [] [] [_____(__  ][]]_n_n__][.",
	"   _|________|_[_________]_[________]_|__|________)<",
	"     oo    oo 'oo      oo ' oo    oo 'oo 0000---oo\\_",
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
};

void moveCursor(int row, int col) {
	printf("\033[%d;%dH", row, col);
}

void printAsciiArtAtLocation(int row, int col, const char* str) {
	printf("\033[%d;%dH%s", row, col, str);
}

Ticket* creatTicket()
{
	Ticket* t = (Ticket*)malloc(sizeof(Ticket));
	t->isWrong = 0;
	t->destination = "몰랑";
	t->lastText = "ANYWHERE";
	t->num = t->subNum = 0;

	for (int i = 0; i < 6; i++) {
		t->paint[i] = paint[i];
	}

	return t;
}

Passenger* createPassenger()
{
	Passenger* p = (Passenger*)malloc(sizeof(Passenger));

	p->ticket = creatTicket();

	return p;
}

StationNode* addStation(StationNode* list, const char* station)
{
	return insertStationLast(list, station);
}

Platform* createPlatform(int num)
{
	Platform* p = (Platform*)malloc(sizeof(Platform));
	PassengerStack* s = (PassengerStack*)malloc(sizeof(PassengerStack));
	initStack(s);
	StationNode* l = NULL;

	p->num = num;
	p->passengerStack = s;
	p->stationList = l;

	return p;
}

void fillPassengerQueue(Day* day)
{
	PassengerQueue* q = day->passengerQueue;
	Passenger* p = createPassenger();
	if (day->day == 0) {
		enqueue(q, p);
	}
}

int countPlatformList(PlatformNode* p)
{
	if (p == NULL) return 0;

	int count = 0;
	PlatformNode* temp = p->link;

	do {
		count++;
		temp = temp->link;
	} while (temp!=p->link);

	return count;
}

Day nextDay(Day day)
{
	day.day++;
	
	switch (day.day)
	{
	case 7: {

		Platform* p3 = createPlatform(3);
		day.platformList = insertPlatformLast(day.platformList, p3);
		break;
	}
	case 14: {
		Platform* p4 = createPlatform(4);
		day.platformList = insertPlatformLast(day.platformList, p4);
	}
	default:
		break;
	}

	return day;
}

#include <stdio.h>
#include "Draw.h"

//테스트용 인클루드
#include "Data.h"
#include "Utils.h"
#include <stdlib.h>
#include <conio.h>

void printPlatform(Day* day) {
	PlatformNode* current = day->platformList->link;
	int index = 0;
	do {
		Platform* platform = current->data;

		moveCursor(7 + index * 3, 15);
		printf("%d번 플랫폼 : ", platform->num);
		printStationList(platform->stationList);

		current = current->link;
		index++;
	} while (current != day->platformList->link);
};

int main() {

	drawMainMenu();

	moveCursor(20,0);

	return 0;
}
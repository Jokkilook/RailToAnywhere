#include "Utils.h"
#include "Data.h"
#include <stdlib.h>
#include <time.h>
#include <conio.h>

static const char* paint[6] = {
	"       _____                 . . . . . o o o o o",
	"     __|[_]|__ ___________ _______    ____      o",
	"    |[] [] []| [] [] [] [] [_____(__  ][]]_n_n__][.",
	"   _|________|_[_________]_[________]_|__|________)<",
	"     oo    oo 'oo      oo ' oo    oo 'oo 0000---oo\\_",
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
};

static const char* wrongPaint[6][6] = {
	{
	"       _____                 . . . . . o o o o o",
	"     __|[_]|__ ___________ _______    ____      o",
	"    |[] [] []| [] [] [] [] [_____(__  ][]]_n_n__][.",
	"   _|________|_[_________]_[________]_|__|________)<",
	"     oo    oo 'oo      oo ' oo    oo 'oo 0000---oo\\_",
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	},
	{
	"       _____                 . . . . . o o o o o",
	"     __|[_]|__ ___________ _______    ____      o",
	"    |[] [] []| [] [] [] [] [_____(__  ][]]_n_n__][.",
	"   _|________|_[_________]_[________]_|__|________)<",
	"     oo    oo 'oo      oo ' oo    oo 'oo 0000---oo\\_",
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	},
	{
	"       _____                 . . . . . o o o o o",
	"     __|[_]|__ ___________ _______    ____      o",
	"    |[] [] []| [] [] [] [] [_____(__  ][]]_n_n__][.",
	"   _|________|_[_________]_[________]_|__|________)<",
	"     oo    oo 'oo      oo ' oo    oo 'oo 0000---oo\\_",
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	},
	{
	"       _____                 . . . . . o o o o o",
	"     __|[_]|__ ___________ _______    ____      o",
	"    |[] [] []| [] [] [] [] [_____(__  ][]]_n_n__][.",
	"   _|________|_[_________]_[________]_|__|________)<",
	"     oo    oo 'oo      oo ' oo    oo 'oo 0000---oo\\_",
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	},
	{
	"       _____                 . . . . . o o o o o",
	"     __|[_]|__ ___________ _______    ____      o",
	"    |[] [] []| [] [] [] [] [_____(__  ][]]_n_n__][.",
	"   _|________|_[_________]_[________]_|__|________)<",
	"     oo    oo 'oo      oo ' oo    oo 'oo 0000---oo\\_",
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	},
	{
	"       _____                 . . . . . o o o o o",
	"     __|[_]|__ ___________ _______    ____      o",
	"    |[] [] []| [] [] [] [] [_____(__  ][]]_n_n__][.",
	"   _|________|_[_________]_[________]_|__|________)<",
	"     oo    oo 'oo      oo ' oo    oo 'oo 0000---oo\\_",
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	}
};

void moveCursor(int row, int col) {
	printf("\033[%d;%dH", row, col);
}

void printAsciiArtAtLocation(int row, int col, const char* str) {
	printf("\033[%d;%dH%s", row, col, str);
}

void printError(const char* str)
{
	moveCursor(40, 0);
	printf("\033[1;31m%s\033[0m", str);
	int key = _getch();
}

Ticket* creatTicket()
{
	//티켓 메모리 할당
	Ticket* t = (Ticket*)malloc(sizeof(Ticket));
	srand(time(NULL));
	t->isWrong = rand() % 1;
	t->destination = "멧돼지";
	t->lastText = "ANYWHERE";
	t->num = t->subNum = 0;

	for (int i = 0; i < 6; i++) {
		t->paint[i] = paint[i];
	}

	return t;
}

Passenger* createPassenger()
{
	//승객 메모리 할당
	Passenger* p = (Passenger*)malloc(sizeof(Passenger));

	p->ticket = creatTicket();

	return p;
}

void addStationToPlatform(Day* day, int num, const char* station)
{
	//Day의 플랫폼 리스트
	PlatformList* pList = day->platformList;
	//num번의 플랫폼 데이터
	Platform* platform = searchPlatformListWithNum(pList, num)->data;
	//플랫폼의 역 리스트에 station 역 추가
	platform->stationList = addStation(platform->stationList, station);
}

StationNode* addStation(StationNode* list, const char* station)
{
	//이름만 바꾼;;
	return insertStationLast(list, station);
}

Platform* createPlatform(int num)
{
	//플랫폼 메모리 할당
	Platform* p = (Platform*)malloc(sizeof(Platform));
	//승객 스택 메모리 할당
	PassengerStack* s = (PassengerStack*)malloc(sizeof(PassengerStack));
	//승객 스택 초기화
	initStack(s);
	//역 리스트 초기화
	StationNode* l = NULL;

	//플랫폼 변수에 번호, 승객 스택, 역 리스트 할당
	p->num = num;
	p->passengerStack = s;
	p->stationList = l;

	return p;
}

void fillPassengerQueue(Day* day, int amount)
{
	PassengerQueue* q = day->passengerQueue;

	for (int i = 0; i < amount; i++) {
		Passenger* p = createPassenger();
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

void nextDay(Day* day)
{
	//날짜 ++
	day->day++;

	//대기 승객 큐에 승객 채우기
	if (0 <= day->day && day->day <= 3) {
		fillPassengerQueue(day, 5);
		//1,2 플랫폼에 역 2개씩 추가
		addStationToPlatform(day, 1, "조끼룩");
		addStationToPlatform(day, 1, "오끼악");
		addStationToPlatform(day, 2, "미리내");
		addStationToPlatform(day, 2, "미리암");
	}
	else if (4 <= day->day && day->day <= 6) {
		fillPassengerQueue(day, 2 + day->day);
	}
	else if (day->day == 7) {
		fillPassengerQueue(day, 8);
		//3번 플랫폼 추가
		Platform* p = createPlatform(3);
		day->platformList = insertPlatformLast(day->platformList, p);
		//3번 플랫폼에 역 추가
		addStationToPlatform(day, 3, "꼬끼오");
	}
	else if (7 < day->day && day->day <= 9) {
		fillPassengerQueue(day, 8);
		//3번 플랫폼에 역 추가
		addStationToPlatform(day, 3, "꼬끼오");
		addStationToPlatform(day, 3, "훌리우");
	}
	else if (10 <= day->day && day->day <= 13) {
		fillPassengerQueue(day, day->day - 1);
	}
	else if (day->day == 14) {
		fillPassengerQueue(day, 12);
		//4번 플랫폼 추가
		Platform* p = createPlatform(4);
		day->platformList = insertPlatformLast(day->platformList, p);
		//4번 플랫폼에 역 추가
		addStationToPlatform(day, 4, "옴멤메");
	}
	else if (14 < day->day && day->day <= 16) {
		fillPassengerQueue(day, 12);
		//4번 플랫폼에 역 추가
		addStationToPlatform(day, 4, "뽀꾸뿌");
		addStationToPlatform(day, 4, "키티닝");
	}
	else if (17 <= day->day && day->day <= 20) {
		fillPassengerQueue(day, day->day - 4);
	}
	else if (day->day == 21) {
		fillPassengerQueue(day, 16);
		//플랫폼 1,3의 역 리스트 교환
		exchangeStationListWithNum(day->platformList, 1, 3);
	}
	else if (22 <= day->day && day->day <= 23) {
		fillPassengerQueue(day, day->day - 5);
	}
	else if (day->day == 24) {
		fillPassengerQueue(day, 18);
		//플랫폼 2,4의 역 리스트 교환
		exchangeStationListWithNum(day->platformList, 2, 4);
	}
	else if (25 <= day->day && day->day <= 29) {
		fillPassengerQueue(day, day->day - 6);
	}
	else if (day->day == 30) {
		fillPassengerQueue(day, 48);
		//플랫폼 1,4 / 2,3 역 리스트 교환
		exchangeStationListWithNum(day->platformList, 1, 4);
		exchangeStationListWithNum(day->platformList, 2, 3);
	}

	int key = _getch();
}

void checkPlatformPassenger(Day* day)
{
	int wrongPassenger = 0;

	//플랫폼 리스트 헤드
	PlatformNode* platformList = day->platformList;
	//플랫폼 리스트 첫번째 노드
	PlatformNode* currentPlatform = platformList->link;

	//현재 추가된 플랫폼 별 검사
	do {
		//현재 플랫폼
		Platform* platform = currentPlatform->data;
		//현재 플랫폼의 목적지 리스트
		StationNode* stationList = platform->stationList;
		//검사할 승객
		Passenger* passenger = pop(platform->passengerStack);

		//플랫폼의 승객 스택에서 승객하나씩 목적지 검사 - 승객 스택이 빌 때까지
		while (passenger != NULL) {
			//승객의 목적지
			const char* passengerDestination = passenger->ticket->destination;

			//승객의 목적지가 해당 플랫폼 목적지 리스트에 없으면 ++
			if (!searchStationList(stationList, passengerDestination)) {
				wrongPassenger++;
			}
			//평가 끝난 승객은 메모리 해제 (티켓 포함)
			killPassenger(passenger);
			//다음 승객 뽑아 오기
			passenger = pop(platform->passengerStack);
		}

		//다음 플랫폼으로
		currentPlatform = currentPlatform->link;

	} while (currentPlatform!=platformList->link);

	day->wrongPassenger = wrongPassenger;
}

void initDay(Day* day)
{
	//승객 큐 생성
	PassengerQueue* queue = (PassengerQueue*)malloc(sizeof(PassengerQueue));
	initQueue(queue);

	//플랫폼 리스트 생성
	PlatformNode* platformList = NULL;

	//2개 플랫폼 생성
	Platform* p = createPlatform(1);
	Platform* p2 = createPlatform(2);

	//day값 할당
	day->day = 1;
	day->wrongPassenger = 0;
	day->GreatPassenger = 0;
	day->passengerQueue = queue;
	day->platformList = platformList;

	//기본 플랫폼 2개 추가
	day->platformList = insertPlatformLast(day->platformList, p);
	day->platformList = insertPlatformLast(day->platformList, p2);
}

void killPassenger(Passenger* passenger)
{
	//티켓 메모리 해제
	free(passenger->ticket);
	//승객 메모리 해제
	free(passenger);
}

void exchangeStationListWithNum(PlatformNode* platformList, int num1, int num2)
{
	//해당 번호의 플랫폼 2개
	Platform* platform1 = searchPlatformListWithNum(platformList, num1)->data;
	Platform* platform2 = searchPlatformListWithNum(platformList, num2)->data;

	//바꿀 플랫폼의 역 리스트
	StationNode* tempList = platform1->stationList;

	//맞교환
	platform1->stationList = platform2->stationList;
	platform2->stationList = tempList;
	//printError("교환함");
}

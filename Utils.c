#include "Utils.h"
#include "Data.h"
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>

StationStack* platform1;
StationStack* platform2;
StationStack* platform3;
StationStack* platform4;

void moveCursor(int row, int col) {
	printf("\033[%d;%dH", row, col);
}

void printAsciiArtAtLocation(int row, int col, const char* str) {
	printf("\033[%d;%dH%s", row, col, str);
}

void printError(const char* str)
{
	moveCursor(40, 0);
	printf("                                                                          ");
	moveCursor(40, 0);
	printf("\033[1;31m%s\033[0m", str);
	int key = _getch();
}

Ticket* createTicket(Day* day)
{
	//티켓 메모리 할당
	Ticket* t = (Ticket*)malloc(sizeof(Ticket));
	//위조 티켓 확률 30%
	t->isWrong = (rand() % 100 < 30) ? 1 : 0;

	//현재 플랫폼 리스트의 플랫폼의 역 리스트 중에서 하나 뽑기
	t->destination = getRandomStation(day);

	//식별 정보 추가
	t->lastText = "ANYWHERE";
	t->num = t->subNum = day->ticketCount++;
	day->totalPassengerCount++;
	for (int i = 0; i < 6; i++) {
		t->paint[i] = paint[i];
	}

	//위조 시 식별 정보 변형
	if (t->isWrong) { 
		switch (rand() % 4) {
		case 0: {
			int pick = rand() % 6;
			for (int i = 0; i < 6; i++) {
				t->paint[i] = wrongPaint[pick][i];
			}
			break;
		}
		case 1:
			t->num = t->subNum = rand() % day->totalPassengerCount;
			break;
		case 2:
			t->subNum = rand() % day->totalPassengerCount;
			break;
		case 3:
			t->lastText = wrongLastText[rand() % 6];
			break;
		}
	}

	return t;
}

Ticket createTutTicket(int isWrong)
{
	Ticket ticket = {
		isWrong,
		isWrong ? rand() % 30 : 0,
		isWrong ? rand() % 30 : 0,
		"서울역",
		{"","","","","",""},
		isWrong ? wrongLastText[rand() % 6] : "ANYWHERE"
	};

	if (isWrong) {
		int pick = rand() % 6;
		for (int i = 0; i < 6; i++) {
			ticket.paint[i] = wrongPaint[pick][i];
		}
	}
	else {
		for (int i = 0; i < 6; i++) {
			ticket.paint[i] = paint[i];
		}
	}

	return ticket;
}

Passenger* createPassenger(Day* day)
{
	//승객 메모리 할당
	Passenger* p = (Passenger*)malloc(sizeof(Passenger));

	p->ticket = createTicket(day);
	p->dialogue = createPassengerDialogue();

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
		Passenger* p = createPassenger(day);
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
	day->wrongPassenger = 0;
	day->greatPassenger = 0;
	day->ticketCount = 1;

	//0~3일째
	if (0 <= day->day && day->day <= 3) {
		//대기 승객 큐에 승객 채우기
		fillPassengerQueue(day, 5);
		//1,2 플랫폼에 역 2개씩 추가
		addStationToPlatform(day, 1, getStationFromPlatform(1));
		addStationToPlatform(day, 1, getStationFromPlatform(1));
		addStationToPlatform(day, 2, getStationFromPlatform(2));
		addStationToPlatform(day, 2, getStationFromPlatform(2));
	}
	//4~6일째
	else if (4 <= day->day && day->day <= 6) {
		//대기 승객 큐에 승객 채우기
		fillPassengerQueue(day, 2 + day->day);
	}
	//7일째
	else if (day->day == 7) {
		//대기 승객 큐에 승객 채우기
		fillPassengerQueue(day, 8);
		//3번 플랫폼 추가
		Platform* p = createPlatform(3);
		day->platformList = insertPlatformLast(day->platformList, p);
		//3번 플랫폼에 역 추가
		addStationToPlatform(day, 3, getStationFromPlatform(3));
	}
	//7~9일째
	else if (7 < day->day && day->day <= 9) {
		//대기 승객 큐에 승객 채우기
		fillPassengerQueue(day, 8);
		//3번 플랫폼에 역 추가
		addStationToPlatform(day, 3, getStationFromPlatform(3));
		addStationToPlatform(day, 3, getStationFromPlatform(3));
	}
	//10~13일째
	else if (10 <= day->day && day->day <= 13) {
		//대기 승객 큐에 승객 채우기
		fillPassengerQueue(day, day->day - 1);
	}
	//14일째
	else if (day->day == 14) {
		//대기 승객 큐에 승객 채우기
		fillPassengerQueue(day, 12);
		//4번 플랫폼 추가
		Platform* p = createPlatform(4);
		day->platformList = insertPlatformLast(day->platformList, p);
		//4번 플랫폼에 역 추가
		addStationToPlatform(day, 4, getStationFromPlatform(4));
	}
	//14~16일째
	else if (14 < day->day && day->day <= 16) {
		//대기 승객 큐에 승객 채우기
		fillPassengerQueue(day, 12);
		//4번 플랫폼에 역 추가
		addStationToPlatform(day, 4, getStationFromPlatform(4));
		addStationToPlatform(day, 4, getStationFromPlatform(4));
	}
	//17~20일째
	else if (17 <= day->day && day->day <= 20) {
		//대기 승객 큐에 승객 채우기
		fillPassengerQueue(day, day->day - 4);
	}
	//21일째
	else if (day->day == 21) {
		//대기 승객 큐에 승객 채우기
		fillPassengerQueue(day, 16);
		//플랫폼 1,3의 역 리스트 교환
		exchangeStationListWithNum(day->platformList, 1, 3);
	}
	//22~23일째
	else if (22 <= day->day && day->day <= 23) {
		//대기 승객 큐에 승객 채우기
		fillPassengerQueue(day, day->day - 5);
	}
	//24일째
	else if (day->day == 24) {
		//대기 승객 큐에 승객 채우기
		fillPassengerQueue(day, 18);
		//플랫폼 2,4의 역 리스트 교환
		exchangeStationListWithNum(day->platformList, 2, 4);
	}
	//25~29일째
	else if (25 <= day->day && day->day <= 29) {
		//대기 승객 큐에 승객 채우기
		fillPassengerQueue(day, day->day - 6);
	}
	//30일째
	else if (day->day == 30) {
		//대기 승객 큐에 승객 채우기
		fillPassengerQueue(day, 48);
		//플랫폼 1,4 / 2,3 역 리스트 교환
		exchangeStationListWithNum(day->platformList, 1, 4);
		exchangeStationListWithNum(day->platformList, 2, 3);
	}
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

			//승객의 목적지가 해당 플랫폼 목적지 리스트에 없거나 위조표면 잘못 응대 ++
			if (!searchStationList(stationList, passengerDestination)||passenger->ticket->isWrong) {
				wrongPassenger++;
			}
			//승객의 목적지가 해당 플랫폼 목적지에 있거나 위조표가 아니면
			else {
				//한번에 안내한 승객이면 훌륭 응대 ++
				if (checkFirstComplete(passenger)) day->greatPassenger++;
			}

			//평가 끝난 승객은 메모리 해제 (티켓 포함)
			killPassenger(passenger);
			//다음 승객 뽑아 오기
			passenger = pop(platform->passengerStack);
		}

		//다음 플랫폼으로
		currentPlatform = currentPlatform->link;

	} while (currentPlatform!=platformList->link);

	day->wrongPassenger += wrongPassenger;
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
	day->greatPassenger = 0;
	day->totalPassengerCount = 0;
	day->totalGreatCount = 0;
	day->totalWrongCount = 0;
	day->wrongDayCount = 0;
	day->ticketCount = 1;
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

//Day의 플랫폼들의 역 리스트 중 역 하나를 뽑는 함수
const char* getRandomStation(Day* day) 
{
	//임시 통합 역 리스트
	StationNode* tempList = NULL;
	//전체 역 개수
	int totalCount = 0;

	//플랫폼 리스트 하나씩 돌며
	PlatformNode* currentPlatform = day->platformList->link;
	do {
		Platform* platform = currentPlatform->data;
		StationNode* stationList = platform->stationList;

		//각 플랫폼의 역 리스트 요소를 tempList에 추가
		StationNode* currentStation = stationList->link;
		do {
			tempList = insertStationLast(tempList, currentStation->data);
			totalCount++;
			currentStation = currentStation->link;
		} while (currentStation != stationList->link);

		currentPlatform = currentPlatform->link;
	} while (currentPlatform != day->platformList->link);

	//랜덤 인덱스에 해당하는 역을 찾아서 반환
	int randomIndex = rand() % totalCount;
	StationNode* tempNode = tempList;
	for (int i = 0; i < randomIndex; i++) {
		tempNode = tempNode->link;
	}

	const char* randomStation = tempNode->data;

	//임시 리스트 메모리 해제
	while (tempList != NULL) {
		tempList = deleteStationLast(tempList);
	}

	return randomStation;
}

void settingStation()
{
	platform1 = (StationStack*)malloc(sizeof(StationStack));
	platform2 = (StationStack*)malloc(sizeof(StationStack));
	platform3 = (StationStack*)malloc(sizeof(StationStack));
	platform4 = (StationStack*)malloc(sizeof(StationStack));

	initStationStack(platform1);
	initStationStack(platform2);
	initStationStack(platform3);
	initStationStack(platform4);

	for (int i = 4; i >= 0; i--) {
		pushStation(platform1, stationNames[0][i]);
		pushStation(platform2, stationNames[1][i]);
		pushStation(platform3, stationNames[2][i]);
		pushStation(platform4, stationNames[3][i]);
	}
}

const char* getStationFromPlatform(int num) {
	switch (num) {
	case 1:
		return popStation(platform1);
		break;
	case 2:
		return popStation(platform2);
		break;
	case 3:
		return popStation(platform3);
		break;
	case 4:
		return popStation(platform4);
		break;
	default:
		return "NONE";
		break;
	}
}

DialogueQueue* createPassengerDialogue()
{
	DialogueQueue* q = (DialogueQueue*)malloc(sizeof(DialogueQueue));
	initDialogueQueue(q);

	int i = rand() % DIALOGUE_SIZE;
	enqueueDialogue(q, firstDialogue[i]);
	i = rand() % DIALOGUE_SIZE;
	enqueueDialogue(q, secondDialogue[i]);
	i = rand() % DIALOGUE_SIZE;
	enqueueDialogue(q, thirdDialogue[i]);

	return q;
}

int checkFirstComplete(Passenger* passenger)
{
	const char* target = dequeueDialogue(passenger->dialogue);

	if (target) {
		for (int i = 0; i < DIALOGUE_SIZE; i++) {
			if (strcmp(target, secondDialogue[i]) == 0) {
				return 1;
			}
		}
	}
	return 0;
}

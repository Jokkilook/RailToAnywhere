#pragma once

//사용된 자료구조
//1. 구조체
//2. 큐 (연결 리스트)
//3. 스택 (연결 리스트)

//플레이어 입력값
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27

typedef struct PassengerQueue PassengerQueue;
typedef struct PassengerStack PassengerStack;
typedef struct StationNode StationNode;
typedef struct PlatformList PlatformList;
typedef struct PlatformNode PlatformNode;

//티켓 구조체
typedef struct Ticket {
	int isWrong;
	int num;
	int subNum;
	const char* destination;
	const char* paint[6];
	const char* lastText;
}Ticket;

//승객 구조체
typedef struct Passenger {
	Ticket* ticket;
	const char* dialogue[4];
}Passenger;

//플랫폼 구조체
typedef struct Platform {
	int num;
	StationNode* stationList;
	PassengerStack* passengerStack;
}Platform;

//날짜 구조체
typedef struct Day {
	int day;
	PassengerQueue* passengerQueue;
	PlatformNode* platformList;
}Day;

//승객 노드
typedef struct PassengerNode {
	Passenger* data;
	struct PassengerNode* link;
}PassengerNode;

//역 노드
typedef struct StationNode {
	const char* data;
	struct StationNode* link;
}StationNode;

//승객 큐=====================================================================================================
typedef struct PassengerQueue {
	PassengerNode *front, *rear;
}PassengerQueue;

//큐는 malloc으로 초기 선언

//승객 큐 초기화 함수
void initQueue(PassengerQueue* q);

//승객 큐 공백 확인 함수
int isEmptyQueue(PassengerQueue *q);

//승객 큐 요소 추가 함수
void enqueue(PassengerQueue *q, Passenger* data);

//승객 큐 요소 빼기 함수
Passenger* dequeue(PassengerQueue *q);

//승객 스택=================================================================================================
typedef struct PassengerStack {
	PassengerNode *top;
}PassengerStack;

//스택은 malloc으로 초기 선언

//승객 스택 초기화
void initStack(PassengerStack* s);

//승객 스택 공백 확인 함수
int isEmptyStack(PassengerStack* s);

//승객 스택 요소 추가 함수
void push(PassengerStack* s, Passenger* data);

//승객 스택 요소 빼기 함수
Passenger* pop(PassengerStack* s);

//역 연결 리스트============================================================================================

//리스트는 NULL로 초기 선언

//역 리스트 출력
void printStationList(StationNode* head);

//역 리스트 첫번째 삽입 함수
StationNode* insertStationFirst(StationNode* head, const char* data);

//역 리스트 임의 삽입 함수
StationNode* insertStation(StationNode* head, StationNode *pre, const char* data);

//역 리스트 마지막 삽입 함수
StationNode* insertStationLast(StationNode* head, const char* data);

//역 리스트 첫번째 삭제 함수
StationNode* deleteStationFirst(StationNode* head);

//역 리스트 임의 삭제 함수
StationNode* deleteStation(StationNode* head, StationNode* pre);

//역 리스트 마지막 삭제 함수
StationNode* deleteStationLast(StationNode* head);

//역 리스트에 해당 역 검색
StationNode* searchStationList(StationNode* head, const char* data);

//플랫폼 연결 리스트========================================================================================
typedef struct PlatformNode {
	Platform* data;
	struct PlatformNode* link;
}PlatformNode;

//리스트는 NULL로 초기 선언

//플랫폼 리스트 출력
void printPlatformList(PlatformNode* head);

//플랫폼 리스트 첫번째 삽입 함수
PlatformNode* insertPlatformFirst(PlatformNode* head, Platform* data);

//플랫폼 리스트 임의 삽입 함수
PlatformNode* insertPlatform(PlatformNode* head, PlatformNode* pre, Platform* data);

//플랫폼 리스트 마지막 삽입 함수
PlatformNode* insertPlatformLast(PlatformNode* head, Platform* data);

//플랫폼 리스트 첫번째 삭제 함수
PlatformNode* deletePlatformFirst(PlatformNode* head);

//플랫폼 리스트 임의 삭제 함수
PlatformNode* deletePlatform(PlatformNode* head, PlatformNode* pre);

//플랫폼 리스트 마지막 삭제 함수
PlatformNode* deletePlatformLast(PlatformNode* head);

//플랫폼 리스트에 해당 플랫폼 검색
PlatformNode* searchPlatformList(PlatformNode* head, Platform* data);
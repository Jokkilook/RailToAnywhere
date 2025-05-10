#pragma once
#include <stdio.h>

typedef struct StationNode StationNode;
typedef struct PlatformNode PlatformNode;
typedef struct Passenger Passenger;
typedef struct Platform Platform;
typedef struct Ticket Ticket;
typedef struct Day Day;
typedef struct DialogueQueue DialogueQueue;

//커서 이동 함수
void moveCursor(int row, int col);

//배열로 저장된 아스키 아트 특정 위치 출력 함수
void printAsciiArtAtLocation(int row, int col, const char* str);

//에러 메시지 출력
void printError(const char* str);

//티켓 생성 함수
Ticket* createTicket(Day* day);

//튜토리얼용 티켓 생성 함수
Ticket createTutTicket(int isWrong);

//승객 생성 함수
Passenger* createPassenger(Day* day);

//그 날의 num번 플랫폼을 찾아 역을 추가하는 함수
void addStationToPlatform(Day* day, int num, const char* station);

//역 리스트에 역 추가하는 함수
StationNode* addStation(StationNode* list, const char* station);

//num번호의 플랫폼 만드는 함수
Platform* createPlatform(int num);

//amount명의 승객을 큐에 채우는 함수
void fillPassengerQueue(Day* day, int amount);

//플랫폼 리스트의 플랫폼 개수를 세는 함수
int countPlatformList(PlatformNode* p);

//다음날 함수
void nextDay(Day* day);

//모든 플랫폼 별 승객 스택을 검사하는 함수
void checkPlatformPassenger(Day* day);

//Day 초기화 함수
void initDay(Day* day);

//승객 메모리 청소 함수 (티켓 포함)
void killPassenger(Passenger* passenger);

//플랫폼 번호로 해당 플랫폼 2개의 역 리스트를 교환하는 함수
void exchangeStationListWithNum(PlatformNode* platformList, int num1, int num2);

//Day의 플랫폼들의 역 리스트 중 역 하나를 뽑는 함수
const char* getRandomStation(Day* day);

//역 이름 스택 초기화
void settingStation();

//해당 플랫폼에 저장된 역 이름 하나 가져오기
const char* getStationFromPlatform(int num);

//승객 다이얼로그 생성
DialogueQueue* createPassengerDialogue();

//훌륭히 응대한 승객 판단 함수
int checkFirstComplete(Passenger* passenger);
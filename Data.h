#pragma once

//사용된 자료구조
//1. 구조체 - 티켓, 승객, 플랫폼, 근무일, 승객 노드, 역 노드, 플랫폼 노드
//2. 큐 (연결 리스트) - 대기 승객 큐
//3. 스택 (연결 리스트) - 플랫폼의 승객 스택, 역 데이터 스택
//4. 원형 연결 리스트 - 플랫폼 리스트, 역 리스트
//5. 트리 - 엔딩 분기 예정...

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
	//날짜 - 1,2,3...30
	int day;
	//한 날에 잘못 응대한 승객 수
	int wrongPassenger;
	//한 날에 훌륭히 응대한 승객 수
	int greatPassenger;
	//전체 응대 승객 수
	int totalPassengerCount;
	//전체 잘못 응대한 누적 승객 수
	int totalWrongCount;
	//전체 훌륭히 응대한 누적 승객 수
	int totalGreatCount;
	//잘못 응대한 날짜 누적 - 그날 wrongPassenger가 0이면 0으로 초기화
	int wrongDayCount;
	//대기 중인 승객 수 - 응대해야할 남은 승객
	PassengerQueue* passengerQueue;
	//플랫폼 리스트
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

//큐 출력 함수
void printQueue(PassengerQueue* q);

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

//플랫폼 리스트에 플랫폼 번호로 검색
PlatformNode* searchPlatformListWithNum(PlatformNode* head, int data);

//역 스택=================================================================================================
typedef struct StationStack {
	StationNode* top;
}StationStack;

//스택은 malloc으로 초기 선언

//역 스택 초기화
void initStationStack(StationStack* s);

//역 스택 공백 확인 함수
int isEmptyStationStack(StationStack* s);

//역 스택 요소 추가 함수
void pushStation(StationStack* s, const char* data);

//역 스택 요소 빼기 함수
const char* popStation(StationStack* s);

//다이얼로그 스택 리스트 큐 뭐로하지

//데이터베이스
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
	"     00    00 '00      00 ' 00    00 'oo 0000---oo\\_",
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	},
	{
	"       _____                 , , , , , o o o o o",
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
	"   _I________I_I_________I_I________I_I__I________)<",
	"     oo    oo 'oo      oo ' oo    oo 'oo 0000---oo\\_",
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	},
	{
	"       _____                 . . . . . o o o o o",
	"     __|[_]|__ ___________ _______    ____      o",
	"    |[] [] []| [] [] [] [] [_____(__  ][]]_n_n__][.",
	"   _{________}_{_________}_{________}_|__|________)<",
	"     oo    oo 'oo      oo ' oo    oo 'oo 0000---oo\\_",
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	},
	{
	"       _____                 . . . . . o o o o o",
	"     __|[_]|__ ___________ _______    ____      o",
	"    |[] [] []| [] [] [] [] [_____(__  ][]]_n_n__][.",
	"   _|________|_[_________]_[________]_|__|________);",
	"     oo    oo 'oo      oo ' oo    oo 'oo 0000---oo\\_",
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	},
	{
	"       _____                 . . . . . o o o o o",
	"     __|[_]|__ ___________ _______    ____      o",
	"    |[] [] []| [] [] [] [] [_____(__  ][]]_n_n__][.",
	"   _|________|_[_________]_[________]_|__|________)<",
	"     oo____oo 'oo      oo ' oo    oo 'oo 0000___oo\\_",
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	}
};

static const char* wrongLastText[6] = {
	"AMYWHERE",
	"ANYWEERE",
	"ANYWHHRE",
	"ANIWHERE",
	"ANVWEHRE",
	"ANYWEHBE"
};

static const char* stationNames[4][5] = {
	{"서울","용산","안양","수원","평택"},
	{"속초","강릉","동해","기장","부산"},
	{"인천","안산","화성","서산","군산"},
	{"천안","논산","대전","대구","김해"}
};


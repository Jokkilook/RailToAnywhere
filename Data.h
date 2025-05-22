#pragma once

//사용된 자료구조
//1. 구조체 - 티켓, 승객, 플랫폼, 근무일, 승객 노드, 역 노드, 플랫폼 노드
//2. 큐 (연결 리스트) - 대기 승객 큐, 승객 다이얼로그 큐
//3. 스택 (연결 리스트) - 플랫폼의 승객 스택, 역 데이터 스택
//4. 원형 연결 리스트 - 플랫폼 리스트, 역 리스트
//5. 트리 - 피드백 분기 - 후위순회 재귀함 수 사용

//플레이어 입력값
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_TAB 9

#define DIALOGUE_SIZE 20

typedef struct PassengerQueue PassengerQueue;
typedef struct PassengerStack PassengerStack;
typedef struct StationNode StationNode;
typedef struct PlatformList PlatformList;
typedef struct PlatformNode PlatformNode;
typedef struct DialogueQueue DialogueQueue;
typedef struct FeedbackTree FeedbackTree;

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
	DialogueQueue* dialogue;
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
	//티켓 카운트 - 날이 넘어가면 0으로 초기화
	int ticketCount;
	//대기 중인 승객 수 - 응대해야할 남은 승객
	PassengerQueue* passengerQueue;
	//플랫폼 리스트
	PlatformNode* platformList;
	//피드백 트리
	FeedbackTree* feedback;
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

//다이얼로그 큐===========================================================================================
//다이얼로그 노드
typedef struct DialogueNode {
	const char* data;
	struct DialogueNode* link;
}DialogueNode;

//다이얼로그 큐
typedef struct DialogueQueue {
	DialogueNode *front, *rear;
}DialogueQueue;

//큐는 malloc으로 초기 선언

//피드백 트리=============================================================================================
typedef struct FeedbackTree {
	const char* data;
	struct FeedbackTree*good, *bad;
}FeedbackTree;

//승객 큐 초기화 함수
void initDialogueQueue(DialogueQueue* q);

//승객 큐 공백 확인 함수
int isEmptyDialogueQueue(DialogueQueue* q);

//승객 큐 요소 추가 함수
void enqueueDialogue(DialogueQueue* q, const char* data);

//승객 큐 요소 빼기 함수
const char* dequeueDialogue(DialogueQueue* q);

//큐 출력 함수
void printDialogueQueue(DialogueQueue* q);

//트리노드 생성 함수
FeedbackTree* createTreeNode(const char* data);

//피드백 초기화 함수
FeedbackTree* initAndSetTree();

//재귀 후위 순회로 하위 트리 삭제 함수
void pruneTree(FeedbackTree* root);

//데이터베이스===========================================================================================
//타이틀 아스키
static const char* title[] = {
" ____      _    ___ _       _____ ___       _    _   ___   ____        ___   _ _____ ____  _____ ",
"|  _ \\    / \\  |_ _| |     |_   _/ _ \\     / \\  | \\ | \\ \\ / /\\ \\      / / | | | ____|  _ \\| ____|",
"| |_) |  / _ \\  | || |       | || | | |   / _ \\ |  \\| |\\ V /  \\ \\ /\\ / /| |_| |  _| | |_) |  _|  ",
"|  _ <  / ___ \\ | || |___    | || |_| |  / ___ \\| |\\  | | |    \\ V  V / |  _  | |___|  _ <| |___ ",
"|_| \\_\\/_/   \\_\\___|_____|   |_| \\___/  /_/   \\_\\_| \\_| |_|     \\_/\\_/  |_| |_|_____|_| \\_\\_____|"
};

//타이틀 그림 아스키
static const char* paint[] = {
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
	{"뒤틀린 숲역","용의 척추역","침묵의 유적역","울음나무 역","잊혀진 사원역"},
	{"서울역","군자역","대전역","경주역","부산역"},
	{"발할라크로프트역","니블헬름역","룬가르드역","엘드스카르역","드라우그헤임역"},
	{"엘드라노스역","아르카디아역","노르트에인역","타오타스역","에텔브룬역"}
};

static const char* firstDialogue[DIALOGUE_SIZE] = {
	"저기요",
	"그 어디였더라~~? 아 맞다!",
	"%.4s....역....",
	"그...여기...",
	"%.5s!!!!!!!",
	"안녕하세요. 티켓 여기있습니다.",
	"아이!! 못 기다리겠네!! 내꺼 먼저 해줘!",
	"(싸가지 없는 표정)",
	"하암~~ 졸립다",
	"어...엄....",
	"빨리요 빨리!! 늦겠어요!!",
	"저기요오....%.4s.....로...",
	".....",
	"내가 어디로 가게요~?",
	"안녕히계세요.",
	"지금 몇시에요?",
	"여기 플랫폼이 어디죠?",
	"기차.",
	"%.4s에오오옹....",
	"먁-아-!",
};

static const char* secondDialogue[DIALOGUE_SIZE] = {
	"%s으로 가고 싶어요.",
	"%s으로... 갈 수 있죠?...",
	"티켓에 종착지가 안 적혀있어서... 어디로 가는 거에요?",
	"%s으로 가려고 하는데 어떻게 가야해요?",
	"%s.",
	"%s 가?",
	"그 뭐지... %s으로 가고 싶어요.",
	"%s까지 가고 싶어요.",
	"저는 %s까지 갈 건데요...",
	"%s으로 여행을 가고 싶어요!",
	".........",
	"저는 %s으로 가요.",
	"왜 티켓에 %s이라고 안 적혀있나요?",
	"몇번 플랫폼이 %s 행 기차죠?",
	"%s은 정말 아름다운 곳 일거에요...",
	"이 역이 좋나요? %s이 좋나요?",
	"%s 행 기차는 몇 시에 있죠?",
	"저기로 가면 %s 행 기차를 탈 수 있나요?",
	"%s 앞에는 택시가 있겠죠?",
	"나는 %s에서 환승할 거에요.",
};

static const char* thirdDialogue[DIALOGUE_SIZE] = {
	"%s말이에요!",
	"%s으로 간다니까요!",
	"%s입니다.",
	"%s으로 가고 싶어요.",
	"%s행 기차",
	"%s",
	"%s x100",
	".........%s....",
	"..........",
	"목적지는 %s",
	"%s으로!",
	"%s이라니까!!!!!",
	"%s!!!!",
	"%s이요.",
	"그래가지고 %s이요.",
	"??? : %s",
	"%s은 어디에~",
	"%s이란 말이에요.",
	"%s까지",
	"마지막으로 말한다. %s",
};

static const char* FeedbackList[14] = {
	"기대되는 신입이군. 훌륭하네.",
	"음... 아직 갈 길이 멀어 보이지만, 신입이니까.",
	"실력이 빠르게 느는군.",
	"\033[1;33m<전설의 역무원>\033[0m 더 배울 게 없는 역무원이야.",
	"\033[1;34m<초심을 잊지 말자>\033[0m 항상 초심을 잊지 말게나.",
	"잘하더니 좀 삐끗하네? 주의하게.",
	"\033[1;35m<되찾은 명예>\033[0m 역시 초반에 잘하더니 될성부른 떡잎이었구만.",
	"\033[1;35m<초심자의 행운>\033[0m 가끔 신입 때의 자네가 그리워.",
	"역시 하다보니 느는구만?",
	"\033[1;34m<슬로우 스타터>\033[0m 입사했을 때는 좀 불안했는데, 아주 훌륭하구만.",
	"\033[1;34m<희망?>\033[0m 실수에 자책하지 말게나. 내가 사람을 좀 볼 줄 아는데 자네는 희망이 있어!",
	"전혀 진전이 없네.",
	"\033[1;34m<새로운 희망>\033[0m 정말 다행이구만. 자네는 분명히 실력이 늘고있어.",
	"\033[1;32m<외줄타기의 신>\033[0m 자네가 아슬아슬하게 해고는 안되는 게 신기하다네."
};
#include "Draw.h"
#include "Utils.h"
#include "Data.h"

#include <windows.h>
#include <conio.h>

//문자 들어갈 네모 그리는 함수
void drawBox(int row, int col, int width, int height) {

    //윗줄
    moveCursor(row, col);
    printf("┌");
    for (int i = 0; i < width - 2; ++i) printf("─");
    printf("┐");

    //중간
    for (int i = 1; i < height - 1; ++i) {
        moveCursor(row + i, col);
        printf("│");
        for (int j = 0; j < width - 2; ++j) printf(" ");
        printf("│");
    }

    //아랫줄
    moveCursor(row + height - 1, col);
    printf("└");
    for (int i = 0; i < width - 2; ++i) printf("─");
    printf("┘");

}

//특정 위치에 메시지 출력 후 ENTER 입력 대기
void printStoryAndWait(int row, int col, const char* str) {
    moveCursor(row, col);
    printf("%s", str);

    while (1) {
        int key = _getch();

        if (key == KEY_ENTER) break;
    }
}

//티켓 그리는 함수
void drawTicket(Ticket ticket, int highlight) {
	
    //티켓 박스 그리기
    drawBox(3, 0, 100, 14);
    
    if(highlight) printf("\033[1;31m");

    //티켓 번호 쓰기
    moveCursor(4, 6);
    printf("No.%03d", ticket.num);
    moveCursor(4, 93);
    printf("%03d", ticket.subNum);

    //티켓 그림 출력
    for (int i = 0; i < sizeof(ticket.paint) / sizeof(ticket.paint[0]); ++i) {
        printAsciiArtAtLocation(8 + i, 24, ticket.paint[i]);
    }
    
    //티켓 하단 문자 출력
    moveCursor(15, 6);
    printf("%s", ticket.lastText);

    //디버그용 출력
    //printf("  %s", ticket.destination);
    //printf("%d", ticket.isWrong);

    printf("\033[0m");

    //티켓 발행처 쓰기
    moveCursor(6, 39);
    printf("ISSUED BY SMU STATION");
}

//메인 메뉴 그리는 함수
void drawMainMenu() {

    //타이틀 아스키
    const char* title[] = {
    " ____      _    ___ _       _____ ___       _    _   ___   ____        ___   _ _____ ____  _____ ",
    "|  _ \\    / \\  |_ _| |     |_   _/ _ \\     / \\  | \\ | \\ \\ / /\\ \\      / / | | | ____|  _ \\| ____|",
    "| |_) |  / _ \\  | || |       | || | | |   / _ \\ |  \\| |\\ V /  \\ \\ /\\ / /| |_| |  _| | |_) |  _|  ",
    "|  _ <  / ___ \\ | || |___    | || |_| |  / ___ \\| |\\  | | |    \\ V  V / |  _  | |___|  _ <| |___ ",
    "|_| \\_\\/_/   \\_\\___|_____|   |_| \\___/  /_/   \\_\\_| \\_| |_|     \\_/\\_/  |_| |_|_____|_| \\_\\_____|"
    };

    //타이틀 그림 아스키
    const char* paint[] = {
        "       _____                 . . . . . o o o o o",
        "     __|[_]|__ ___________ _______    ____      o",
        "    |[] [] []| [] [] [] [] [_____(__  ][]]_n_n__][.",
        "   _|________|_[_________]_[________]_|__|________)<",
        "     oo    oo 'oo      oo ' oo    oo 'oo 0000---oo\\_",
        "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    };

    const char* menus[] = {
    "게임 시작",
    "게임 정보",
    "종료"
    };

    int menu = 1;
    int menuCount = 3;
    int selected = 0;

    while (menu) {
        system("cls");

        //로고 타이틀 그리기
        for (int i = 0; i < sizeof(title) / sizeof(title[0]); ++i) {
            printAsciiArtAtLocation(4 + i, 10, title[i]);
        }

        //로고 그림 그리기
        for (int i = 0; i < sizeof(paint) / sizeof(paint[0]); ++i) {
            printAsciiArtAtLocation(11 + i, 30, paint[i]);
        }

        //메뉴 박스 출력
        drawBox(20, 50, 15, 7);

        //메뉴 출력
        for (int i = 0; i < 3; ++i) {
            moveCursor(22 + i, 51);
            if (i == selected)
                printf("\033[01m > %s\033[0m\n", menus[i]);
            else if (i == menuCount - 1)
                printf("   %s", menus[i]);
            else
                printf("   %s\n", menus[i]);
        }

        moveCursor(25, 0);

        int key = _getch();

        if (key == 0 || key == 224) {
            key = _getch();
            switch (key) {
            case KEY_UP:
                selected = (selected - 1 + menuCount) % menuCount;
                break;
            case KEY_DOWN:
                selected = (selected + 1) % menuCount;
                break;
            }
        }
        else if (key == KEY_ENTER) {
            switch (selected) {
            case 0:
                drawGame();
                break;
            case 1:
                printf("게임 정보");
                break;
            case 2:
                menu = 0;
                break;
            }
        }
    }
}

//게임 진행 그리는 함수
void drawGame() {

    int isPlay = 1;
    int selected = 0;
    int optionsSize;
    int dialogueIndex = 0;
    int tutComplete = 0;

    //역 이름 세팅
    settingStation();

    //날 데이터 생성
    Day day;
    initDay(&day);

    //기본 플랫폼 2개 추가
    addStationToPlatform(&day, 1, getStationFromPlatform(1));
    addStationToPlatform(&day, 2, getStationFromPlatform(2));

    //처음 승객 5명 채우기
    fillPassengerQueue(&day, 5);

    //현재 승객
    Passenger* passenger;
    passenger = dequeue(day.passengerQueue);

    while (isPlay) {

        //튜토리얼 시작
        if (!tutComplete) {
            drawTutorial();
            tutComplete = 1;

            drawPlatformState(&day);
        }

        //화면 초기화
        system("cls");

        //날짜 표시
        moveCursor(0, 2);
        printf("DAY %d", day.day);

        //티켓 그리기
        drawTicket(*passenger->ticket, 0);

        //승객 다이얼로그 출력
        moveCursor(18, 2);
        printf(passenger->dialogue[dialogueIndex], passenger->ticket->destination);

        //선택지 출력
        optionsSize = countPlatformList(day.platformList);
        moveCursor(26, 0);
        PlatformNode* p = day.platformList->link;
        do {
            if (p->data->num - 1 == selected)
                printf("\033[01m > %d번 플랫폼\033[0m", p->data->num);
            else
                printf("   %d번 플랫폼", p->data->num);
            p = p->link;
        } while (p != day.platformList->link);

        //되묻기 출력
        if (selected == optionsSize)
            printf(" > 네?");
        else
            printf("   네?");
        
        //경찰서 출력
        moveCursor(28, 0);
        if (selected > optionsSize || selected < 0)
            printf("\033[01m > ☎  경찰서\033[0m");
        else
            printf("   ☎  경찰서");

        //디버그 출력
        moveCursor(0, 10);
        printf("남은 승객 : ");
        printQueue(day.passengerQueue);
        //moveCursor(1, 10);
        //printf("PQ ADDRESS: %p\n", (void*)day.passengerQueue);
        //moveCursor(30, 0);
        //printf("SELECTED : %d\n", selected);
        //printf("1 : %d\n", day.platformList->link->data->num);
        //printf("2 : %d\n", day.platformList->link->link->data->num);
        //printf("3 : %d\n", day.platformList->link->link->link->data->num);
        //printf("4 : %d\n", day.platformList->link->link->link->link->data->num);
        //printPlatformList(day.platformList);

        //플레이어 입력 받기
        int key = _getch();

        //방향기 좌우 입력 시
        if (key == 0 || key == 224) {
            key = _getch();
            switch (key) {
            case KEY_LEFT:
                selected = (selected - 1 + optionsSize+1) % (optionsSize+1);
                break;
            case KEY_RIGHT:
                selected = (selected + 1) % (optionsSize+1);
                break;
            case KEY_UP:
            case KEY_DOWN:
                selected = selected > optionsSize ? 0 : 100;
                break;
            }
        }
        //엔터 입력 시
        else if (key == KEY_ENTER) {
            //선택지의 따라
            switch (selected) {
            //1번째 선택지
            case 0: {
                //승객을 첫번째 플랫폼으로 보냄
                PassengerStack* p1ps = day.platformList->link->data->passengerStack;
                push(p1ps, passenger);
                break;
            }
            //2번째 선택지
            case 1: {
                //승객을 두번째 플랫폼으로 보냄
                PassengerStack* p2ps = day.platformList->link->link->data->passengerStack;
                push(p2ps, passenger);
                break;
            }
            //3번째 선택지
            case 2: {
                PassengerStack* p3ps = day.platformList->link->link->link->data->passengerStack;
                //플랫폼 3개 이상일 때
                if (countPlatformList(day.platformList) >= 3) {
                    //승객을 세번째 플랫폼으로 보냄
                    push(p3ps, passenger);
                }
                //플랫폼이 2개고 3번째가 네? 일 때
                else {
                    //다음 다이얼로그로 이동
                    dialogueIndex++;
                    //다음 다이얼로그가 없으면 승객 빡쳐서 감
                    if (dialogueIndex >= 4) {
                        //잘못 응대 ++
                        day.wrongPassenger++;
                        //승객 데이터 없애고
                        killPassenger(passenger);
                        //다이얼로그 인덱스 초기화
                        dialogueIndex = 0;
                    }
                    //다음 다이얼로그가 있으면 다음거로
                    else continue;
                }
                break;
            }
            //4번째 선택지
            case 3: {
                PassengerStack* p4ps = day.platformList->link->link->link->link->data->passengerStack;
                //플랫폼 4개 이상일 때
                if (countPlatformList(day.platformList) >= 4) {
                    //승객을 네번째 플랫폼으로 보냄
                    push(p4ps, passenger);
                }
                //플랫폼이 3개고 4번째가 네? 일 때
                else {
                    //다음 다이얼로그로 이동
                    dialogueIndex++;
                    //다음 다이얼로그가 없으면 승객 빡쳐서 감
                    if (dialogueIndex >= 4) {
                        //잘못 응대 ++
                        day.wrongPassenger++;
                        //승객 데이터 없애고
                        killPassenger(passenger);
                        //다이얼로그 인덱스 초기화
                        dialogueIndex = 0;
                    }
                    //다음 다이얼로그가 있으면 다음거로
                    else continue;
                }
                break;
            }
            default:
                //경찰서 신고 (위조 티켓)
                if (passenger->ticket->isWrong) {
                }
                //위조 티켓아닌데 신고한거면
                else {
                    day.wrongPassenger++;
                }
                killPassenger(passenger);
                break;
            }

            //선택 초기화
            selected = 0;
            //다이얼로그 인덱스 초기화
            dialogueIndex = 0;

            //선택 후 메시지 출력
            //예정

            //승객 큐가 비었으면
            if (isEmptyQueue(day.passengerQueue)) {
                //모든 플랫폼 별 승객 검사
                checkPlatformPassenger(&day);

                //승객 카운트
                day.totalGreatCount += day.greatPassenger;
                day.totalWrongCount += day.wrongPassenger;
                if (day.wrongPassenger > 0) day.wrongDayCount++;
                else day.wrongDayCount = 0;

                //Day 통계 화면 출력
                drawDayOver(day, &isPlay);

                //잘못 응대 승객 수 - 훌륭 응대 승객 수가 3 이상이면 게임 종료
                if (day.wrongPassenger - day.greatPassenger >= 3) break;

                //마지막 근무일(30)이 아니면
                if (day.day != 30) {
                    //다음 날 시퀀스 작동
                    nextDay(&day);
                    //플랫폼 현황 화면 출력
                    drawPlatformState(&day);
                }
                else {
                    //게임 종료 시퀀스 작동
                    drawEnding(&day);
                    break;
                }
            }

            //다음 승객 빼오기
            passenger = dequeue(day.passengerQueue);
        }        
        //ESC 입력 시
        else if (key == KEY_ESC) {
            drawPause(&isPlay);
        }
    }   
}

//Day 넘어가기 전 통계 화면
void drawDayOver(Day day, int* isPlay) {
    //화면 초기화
    system("cls");
    
    //통계 박스 그리기
    drawBox(2, 0, 110, 20);

    //날짜 표시
    moveCursor(5, 53);
    printf("DAY %2d", day.day);

    //잘 못 응대한 승객 수 표시
    moveCursor(8, 44);
    printf("잘못 응대한 승객 수 : %2d", day.wrongPassenger);

    //첫날엔 훌륭 승객 수 출력 안함
    if (day.day != 1) {
        moveCursor(9, 42);
        printf("훌륭하게 응대한 승객 수 : %2d", day.greatPassenger);
    }

    //첫날엔 아묻따 칭찬
    if (day.day == 1) {
        moveCursor(13, 43);
        printf("수고했네! 아주 잘 하고 있어");
    }
    //둘째날에 3번 실수하면 해고할 수 있다고 알려줌
    else if (day.day == 2) {
        moveCursor(13, 17);
        printf("내가 그거 말했나? 하루에 실수가 3번을 넘거나 연속 3일로 실수가 한번이라도 있으면");
        moveCursor(15, 49);
        printf("\033[1;31m자넨 해고야!\033[0m");
        moveCursor(17, 30);
        printf("하지만, 그만큼 훌륭하게 응대한 손님이 있다면 봐줄지도.");
    }

    //잘못 응대 - 훌륭 응대 가 3초과(4이상)이면 해고
    if (day.wrongPassenger - day.greatPassenger > 3) {
        moveCursor(13, 40);
        printf("시간 낭비한 손님이 몇명인가!!");
        moveCursor(15, 49);
        printf("\033[1;31m자넨 해고야!\033[0m");
    }
    else if (day.wrongDayCount >= 3){
        moveCursor(13, 46);
        printf("3일 연속 실수라니!!");
        moveCursor(15, 49);
        printf("\033[1;31m자넨 해고야!\033[0m");
    }

    //다음날 메시지 출력
    moveCursor(26, 48);
    printf("> %s", day.wrongPassenger - day.greatPassenger >= 3 ? "타이틀로" : "다음날로");

    int key = _getch();
}

//일시 정지 화면
void drawPause(int* isPlay)
{
    const char* title[] = {
      "  _____          __  __ ______   _____       _    _  _____ ______ ",
      " / ____|   /\\   |  \\/  |  ____| |  __ \\ /\\  | |  | |/ ____|  ____|",
      "| |  __   /  \\  | \\  / | |__    | |__) /  \\ | |  | | (___ | |__   ",
      "| | |_ | / /\\ \\ | |\\/| |  __|   |  ___/ /\\ \\| |  | |\\___ \\|  __|  ",
      "| |__| |/ ____ \\| |  | | |____  | |  / ____ \\ |__| |____) | |____ ",
      " \\_____/_/    \\_\\_|  |_|______| |_| /_/    \\_\\____/|_____/|______|"
    };

    int isPause = 1;
    int selected = 0;
    int menuCount = 2;

    const char* menus[] = {
    "돌아가기",
    "종료",
    };


    while (isPause) {
        system("cls");

        //PAUSE 타이틀 그리기
        for (int i = 0; i < sizeof(title) / sizeof(title[0]); ++i) {
            printAsciiArtAtLocation(4 + i, 25, title[i]);
        }

        //안내 메시지
        moveCursor(15, 37);
        printf("지금 종료하면 모든 진행 상황을 잃게됩니다!");

        //메뉴 박스 출력
        drawBox(20, 50, 15, 6);

        //메뉴 출력
        for (int i = 0; i < 2; ++i) {
            moveCursor(22 + i, 51);
            if (i == selected)
                printf("\033[01m > %s\033[0m\n", menus[i]);
            else if (i == menuCount - 1)
                printf("   %s", menus[i]);
            else
                printf("   %s\n", menus[i]);
        }

        //플레이어 입력 받기
        int key = _getch();

        if (key == KEY_ESC) {
            isPause = 0;
        }

        //방향기 좌우 입력 시
        if (key == 0 || key == 224) {
            key = _getch();
            switch (key) {
                case KEY_UP:
                    selected = (selected + 1) % menuCount;
                    break;
                case KEY_DOWN:
                    selected = (selected - 1 + menuCount) % menuCount;
                    break;
            }
        }
        //엔터 입력 시
        else if (key == KEY_ENTER) {
            switch (selected) {
            case 0:
                isPause = 0;
                break;
            case 1:
                *isPlay = 0;
                isPause = 0;
                break;
            }
        }
    }
}

//플랫폼 현황 화면
void drawPlatformState(Day* day)
{
    //화면 초기화
    system("cls");

    //박스 그리기
    drawBox(2, 0, 110, 20);

    //플랫폼 현황판 타이틀 출력
    moveCursor(5, 45);
    printf("★ 플랫폼 별 노선도 ★");

    //현재 플랫폼 출력
    PlatformNode* current = day->platformList->link;
    int index = 0;
    do {
        Platform* platform = current->data;

        moveCursor(8 + index*3, 25);
        printf("%d번 플랫폼 : ", platform->num);
        printStationList(platform->stationList);

        current = current->link;
        index++;
    } while (current != day->platformList->link);

    //1일째
    if (day->day == 1) {
        moveCursor(19, 25);
        printf("우리역의 플랫폼 별 노선도네! 잘 숙지하는 게 좋을거야");
    }
    //2~3일째
    else if (1 < day->day && day->day <= 3) {
        moveCursor(19, 25);
        printf("두 플랫폼의 역이 확장 되었네! 자네는 고생 좀 하겠어");
    }
    //7일째
    else if (day->day == 7) {
        moveCursor(19, 25);
        printf("플랫폼 확장 공사를 했다네! 일이 더 힘들어지겠군");
    }
    //7~9일째
    else if (7 < day->day && day->day <= 9) {
        moveCursor(19, 25);
        printf("두 플랫폼의 역이 확장 되었네! 역이 점점 성장하는군!");
    }
    //14일째
    else if (day->day == 14) {
        moveCursor(19, 25);
        printf("플랫폼 확장 공사를 했다네! 이번이 마지막이니 걱정 말게나!");
    }
    //14~16일째
    else if (14 < day->day && day->day <= 16) {
        moveCursor(19, 25);
        printf("새로운 플랫폼의 역이 확장 되었네! 조금 더 힘내주게");
    }
    //21일째
    else if (day->day == 21) {
        moveCursor(19, 25);
        printf("플랫폼의 들어오는 열차가 서로 바뀌었네! 잘 확인해보게나");
    }
    //24일째
    else if (day->day == 24) {
        moveCursor(19, 25);
        printf("플랫폼의 들어오는 열차가 다시 한번 바뀌었어! 실수하지 않도록 주의하게");
    }
    //30일째
    else if (day->day == 30) {
        moveCursor(19, 25);
        printf("열차가 다시 바뀌었다지 뭔가... 끝까지 잘해보세!");
    }
    
    //다음날 메시지 출력
    moveCursor(26, 48);
    printf("> 근무 시작");

    int key = _getch();
}

//엔딩 화면
void drawEnding(Day* day)
{
    system("cls");

    //통계 박스 그리기
    drawBox(2, 0, 110, 20);

    //날짜 표시
    moveCursor(5, 53);
    printf("DAY %2d", day->day);
    
    moveCursor(7, 48);
    printf("한 달 근무 결과");
    moveCursor(9, 44);
    printf("총 응대한 승객 수 : %2d", day->totalPassengerCount);
    moveCursor(10, 44);
    printf("잘못 응대한 승객 수 : %2d", day->totalWrongCount);
    moveCursor(11, 42);
    printf("훌륭하게 응대한 승객 수 : %2d", day->totalGreatCount);

    moveCursor(14, 38);
    if (day->totalGreatCount == 0 && day->totalWrongCount == 0) {
        printf("완벽하게 승객을 응대했군! 아주 훌륭해!");
    }
    else if (day->totalWrongCount > 0 && (day->totalWrongCount - day->totalGreatCount < 4)) {
        printf("이 정도면 완벽하진 않지만, 훌륭하네!");
    }
    moveCursor(16, 35);
    printf("앞으로는 내 도움 없이도 잘할 수 있을 거야.");
    moveCursor(18, 37);
    printf("이제는 자네만의 선로를 개척해 보게나!");

    //타이틀로 메시지 출력
    moveCursor(26, 48);
    printf("> 타이틀로");

    int key = _getch();
}

void drawTutorial()
{
    int isTutorial = 1;
    int selected = 0;
    int duringPlatform = 0;
    int police = 0;
    int duringPolice = 0;
    int policeNotice = 0;
    int completePolice = 0;


    while (isTutorial) {
        //화면 초기화
        system("cls");

        //날짜 표시
        moveCursor(0, 2);
        printf("수습 기간");

        //티켓 발행
        Ticket t;
        Ticket wt;
        t = createTutTicket(0);
        wt = createTutTicket(1);

        //티켓 그리기
        drawTicket(t, 0);

       //안내 메시지 출력
        if (!completePolice) {
            if (!police) {
                if (!duringPlatform) {
                    moveCursor(18, 2);
                    printf("어서오게! 여기가 자네가 일하게 될 역이라네.");
                    _getch();
                    moveCursor(20, 2);
                    printf("우리 기차는 표만 있으면 어디든 갈 수 있지. 하지만 표에 어느 플랫폼인지가 안 써있네. 다 자네한테 물어보러 온다고.");
                    _getch();
                    moveCursor(22, 2);
                    printf("자네가 할 일은 승객의 티켓을 확인하고 플랫폼을 안내해주는 일이네!");
                    _getch();
                    moveCursor(24, 2);
                    printf("여기 이 손님은 %s에 가고싶어 하는군. %s은 \033[1;31m1번 플랫폼\033[0m이네 그 곳으로 안내해드리게", t.destination, t.destination);
                    _getch();
                }
                else {
                    moveCursor(18, 2);
                    printf("어서오게! 여기가 자네가 일하게 될 역이라네.");
                    moveCursor(20, 2);
                    printf("자네가 할 일은 승객의 티켓을 확인하고 플랫폼을 안내해주는 일이네!");
                    moveCursor(22, 2);
                    printf("여기 이 손님은 %s에 가고싶어 하는군. %s은 \033[1;31m1번 플랫폼\033[0m이네 그 곳으로 안내해드리게",t.destination, t.destination);
                }
            }
            else {
                if (!duringPolice) {
                    duringPolice = 1;
                    selected = 100;
                    moveCursor(18, 2);
                    printf("잘했네! 이렇게 플랫폼의 역을 확인하고 승객을 안내해주면 되네");
                    _getch();
                    moveCursor(20, 2);
                    printf("하지만 표가 있다고 아무나 받아서는 안되네. \033[1;31m위조표\033[0m를 들고오는 범죄자도 있기 때문이지. 지금 표가 정상표지만..");
                    _getch();
                    drawTicket(wt, 1);
                    moveCursor(22, 2);
                    printf("만약 지금 보여주는 표처럼 어딘가 이상한 표라면 경찰서에 연락을 해야하네!");
                    moveCursor(23, 2);
                    printf("\033[1;32m※ 위조표는 표의 순서가 다르거나, 상단 오른쪽 왼쪽 숫자가 다르거나, 그림이 이상하거나, 좌측 하단 문자가 이상합니다. ※\033[0m");
                    _getch();
                }
                else {
                    drawTicket(wt, 1);
                    moveCursor(18, 2);
                    printf("잘했네! 이렇게 플랫폼의 역을 확인하고 승객을 안내해주면 되네");
                    moveCursor(20, 2);
                    printf("하지만 표가 있다고 아무나 받아서는 안되네. \033[1;31m위조표\033[0m를 들고오는 범죄자도 있기 때문이지. 지금 표가 정상표지만..");
                    moveCursor(22, 2);
                    printf("만약 지금 보여주는 표처럼 어딘가 이상한 표라면 경찰서에 연락을 해야하네!");
                    moveCursor(23, 2);
                    printf("\033[1;32m※ 위조표는 표의 순서가 다르거나, 오른쪽 왼쪽 숫자가 다르거나, 그림이 이상하거나, 좌측 하단 문자가 이상합니다. ※\033[0m");
                    if (policeNotice) {
                        moveCursor(24, 2);
                        printf("플랫폼을 안내하는 게 아니라, \033[1;31m경찰서\033[0m에 전화해야 하네!");
                    }
                }
            }
        }
        else {
            moveCursor(18, 2);
            printf("일을 잘 이해하는 군! 앞으로의 모습이 기대되네");
            _getch();
            moveCursor(20, 2);
            printf("앞으로도 승객의 말을 잘 듣고 정확히 안내해주길 바라네");
            _getch();
            moveCursor(22, 2);
            printf("위조표가 아닌 정상표를 다시 한번 보여주겠네!");
            _getch();
            moveCursor(24, 2);
            printf("위조표를 들고오는 범죄자는 즉시 경찰서에 연락하게!");
            _getch();
            break;
        }

        //선택지 출력
        moveCursor(26, 0);
        if (selected == 0)
            printf(" > 1번 플랫폼");
        else
            printf("   1번 플랫폼");

        //경찰서 출력
        if (police) {
            moveCursor(28, 0);
            if (selected > 0 || selected < 0)
                printf("\033[01m > ☎  경찰서\033[0m");
            else
                printf("   ☎  경찰서");
        }

        //플레이어 입력 받기
        int key = _getch();

        //방향기 좌우 입력 시
        if (key == 0 || key == 224) {
            key = _getch();
            switch (key) {
            case KEY_LEFT:
            case KEY_RIGHT:
                selected = 0;
                break;
            case KEY_UP:
            case KEY_DOWN:
                selected = selected > 0 ? 0 : 100;
                break;
            }
        }
        //엔터 입력 시
        else if (key == KEY_ENTER) {
            switch (selected) {
            case 0: {
                police = 1;
                if (duringPolice) policeNotice = 1;
                break;
            }
            default:
                if (duringPolice) completePolice = 1;
                break;
            }

        }
    }
}

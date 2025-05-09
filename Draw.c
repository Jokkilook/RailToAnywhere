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
void drawTicket(Ticket ticket) {
	
    //티켓 박스 그리기
    drawBox(3, 0, 100, 14);

    //티켓 번호 쓰기
    moveCursor(4, 6);
    printf("No.%03d", ticket.num);
    moveCursor(4, 96);
    printf("%03d", ticket.subNum);

    //티켓 발행처 쓰기
    moveCursor(7, 40);
    printf("ISSUED BY SMU STATION");

    //티켓 그림 출력
    for (int i = 0; i < sizeof(ticket.paint) / sizeof(ticket.paint[0]); ++i) {
        printAsciiArtAtLocation(8 + i, 25, ticket.paint[i]);
    }

    //티켓 그림 반전 출력
    //for (int i = sizeof(ticket.paint) / sizeof(ticket.paint[0]); i > 0; --i) {
    //    printAsciiArtAtLocation(i + 2, 25, ticket.paint[i]);
    //}
    
    //티켓 하단 문자 출력
    moveCursor(15, 6);
    printf("%s", ticket.lastText);
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

    //날 데이터 생성
    Day day;
    initDay(&day);

    addStationToPlatform(&day, 2, "멧돼지");
    addStationToPlatform(&day, 1, "고라니");

    fillPassengerQueue(&day, 5);

    //현재 승객
    Passenger* passenger;
    passenger = dequeue(day.passengerQueue);

    drawPlatformState(&day);

    while (isPlay) {

        //화면 초기화
        system("cls");

        //날짜 표시
        moveCursor(0, 2);
        printf("DAY %d", day.day);

        //티켓 그리기
        drawTicket(*passenger->ticket);

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
                selected = (selected - 1 + optionsSize) % optionsSize;
                break;
            case KEY_RIGHT:
                selected = (selected + 1) % optionsSize;
                break;
            case KEY_UP:
            case KEY_DOWN:
                selected = selected > optionsSize ? 0 : 100;
                break;
            }
        }
        //엔터 입력 시
        else if (key == KEY_ENTER) {
            switch (selected) {
            case 0:
                push(day.platformList->link->data->passengerStack, passenger);
                break;
            case 1:
                push(day.platformList->link->link->data->passengerStack, passenger);
                break;
            case 2:
                push(day.platformList->link->link->link->data->passengerStack, passenger);
                break;
            case 3:
                push(day.platformList->link->link->link->link->data->passengerStack, passenger);
                break;
            default:

                break;
            }

            selected = 0;

            //승객 큐가 비었으면
            if (isEmptyQueue(day.passengerQueue)) {
                //모든 플랫폼 별 승객 검사
                checkPlatformPassenger(&day);
                //Day 통계 화면 출력
                drawDayOver(day);
                //마지막 근무일(30)이 아니면
                if (day.day != 30) {
                    //다음 날 시퀀스 작동
                    nextDay(&day);
                    //플랫폼 현황 화면 출력
                    drawPlatformState(&day);
                }
                else {
                    //게임 종료 시퀀스 작동
                    drawEnding(&day, &isPlay);
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
void drawDayOver(Day day) {
    //화면 초기화
    system("cls");
    
    //통계 박스 그리기
    drawBox(2, 0, 110, 20);

    //날짜 표시
    moveCursor(5, 53);
    printf("DAY %2d", day.day);

    //잘 못 응대한 승객 수 표시
    moveCursor(15, 30);
    printf("잘 못 응대한 승객 수 : %d", day.wrongPassenger);

    //다음날 메시지 출력
    moveCursor(26, 51);
    printf("> 다음날로");

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
    

    //다음날 메시지 출력
    moveCursor(26, 30);
    printf("> 근무 시작");

    int key = _getch();
}

//엔딩 화면
void drawEnding(Day* day, int* isPlay)
{
    system("cls");
    printf("수고했네");
    int key = _getch();

    *isPlay = 0;
}

#pragma once


typedef struct Ticket Ticket;
typedef struct Day Day;
//문자 들어갈 네모 그리는 함수
void drawBox(int row, int col, int width, int height);

//특정 위치에 메시지 출력 후 ENTER 입력 대기
void printStoryAndWait(int row, int col, const char* str);

//티켓 그리는 함수
void drawTicket(Ticket ticket);

//메인 메뉴 그리는 함수
void drawMainMenu();

//게임 진행 그리는 함수
void drawGame();

//Day 넘어가기 전 통계 화면
void drawDayOver(Day day);

//일시 정지 화면
void drawPause(int* isPlay);
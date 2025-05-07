#include "Data.h"
#include <stdlib.h>
#include <stdio.h>

//승객 큐 초기화 함수
void initQueue(PassengerQueue* q)
{
	q->front = NULL;
	q->rear = NULL;
}

//승객 큐 공백 확인 함수
int isEmptyQueue(PassengerQueue *q) {
	if (q->front == NULL && q->rear == NULL) return 1;
	
	return 0;
}

//승객 큐 요소 추가 함수
void enqueue(PassengerQueue *q, Passenger* data) {
	PassengerNode* temp = (PassengerNode *)malloc(sizeof(PassengerNode));
	temp->data = data;
	temp->link = NULL;

	if (isEmptyQueue(q)) {
		q->front = temp;
		q->rear = temp;
	}
	else {
		q->rear->link = temp;
		q->rear = temp;
	}
}

//승객 큐 요소 빼기 함수
Passenger* dequeue(PassengerQueue *q)
{
	PassengerNode* temp = q->front;
	Passenger* data;
	if (isEmptyQueue(q)) {
		exit(1);
	}
	else {
		data = temp->data;
		q->front = q->front->link;
		if (q->front == NULL)
			q->rear = NULL;
		free(temp);
		return data;
	}
}

//승객 스택 초기화
void initStack(PassengerStack* s)
{
	s->top = NULL;
}

//승객 스택 공백 확인 함수
int isEmptyStack(PassengerStack* s)
{
	if (s->top == NULL) return 1;
	return 0;
}

//승객 스택 요소 추가 함수
void push(PassengerStack* s, Passenger* data)
{
	PassengerNode* temp = (PassengerNode *)malloc(sizeof(PassengerNode));
	temp->data = data;
	temp->link = s->top;
	s->top = temp;
}

//승객 스택 요소 빼기 함수
Passenger* pop(PassengerStack* s)
{
	if (isEmptyStack(s)) {
		exit(1);
	}
	else {
		PassengerNode* temp = s->top;
		Passenger* data = temp->data;
		s->top = s->top->link;
		free(temp);
		return data;
	}
}

//역 리스트 출력
void printStationList(StationNode* head)
{
	StationNode* p;
	if (head == NULL) {
		printf("NULL");
		return;
	}
	p = head->link;
	do {
		printf("%s -> ", p->data);
		p = p->link;
	} while (p != head->link);
}

//역 리스트 첫번째 삽입 함수
StationNode* insertStationFirst(StationNode* head, const char* data)
{	
	StationNode* node = (StationNode*)malloc(sizeof(StationNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;
		head->link = node;
	}
	return head;
}

//역 리스트 임의 삽입 함수
StationNode* insertStation(StationNode* head, StationNode* pre, const char* data)
{
	StationNode* node = (StationNode*)malloc(sizeof(StationNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else if (pre == head) {
		node->link = pre->link;
		pre->link = node;
		head = node;
	}
	else
	{
		node->link = pre->link;
		pre->link = node;
	}
	return head;
}

//역 리스트 마지막 삽입 함수
StationNode* insertStationLast(StationNode* head, const char* data)
{
	StationNode* node = (StationNode*)malloc(sizeof(StationNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;
		head->link = node;
		head = node;
	}
	return head;
}

//역 리스트 첫번째 삭제 함수
StationNode* deleteStationFirst(StationNode* head)
{
	if (head == NULL)
		return NULL;
	if (head->link == head) {
		free(head);
		head = NULL;
	}
	else {
		StationNode* removed = head->link;
		head->link = removed->link;
		free(removed);
	}
	return head;
}

//역 리스트 임의 삭제 함수
StationNode* deleteStation(StationNode* head, StationNode* pre)
{
	StationNode* removed;
	if (head == NULL)
		return NULL;
	if (pre->link == pre) {
		free(pre);
		head = NULL;
	}
	else {
		if (pre->link == head)
			head = pre;
		removed = pre->link;
		pre->link = removed->link;
		free(removed);
	}
	return head;

}

//역 리스트 마지막 삭제 함수
StationNode* deleteStationLast(StationNode* head)
{
	StationNode* removed, * pre;
	if (head == NULL)
		return NULL;
	if (head == head->link) {
		removed = head;
		head = NULL;
	}
	else {
		pre = head->link;
		while (pre->link != head)
			pre = pre->link;
		removed = head;
		pre->link = head->link;
		head = pre;
	}
	free(removed);
	return head;
}

//역 리스트에 해당 역 검색
StationNode* searchStationList(StationNode* head, const char* data)
{
	if (head == NULL) return NULL;

	StationNode* node = head->link;
	do {
		if (node->data == data) {
			return node;
		}
		node = node->link;
	} while (node != head->link);

	return NULL;
}


//플랫폼 리스트 출력
void printPlatformList(PlatformNode* head)
{
	PlatformNode* p;
	if (head == NULL) {
		printf("NULL");
		return;
	}
	p = head->link;
	do {
		printf("%d -> ", p->data->num);
		p = p->link;
	} while (p != head->link);
}

//플랫폼 리스트 첫번째 삽입 함수
PlatformNode* insertPlatformFirst(PlatformNode* head, Platform* data)
{
	PlatformNode* node = (PlatformNode*)malloc(sizeof(PlatformNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;
		head->link = node;
	}
	return head;
}

//플랫폼 리스트 임의 삽입 함수
PlatformNode* insertPlatform(PlatformNode* head, PlatformNode* pre, Platform* data)
{
	PlatformNode* node = (PlatformNode*)malloc(sizeof(PlatformNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else if (pre == head) {
		node->link = pre->link;
		pre->link = node;
		head = node;
	}
	else
	{
		node->link = pre->link;
		pre->link = node;
	}
	return head;
}

//플랫폼 리스트 마지막 삽입 함수
PlatformNode* insertPlatformLast(PlatformNode* head, Platform* data)
{
	PlatformNode* node = (PlatformNode*)malloc(sizeof(PlatformNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;
		head->link = node;
		head = node;
	}
	return head;
}

//플랫폼 리스트 첫번째 삭제 함수
PlatformNode* deletePlatformFirst(PlatformNode* head)
{
	if (head == NULL)
		return NULL;
	if (head->link == head) {
		free(head);
		head = NULL;
	}
	else {
		PlatformNode* removed = head->link;
		head->link = removed->link;
		free(removed);
	}
	return head;
}

//플랫폼 리스트 임의 삭제 함수
PlatformNode* deletePlatform(PlatformNode* head, PlatformNode* pre)
{
	PlatformNode* removed;
	if (head == NULL)
		return NULL;
	if (pre->link == pre) {
		free(pre);
		head = NULL;
	}
	else {
		if (pre->link == head)
			head = pre;
		removed = pre->link;
		pre->link = removed->link;
		free(removed);
	}
	return head;

}

//플랫폼 리스트 마지막 삭제 함수
PlatformNode* deletePlatformLast(PlatformNode* head)
{
	PlatformNode* removed, * pre;
	if (head == NULL)
		return NULL;
	if (head == head->link) {
		removed = head;
		head = NULL;
	}
	else {
		pre = head->link;
		while (pre->link != head)
			pre = pre->link;
		removed = head;
		pre->link = head->link;
		head = pre;
	}
	free(removed);
	return head;
}

//플랫폼 리스트에 해당 역 검색
PlatformNode* searchPlatformList(PlatformNode* head, Platform* data)
{
	if (head == NULL) return NULL;

	PlatformNode* node = head->link;
	do {
		if (node->data == data) {
			return node;
		}
		node = node->link;
	} while (node != head->link);

	return NULL;
}
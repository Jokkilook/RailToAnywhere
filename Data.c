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
	//if (q->front == NULL && q->rear == NULL) return 1;
	if (q->front == NULL) return 1;
	
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
		return NULL;
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

//큐 출력 함수
void printQueue(PassengerQueue* q) {
	if (isEmptyQueue(q)) {
		printf("");
		return;
	}

	PassengerNode* curr = q->front;
	int index = 1;

	while (curr != NULL) {
		Passenger* p = curr->data;
		printf("■ ", index++, p->ticket->destination);
		curr = curr->link;
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
		return NULL;
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
		printf("%s", p->data);
		if (p->link != head->link) {
			printf(" - ");
		}
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

PlatformNode* searchPlatformListWithNum(PlatformNode* head, int data)
{
	if (head == NULL) return NULL;

	PlatformNode* node = head->link;
	do {
		if (node->data->num == data) {
			return node;
		}
		node = node->link;
	} while (node != head->link);

	return NULL;
}

//승객 스택 초기화
void initStationStack(StationStack* s)
{
	s->top = NULL;
}

//승객 스택 공백 확인 함수
int isEmptyStationStack(StationStack* s)
{
	if (s->top == NULL) return 1;
	return 0;
}

//승객 스택 요소 추가 함수
void pushStation(StationStack* s, const char* data)
{
	StationNode* temp = (StationNode*)malloc(sizeof(StationNode));
	temp->data = data;
	temp->link = s->top;
	s->top = temp;
}

//승객 스택 요소 빼기 함수
const char* popStation(StationStack* s)
{
	if (isEmptyStationStack(s)) {
		return NULL;
	}
	else {
		PassengerNode* temp = s->top;
		Passenger* data = temp->data;
		s->top = s->top->link;
		free(temp);
		return data;
	}
}

//승객 큐 초기화 함수
void initDialogueQueue(DialogueQueue* q)
{
	q->front = NULL;
	q->rear = NULL;
}

//승객 큐 공백 확인 함수
int isEmptyDialogueQueue(DialogueQueue* q) {
	//if (q->front == NULL && q->rear == NULL) return 1;
	if (q->front == NULL) return 1;

	return 0;
}

//승객 큐 요소 추가 함수
void enqueueDialogue(DialogueQueue* q, const char* data) {
	DialogueNode* temp = (DialogueNode*)malloc(sizeof(DialogueNode));
	temp->data = data;
	temp->link = NULL;

	if (isEmptyDialogueQueue(q)) {
		q->front = temp;
		q->rear = temp;
	}
	else {
		q->rear->link = temp;
		q->rear = temp;
	}
}

//승객 큐 요소 빼기 함수
const char* dequeueDialogue(DialogueQueue* q)
{
	DialogueNode* temp = q->front;
	const char* data;
	if (isEmptyDialogueQueue(q)) {
		return NULL;
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

//큐 출력 함수
void printDialogueQueue(DialogueQueue* q) {
	if (isEmptyDialogueQueue(q)) {
		printf("");
		return;
	}

	DialogueNode* curr = q->front;
	int index = 1;

	while (curr != NULL) {
		const char* p = curr->data;
		printf("%s", p);
		curr = curr->link;
	}
}

FeedbackTree* createTreeNode(const char* data)
{
	FeedbackTree* node = (FeedbackTree*)malloc(sizeof(FeedbackTree));
	node->data = data;
	node->good = NULL;
	node->bad = NULL;

	return node;
}

FeedbackTree* initAndSetTree()
{
	FeedbackTree* root = (FeedbackTree*)malloc(sizeof(FeedbackTree));

	FeedbackTree* g = createTreeNode(FeedbackList[0]);
	FeedbackTree* b = createTreeNode(FeedbackList[1]);
	FeedbackTree* gg = createTreeNode(FeedbackList[2]);
	FeedbackTree* gb = createTreeNode(FeedbackList[5]);
	FeedbackTree* ggg = createTreeNode(FeedbackList[3]);
	FeedbackTree* ggb = createTreeNode(FeedbackList[4]);
	FeedbackTree* gbg = createTreeNode(FeedbackList[6]);
	FeedbackTree* gbb = createTreeNode(FeedbackList[7]);
	FeedbackTree* bg = createTreeNode(FeedbackList[8]);
	FeedbackTree* bb = createTreeNode(FeedbackList[11]);
	FeedbackTree* bgg = createTreeNode(FeedbackList[9]);
	FeedbackTree* bgb = createTreeNode(FeedbackList[10]);
	FeedbackTree* bbg = createTreeNode(FeedbackList[12]);
	FeedbackTree* bbb = createTreeNode(FeedbackList[13]);

	root->data = "";
	root->good = g;
	root->bad = b;
	g->good = gg;
	g->bad = gb;
	gg->good = ggg;
	gg->bad = ggb;
	gb->good = gbg;
	gb->bad = gbb;
	b->good = bg;
	b->bad = bb;
	bg->good = bgg;
	bg->bad = bgb;
	bb->good = bbg;
	bb->bad = bbb;

	return root;
}

void pruneTree(FeedbackTree* root)
{
	if (root) {
		pruneTree(root->good);
		pruneTree(root->bad);
		free(root);
	}
}

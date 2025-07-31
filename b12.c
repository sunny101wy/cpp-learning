#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct Stack{
	int items[MAX];
	int top;
}Stack;
void initStack(Stack*s){
	s->top=-1;
}
bool isEmpty(Stack*s){
	return s->top==-1;
}
bool isFull(Stack*s){
	return s->top==MAX-1;
}
void push(Stack*s,int item){
	if(isFull(s)){
		return;
	}
	s->items[(s->top)++]=item;
}
int pop(Stack*s){
	if(isEmpty(s)){
		return -1;
	}
	return s->items[(s->top)--]; 
}
int peek(Stack*s){
	if(isEmpty(s)){
		return -1;
	}
	return s->items[s->top];
}

//typedef struct Node{
//	int data;
//	struct Node*next;
//}Node;
//typedef struct Stack{
//	Node*top;
//}Stack;
//bool isEmpty(Stack*s){
//	return s->top==NULL;
//}
//void push(Stack*s,int item){
//	Node*newNode=(Node*)malloc(sizeof(Node));
//	newNode->data=item;
//	newNode->next=s->top;
//	s->top=newNode;
//}
//int pop(Stack*s){
//	if(isEmpty(s)){
//		return -1;
//	}
//	Node*temp=s->top;
//	s->top=temp->next;
//	int item=temp->data;
//	free(temp);
//	return item;
//}
//int peek(Stack*s){
//	if(isEmpty(s)){
//		return -1;
//	}
//	return s->top->data;
//}
#define CAPACITY 100
typedef struct Queue{
	int data[CAPACITY];
	int front;
	int rear;
	int size;
}Queue;
void initQueue(Queue*q){
	q->front=0;
	q->rear=-1;
	q->size=0;
}
bool isEmpty(Queue*q){
	return q->size==0;
}
bool isFull(Queue*q){
	return q->size==CAPACITY;
}
void enqueue(Queue*q,int value){
	if(isFull(q)){
		exit(1);
	}
	q->rear=(q->rear+1)%CAPACITY;
	q->data[q->rear]=value;
	q->size++;
}
int dequeue(Queue*q){
	if(isEmpty(q)){
		exit(1);
	}
	int value=q->data[q->front];
	q->front=(q->front+1)%CAPACITY;
	q->size--;
	return value;
}
int front(Queue*q){
	if(isEmpty(q)){
		exit(1);
	}
	return q->data[q->front];
}


//typedef struct Node {
//    int data;
//    struct Node* next;
//} Node;
//
//typedef struct {
//    Node* front;
//    Node* rear;
//} Queue;
//
//void initQueue(Queue* q) {
//    q->front = NULL;
//    q->rear = NULL;
//}
//
//int isEmpty(Queue* q) {
//    return q->front == NULL;
//}
//
//void enqueue(Queue* q, int value) {
//    Node* newNode = (Node*)malloc(sizeof(Node));
//    newNode->data = value;
//    newNode->next = NULL;
//
//    if (isEmpty(q)) {
//        q->front = newNode;
//        q->rear = newNode;
//    } else {
//        q->rear->next = newNode;
//        q->rear = newNode;
//    }
//}
//
//int dequeue(Queue* q) {
//    if (isEmpty(q)) {
//        exit(1);
//    }
//
//    Node* temp = q->front;
//    int value = temp->data;
//    q->front=temp->next;
//    if(q->front==NULL){
//    	q->rear=NULL;
//	}
//    free(temp);
//    return value;
//}
//#define CAPACITY 100
//typedef struct Deque{
//	int data[CAPACITY];
//	int front;
//	int rear;
//	int size;
//}Deque;
//void init(Deque*dq){
//	int front=-1;
//	int rear=0;
//	int size=0;
//}
//bool isEmpty(Deque*dq){
//	return dq->size==0;
//}
//bool isFull(Deque*dq){
//	return dq->size==CAPACITY;
//}
//void insertHead(Deque*dq,int value){
//	if(isFull(dq)){
//		exit(1);
//	}
//	if(dq->front==-1){
//		dq->front=0;
//		dq->rear=0;
//	}
//	else if(dq->front==0){
//		dq->front=CAPACITY-1;
//	}
//	else
//		dq->front--;
//	dq->data[dq->front]=value;
//	dq->size++;
//}
//void insertTail(Deque*dq,int value){
//	if(isFull(dq)){
//		exit(1);
//	}
//	
//	if(dq->front==-1){
//		dq->front=0;
//		dq->rear=0;		
//	}
//	else if(dq->rear==CAPACITY-1){
//		dq->rear=0;
//	}
//	else
//		dq->rear++;
//	dq->data[dq->rear]=value;
//	dq->size++;
//}
//int deleteFront(Deque*dq){
//	if(isEmpty(dq)){
//		exit(1);
//	}
//	int value=dq->data[dq->front];
//	if(dq->front==dq->rear){
//		dq->front=-1;
//		dq->rear=0;
//	}
//	else if(dq->front==CAPACITY-1){
//		dq->front=0;
//	}
//	else
//		dq->front++;
//	dq->size--;
//	return value;
//}
//int deleteTail(Deque*dq){
//	if(isEmpty(dq)){
//		exit(1);
//	}
//	int value=dq->data[dq->rear];
//	if(dq->rear==dq->front){
//		dq->rear=0;
//		dq->front=-1;
//	}
//	else if(dq->rear==0){
//		dq->rear=CAPACITY-1;
//	}
//	else
//		dq->rear--;
//	dq->size--;
//	return value;
//}
//int getFront(Deque*dq){
//	if(isEmpty(dq)){
//		exit(1);
//	}
//	int value=dq->data[dq->front];
//	return value;
//}
//int getTail(Deque*dq){
//	if(isEmpty(dq)){
//		exit(1);
//	}
//	int value=dq->data[dq->rear];
//	return value;
//}
typedef struct Node{
	int data;
	struct Node*next;
	struct Node*prev;
}Node;
typedef struct{
	Node*front;
	Node*rear;
}Deque;
bool isEmpty(Deque*dq){
	return dq->front==NULL;
}
void init(Deque*dq){
	dq->front=NULL;
	dq->rear=NULL;
}
void insertFront(Deque*dq,int value){
	Node*newNode=(Node*)malloc(sizeof(Node));
	if(!newNode){
		exit(1);
	}
	newNode->data=value;
	newNode->prev=NULL;
	newNode->next=dq->front;
	if(isEmpty(dq))
	{
		dq->rear=newNode;
	}
	else
	{
		dq->front->prev=newNode;
	}
	dq->front=newNode;
}
void insertTail(Deque*dq,int value){
	Node*newNode=(Node*)malloc(sizeof(Node));
	if(!newNode){
		exit(1);
	}
	newNode->data=value;
	newNode->prev=dq->rear;
	newNode->next=NULL;
	if(isEmpty(dq)){
		dq->front=newNode;
	}
	else
		dq->rear->next=newNode;
	dq->rear=newNode;
}
int deleteFront(Deque*dq){
	if(isEmpty(dq)){
		exit(1);
	}
	Node*temp=dq->front;
	int value=temp->data;
	dq->front=dq->front->next;
	if(dq->front==NULL){
		dq->rear=NULL;
	}
	else
		dq->front->prev=NULL;
	free(temp);
	return value;
}
int deleteTail(Deque*dq){
	if(isEmpty(dq)){
		exit(1);
	}
	Node*temp=dq->rear;
	int value=temp->data;
	dq->rear=dq->rear->prev;
	if(dq->rear==NULL){
		dq->front=NULL;
	}
	else
		dq->rear->next=NULL;
	free(temp);
	return value;
}
int getFront(Deque*dq){
	if(isEmpty(dq)){
		exit(1);
	}
	return dq->front->data;
}
int getTail(Deque*dq){
	if(isEmpty(dq)){
		exit(1);
	}
	return dq->rear->data;
}
int main(int argc, char *argv[]) {

}


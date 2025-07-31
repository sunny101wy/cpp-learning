#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define nodeCount 5
#define MAX_NODES 5
int graph[nodeCount][nodeCount]={
	{0,1,1,0,1},
	{1,0,1,1,1},
	{1,1,0,0,0},
	{0,1,0,0,1},
	{1,1,0,1,0} 

};
bool visit[nodeCount]={false};

void dfs1(int node){

	
//	static bool visit[nodeCount]={false};
	printf("visit %d \n",node);
	visit[node]=true;
	
	for(int i=0;i<nodeCount;i++){
		if(graph[node][i]==1&&!visit[i]){
			dfs1(i);
		}
	}
	
}

void dfs2(int node){
	bool visit[nodeCount]={false};
	int stack[nodeCount];
	int top=0;
	
	visit[node]=true;
	stack[top]=node;
	top +=1; 
	
	while(top>0){
		top -= 1;
		int node=stack[top];
		printf("visit %d \n",node);
//		for(int i=0;i<nodeCount;i++){
		for(int i=nodeCount-1;i>=0;i--){
			if(graph[node][i]==1&&!visit[i]){
				stack[top]=i;
				visit[i]=true;
				
				top += 1;
			}

		}
	}
} 
void dfs3(int node){
	bool visit[nodeCount]={false};
	int stack[nodeCount*nodeCount];
	int top=0;
	
	
	stack[top]=node;
	top +=1; 
	
	while(top>0){
		top -= 1;
		int node=stack[top];
		if(!visit[node])
		{
			visit[node]=true;
			printf("visit %d \n",node);
			
			for(int i=nodeCount-1;i>=0;i--){
				if(graph[node][i]==1&&!visit[i]){
					stack[top]=i;
					
					top += 1;
				}
	
			}

		}
	}
} 
 
bool visited[MAX_NODES] = { false }; // 标记每个节点是否访问过

typedef struct {
    int node;   // 节点编号
    bool isFirstVisit; // 标记节点是否是首次入栈
} StackFrame;



int graph2[nodeCount][nodeCount]={
	{0,1,1,1,1},
	{1,0,0,0,1},
	{1,0,0,1,0},
	{1,0,1,0,0},
	{1,0,1,0,0}

};

int graph4[20][20]={0};
typedef struct Queue{
	int arr[nodeCount];
	int front;
	int rear;
}Queue;
void initQueue(Queue*q){
	q->front=0;
	q->rear=0;
}
bool isEmpty(Queue*q){
	return q->front==q->rear;
}
bool isFull(Queue*q){
	return (q->rear+1)%nodeCount==q->front;
}
void enQueue(Queue*q,int value){
	if(!isFull(q)){
		q->arr[q->rear]=value;
		q->rear=(q->rear+1)%nodeCount;
	}
	else{
		printf("The queue is full");
	}
}
int deQueue(Queue*q){
	if(!isEmpty(q)){
		int temp=q->arr[q->front];
		q->front=(q->front+1)%nodeCount;
		return temp;
	}
	else{
		printf("The queue is empty");
	}
}
void bfs(int start){
	bool visit[nodeCount]={false};
	Queue*q=(Queue*)malloc(sizeof(Queue));
	initQueue(q);
	
	visit[start]=true;
	enQueue(q,start);
	while(!isEmpty(q)){
		int node=deQueue(q);
		printf("visit node %d \n",node);
		
		for(int i=0;i<nodeCount;i++){
			if((!visit[i])&&graph2[node][i]==1){
				visit[i]=true;
				enQueue(q,i);
			}
		}
	}
}
//bool visit2[20]={false};
void dfs4(bool visit[],int node_count,int node){
	int stack[20];
	int top=0;
	
	visit[node]=true;
	stack[top]=node;
	top +=1; 
	
	while(top>0){
		top -= 1;
		int node=stack[top];	
		printf("visit %d \n",node);
		
		for(int i=node_count-1;i>0;i--){
			if(graph4[node][i]==1&&!visit[i]){
				stack[top]=i;
				visit[i]=true;
				top += 1;
			}

		}
	}
} 
void count2(){
	bool visit[20]={false};
	int node_count=0;
	int count=0;
	int a=0;
	int b=0;
	int temp=0;
	FILE*file=fopen("input.txt","r");
	fscanf(file,"%d %d",&node_count,&count);
	
	for(int i=0;i<count;i++){
		fscanf(file,"%d %d",&a,&b);
		graph4[a][b]=1;
		graph4[b][a]=1;
	}
	
	for(int i=0;i<node_count;i++){
		if(!visit[i]){
			dfs4(visit,node_count,i);
			temp += 1;
		}
	}
	printf("the number is %d",temp);
//	dfs4(graph,node_count,0);
//	passing argument 1of dfs4 from incompatible pointer type
//	从不兼容的指针类型传递dfs4的参数1
} 
void count(){
	bool visit[20]={false};
	int node_count=0;
	int count=0;
	int a=0;
	int b=0;
	int temp=0;
	printf("input node number and count:\n");
	scanf("%d %d",&node_count,&count);
	
	printf("input graph:\n");
	
	for(int i=0;i<count;i++){
		scanf("%d %d",&a,&b);
		graph4[a][b]=1;
		graph4[b][a]=1;
	}
	
	for(int i=0;i<node_count;i++){
		if(!visit[i]){
			dfs4(visit,node_count,i);
			temp += 1;
		}
	}
	printf("the number is %d",temp);
//	dfs4(graph,node_count,0);
//	passing argument 1of dfs4 from incompatible pointer type
//	从不兼容的指针类型传递dfs4的参数1
}
int g_node_count=0;
int graph5[20][20]={0};
bool visited2[20]={false};
int getGraph(){
	int count=0;
	int a=0;
	int b=0;
	int temp=0;
	
	printf("input node number and count:\n");
	scanf("%d %d",&g_node_count,&count);
	
	printf("input graph:\n");
	
	for(int i=0;i<count;i++){
		scanf("%d %d",&a,&b);
		graph5[a][b]=1;
		graph5[b][a]=1;
	}
	return g_node_count;
}

bool ringDetect(int node,int parent){
	visited2[node]=true;
	
	for(int i=0;i<g_node_count;i++){
		if(graph5[node][i]==1){
			if(!visited2[i]){
				if(ringDetect(i,node)){
					return true;
				}
			}
			else{
				if(i!=parent){
					printf("yes");
					return true;
				}
			}
			
		}
	}
	printf("no");
	return false;
}
bool visited3[20]={false};
int graph_path[20][20]={0};
void pathDetect(){	
	int node_Count;
	int count=0;
	int a=0;
	int b=0;
	int temp=0;
	int start;
	int target;
	
	FILE*file=fopen("input2.txt","r");
	fscanf(file,"%d %d",&node_Count,&count);
	
	for(int i=0;i<count;i++){
		fscanf(file,"%d %d",&a,&b);
		graph_path[a][b]=1;
		graph_path[b][a]=1;
	}
	fscanf(file,"%d %d",&start,&target);



	Queue*que=(Queue*)malloc(sizeof(Queue));
	initQueue(que);
	
	visited3[start]=true;
	enQueue(que,start);
	while(!isEmpty(que)){
		int node=deQueue(que);
		printf("visit node %d \n",node);
		
		for(int i=0;i<node_Count;i++){
			if((!visited3[i])&&graph_path[node][i]==1){
				visited3[i]=true;
				enQueue(que,i);
			}
		}
	}
	if(!visited3[target]){
		printf("no path");
	}
	else{
		printf("have path");
	}
}
int main()
{
	pathDetect();
//	getGraph();
//	ringDetect(0,0);
}

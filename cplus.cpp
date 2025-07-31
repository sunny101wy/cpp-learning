
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>
//#include <ifstream>
//using namespace std;
class Stack{
private:
	int _capacity;
	int _top;
	int*_items;
public:
	Stack(int cap);
	~Stack();
	bool isEmpty();	
	bool isFull();
	void push(int item);
	int pop();
	int peek();		
};
Stack::Stack(int cap):_capacity(cap){
	_items=new int[cap];
	memset(_items,0,cap*sizeof(int));
	_top=-1;
} 
Stack::~Stack(){
	delete[] _items;
}
bool Stack::isEmpty(){
	return _top==-1;
}
bool Stack::isFull(){
	return _top==_capacity-1;
}
void Stack::push(int item){
	if(isFull()){
		return;
	}
	_top+=1;
	_items[_top]=item;
//	printf("push %d,top=%d\n",item,_top);
	std::cout<<"push"<<item<<",top="<<_top<<std::endl;
//	cout<<"push";
//	cout<<item;
//	cout<<",top=";
//	cout<<_top<<endl;
//	int i=0;

}
int Stack::pop(){
	if(isEmpty()){
		return -1;
	}
	int ret = _items[_top]; 
	_top-=1;
//	printf("pop %d,top=%d\n",ret,_top);
	std::cout<<"pop"<<ret<<",top="<<_top<<std::endl;
	return ret;
}
int Stack::peek(){
	if(isEmpty()){
		return -1;
	}
	return _items[_top];
}
class Queue{
private:
	int _capacity; 
	int*_data;
	int _front;
	int _rear;
	int _size;
public:
	Queue(int cap);
	~Queue();
	bool isEmpty();
	bool isFull();
	void enqueue(int value);
	int dequeue();
	int front();
};
Queue::Queue(int cap):_capacity(cap){
	_data=new int[cap];
	memset(_data,0,cap*sizeof(int));
	_front=0;
	_rear=-1;
	_size=0;
	
} 
Queue::~Queue() {
	delete[] _data;
}
bool Queue::isEmpty(){
	return _size==0;
}
bool Queue::isFull(){
	return _size==_capacity;
}
void Queue::enqueue(int value){
	if(isFull()){
		exit(1);
	}
	_rear=(_rear+1)%_capacity;
	_data[_rear]=value;
	_size++;
}
int Queue::dequeue(){
	if(isEmpty()){
		exit(1);
	}
	int value=_data[_front];
	_front=(_front+1)%_capacity;
	_size--;
	return value;
}
int Queue::front(){
	if(isEmpty()){
		exit(1);
	}
	return _data[_front];
}

class Graph{
private:
	int _vertex;
	int** _arr;
public:
	Graph(const Graph& other);
	Graph(int vertex);
	~Graph();
	void addEdge(int u,int v);
	void dfs(int start);
};
Graph::Graph(const Graph& other){
	_vertex=other._vertex;
	
	_arr=new int*[_vertex];
	for(int i=0;i<_vertex;i++){
		_arr[i]=new int[_vertex];
		memcpy(_arr[i],other._arr[i],_vertex*sizeof(int));
	}
}
Graph::Graph(int vertex):_vertex(vertex){
//	_vertex=vertex;
	_arr=new int*[_vertex];

	for(int i=0;i<_vertex;i++){
		_arr[i]=new int[_vertex];
		memset(_arr[i],0,_vertex*sizeof(int));
	}
//	int *p = new int[4] ;
//	delete[] p;
}
Graph::~Graph(){
	for(int i=0;i<_vertex;i++){
		delete[] _arr[i];
	}
	delete[] _arr;
}
void Graph::addEdge(int u,int v){
	_arr[u][v]=1;
	_arr[v][u]=1;
}
void Graph::dfs(int start){
//	bool*visit=(bool*)malloc(_vertex*sizeof(bool));
	bool*visit=new bool[_vertex];
	memset(visit,0,_vertex*sizeof(bool));
	Stack stack(_vertex*_vertex);
	
	stack.push(start);  
	
	while(!stack.isEmpty() ){
		int node=stack.pop() ;
		if(!visit[node])
		{
			visit[node] = true;
			
//			printf("visit %d \n",node);
//			
			std::cout<<"visit"<<node<<std::endl;
			for(int i=_vertex-1;i>=0;i--){
				if(_arr[node][i]==1&&!visit[i]){
//					visit[i]=true;
					stack.push(i) ;
				}
	
			}

		}
	}
	delete[] visit;
} 



int main() {
	int vertex(6);
	int temp = 3;
//	int temp(4);
	Graph graph(vertex);
	graph.addEdge(0,1);
	graph.addEdge(1,2);
	graph.addEdge(1,3);
	graph.addEdge(0,4);
	graph.addEdge(0,5);
	graph.addEdge(2,5);
	
	Graph graph2(5);
	graph2.addEdge(3,4); 
	graph.dfs(0);
	
	Graph g3(graph);
	
	int a = 20;
	const int b = 30;
	a = 40;
//	graph2.dfs(3); 
}

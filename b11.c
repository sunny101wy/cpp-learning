#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct Node{
	int data;
	struct Node*next;
	struct Node*prev;
}Node;
Node*creat(){
	return NULL;
}
Node*createNode(int data){
	Node*node=(Node*)malloc(sizeof(Node));
	node->data=data;
	node->next=NULL;
	node->prev=NULL;
	return node;
}
void insertAtHead(Node**head,int data){
	Node*newNode=createNode(data);
	if(*head==NULL){
		*head=newNode;
		return;
	}
	newNode->next=*head;
	(*head)->prev = newNode;
	*head=newNode;
	
}
void insertAtTail(Node**head,int data){
	Node*newNode=createNode(data);
	if(*head==NULL){
	   *head=newNode;
	   return;
	}
	Node*temp=*head;
	while(temp->next!=NULL){
		temp=temp->next;
	}
	temp->next=newNode;
	newNode->prev=temp;
}
void insertAfter(Node*prev,int data){
	if(prev==NULL){
		return;
	}
	Node*newNode=createNode(data);
	newNode->prev=prev;
	if(prev->next!=NULL){
		prev->next->prev=newNode;
		newNode->next=prev->next;
	}
	prev->next=newNode;

} 
void deleteHead(Node**head){
	if(*head==NULL){
		return;
	}
	Node*temp=*head;
	*head=(*head)->next;
	if(*head!=NULL){
		(*head)->prev=NULL;
	}
	free(temp);
}
void deleteTail(Node**head){
	if(*head==NULL){
		return;
	}
	Node*temp=*head;
	if(temp->next==NULL){
		*head=NULL;
		free(temp);
		return;
	}
	while(temp->next!=NULL){
		temp=temp->next;
	}
	temp->prev->next=NULL;
	free(temp);
}
void deleteNode(Node**head,Node*delNode){
	if(*head==NULL||delNode==NULL)
		return;
	if(delNode==*head)
		*head=delNode->next;
	if(delNode->next!=NULL)
		delNode->next->prev=delNode->prev;
	if(delNode->prev!=NULL){
		delNode->prev->next=delNode->next;
	}
	free(delNode);
	return;
}
void sort(int arr[],int len){
	for(int i=0;i<len-1;i++){
		int bozital=0;
		for(int j=0;j<len-i-1;j++){
			
			if(arr[j]>arr[j+1]){
				int blank=0;
				blank=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=blank;
				bozital=1;
			}
		}
		if(bozital==0){
			break;
		}
	}	
}
void sort2(int arr[],int len){
	int i=0;
	for( ;i<len-1;i++){
		int min_idx=i;
		int j=i;
		for( int j=i+1;j<len;j++)
		{
			if(arr[j]<arr[min_idx]){
				min_idx=j;
			}
		} 
		if(min_idx!=i){
			int blank=arr[min_idx];
			arr[min_idx]=arr[i];
			arr[i]=blank;
		}
	}
}
void sort3(int arr[],int len){
	int i=1;
	for(;i<len;i++){
		for(int j=i-1;j>0;j--){
			int key=arr[i];
			if(arr[j]>key){
				arr[j+1]=arr[j];
			}
			else
			{
				arr[j+1]=key;
				break; 
			}
		}
	}
}
void sort4(int arr[],int len){
	int i=1;
	for(;i<len;i++){
		int key=arr[i];
		int j=i-1;
		while(j>=0 && arr[j]>key){
			arr[j+1]=arr[j];
			j--;
		}
		arr[j]=key;
	}
}
int main(int argc, char *argv[]) {
	Node *node = malloc(sizeof(Node));
	
	{
		Node node2

	}
	
}



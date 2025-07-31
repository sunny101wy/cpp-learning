#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Table_size 100

typedef struct Node{
	char*key;
	int value;
	struct Node*next;
}Node;
typedef struct{
	Node*hash_table[Table_size];
}HashTable;
int hash(char*key){
	int hashSize=0;
	int i=0;
	while(key[i]!='0'){
		hashSize=hashSize*19+key[i];
		i++;
	}
	return hashSize%Table_size;
}
Node*createNode(char*key,int value){
	Node*newNode=(Node*)malloc(sizeof(Node));
	newNode->key=strdup(key);
	newNode->value=value;
	newNode->next=NULL;
	return newNode;
}
void insert(HashTable*hashTable,char*key,int value){
	int index=hash(key);
	Node*newNode=createNode(key,value);
	Node*temp=hashTable->hash_table[index];
	while(temp!=NULL){
		if(strcmp(key,temp->key)==0 ){
			temp->value=value;
			free(newNode->key);
			free(newNode);
			return;
		}
		temp=temp->next;
	}
	newNode->next=hashTable->hash_table[index];
	hashTable->hash_table[index]=newNode;
	return;
}
int find(HashTable*hashTable,char*key){
	int index=hash(key);
	Node*temp=hashTable->hash_table[index];
	while(temp!=NULL){
		if(strcmp(key,temp->key)==0){
			return temp->value;
		}
		temp=temp->next;
	}
	printf("not exit");
	return -1;
}
void deleteNode(HashTable*hashTable,char*key){
	int index=hash(key);
	Node*prev=NULL;
	Node*temp=hashTable->hash_table[index];
	while(temp!=NULL){
		if(strcmp(key,temp->key)==0 ){
			if(prev==NULL){
				hashTable->hash_table[index]=temp->next;
			}
			else{
				prev->next=temp->next;
			}
			free(temp->key);
			free(temp);
			return;
		}
		prev=temp;
		temp=temp->next;
	}
	
	
}
int main()
{

}

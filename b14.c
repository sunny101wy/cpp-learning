#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node{
	int key;
	struct Node*left;
	struct Node*right;
}Node;

Node* createTreeNode(int key){
	Node*newNode=(Node*)malloc(sizeof(Node));
	newNode->key=key;
	newNode->left=NULL;
	newNode->right=NULL;
	return newNode;
}

Node* insertNode(Node*root,int key){
	if(root==NULL){
		return createTreeNode(key);
	}
	
	if(key<root->key){
		root->left=insertNode(root->left,key);
	}else if(key>root->key){
		root->right=insertNode(root->right,key);
	}
	return root;
}

Node* findMin(Node* root) {
    while (root&&root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key<root->key){
        root->left=deleteNode(root->left,key);
	}
	else if(key>root->key){
		root->right=deleteNode(root->right,key);
	}
	else 
	{
		if(root->left==NULL){
			Node*temp=root->right;
			free(root);
			root = temp;
//			return temp;
		}
		else if(root->right==NULL){
			Node*temp=root->left;
			free(root);
			root = temp;
//			return temp;
		}else{		
			Node*node=findMin(root->right);
			root->key=node->key;
			root->right= deleteNode(root->right,node->key);
		}
	}
	return root;
	
}
void preoderTraversal(Node*root){
	if(root==NULL){
		return;
	}
	printf("%d",root->key);
	
	preoderTraversal(root->left);
	
	preoderTraversal(root->right);
}
void inoderTraversal(Node*root){
	if(root==NULL){
		return;
	}
	inoderTraversal(root->left);
	
	printf("%d",root->key);
	
	inoderTraversal(root->right);
}
void postoderTraversal(Node*root){
	if(root==NULL){
		return;
	}	
	postoderTraversal(root->left);
	
	postoderTraversal(root->right);
	
	printf("%d",root->key);
}

int main(int argc, char *argv[]) {
	
	int i = 4;
	int *p = &i;
	int j = 6;
	
	p = &j;
	
	*p = 7;
}


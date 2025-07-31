#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define BLACK 0
#define RED 1

typedef struct RBNode{
	struct RBNode*parent;
	struct RBNode*left;
	struct RBNode*right;
	int data;
	int color;
}RBNode;



RBNode nil_node={NULL,NULL,NULL,0,BLACK};

RBNode*NIL=&nil_node;

typedef struct RBTree{
	RBNode*root;
}RBTree;

RBNode*createNode(int data){
	RBNode*node=malloc(sizeof(RBNode));
	node->parent=NIL;
	node->left=NIL;
	node->right=NIL;
	node->data=data;
	node->color=RED;
	return node;
	
}
RBNode*findMin(RBNode*node){
	while(node->left!=NIL){
		node=node->left;
	}
	return node;
}

void transPlant(RBTree*tree,RBNode*x,RBNode*y){
	if(x->parent==NIL){
		tree->root=y;
	}
	else if(x==x->parent->left){
		x->parent->left=y;
	}
	else
	{
		x->parent->right=y;	
	}
	y->parent=x->parent;
	
}
//void leftRotate(RBTree*tree,RBNode*x){
//	RBNode*y=x->right;
//	if()
//}
void leftRotate(RBTree*tree,RBNode*x){
	RBNode*y=x->right;
	x->right=y->left;
	if(y->left!=NIL){
		x->right->parent=x;
	}
	y->parent=x->parent;
	if(tree->root==x){
		tree->root=y;
	}
	else if(x==x->parent->left){
		x->parent->left=y;
	}
	else{
		x->parent->right=y;
	}
	y->left=x;
	x->parent=y;
}
void rightRotate(RBTree*tree,RBNode*y){
	RBNode*x=y->left;
	y->left=x->right;
	if(x->right!=NIL){
		y->left->parent=y;
	}
	x->parent=y->parent;
	if(tree->root==y){
		tree->root=x;
	}
	else if(y==y->parent->left){
		y->parent->left=x;
	}
	else{
		y->parent->right=x;
	}
	x->right=y;
	y->parent=x;
}
void fixInsert(RBTree*tree,RBNode*z){
	RBNode*w;
	while(z->parent->color==RED)
	{
		if(z->parent==z->parent->parent->left)
		{
			w=z->parent->parent->right;
			if(w->color==RED)
			{
				z->parent->parent->color=RED;
				z->parent->color=BLACK;
				w->color=BLACK;
				z=z->parent->parent;
			}
			else
			{
				if(z==z->parent->right)
				{
					z=z->parent;
					leftRotate(tree,z);
				}
				z->parent->color=BLACK;
				z->parent->parent->color=RED;
				rightRotate(tree,z->parent->parent);	
			}
		}
		else
		{
			w=z->parent->parent->left;
			if(w->color==RED)
			{
				z->parent->parent->color=RED;
				z->parent->color=BLACK;
				w->color=BLACK;
				z=z->parent->parent;
			}
			else
			{
				if(z==z->parent->left)
				{
					z=z->parent;
					rightRotate(tree,z);
				}
				z->parent->color=BLACK;
				z->parent->parent->color=RED;
				leftRotate(tree,z->parent->parent);
			}
		}
	}
	tree->root->color=BLACK;
}
void insert(RBTree*tree,int data){
	printf("insert %d being\n",data);
	RBNode*node=createNode(data);
	RBNode*x=tree->root;
	RBNode*y;
	if(x==NIL){
		tree->root=node;
	}
	else{
		while(x!=NIL){
			y=x;
			if(node->data<x->data){
				x=x->left;
			}
			else if(node->data>x->data){
				x=x->right;
			}
			else{
				free(node);
				printf("The data %d is exit\n",data);
				return;
			}
		}
		node->parent=y;
		if(node->data<y->data){
			y->left=node;
		}
		else{
			y->right=node;
		}
	}
	fixInsert(tree,node);
}
void fixDelete(RBTree*tree,RBNode*x,RBNode*parent)
{
	while(x!=tree->root&&x->color==BLACK && parent!=NIL)
	{
		if(x==parent->left)
		{
			RBNode*w=parent->right;
			if(w->color==RED)
			{
				w->color=BLACK;
				parent->color=RED;
				leftRotate(tree,parent);
				w=parent->right;
			}
			if(w->left->color==BLACK&&w->right->color==BLACK)
			{
				w->color=RED;
				if(parent->color==RED){
					parent->color=BLACK;
					x=tree->root;
				}
				else{
					x=parent;
					parent=parent->parent;
				}
			}
			else
			{
				if(w->left->color==RED)
				{
					rightRotate(tree,w);
					w=parent->right;
					w->color=BLACK;
					w->right->color=RED;
				}
				w->right->color=w->color;
				w->color=parent->color;
				parent->color=BLACK;
				leftRotate(tree,parent);
				x=tree->root;
			}
		}
		else
		{
			RBNode*w=parent->left;
			if(w->color==RED)
			{
				w->color=BLACK;
				parent->color=RED;
				rightRotate(tree,parent);
			}				w=parent->left;

			if(w->left->color==BLACK&&w->right->color==BLACK)
			{
				w->color=RED;
				if(parent->color==RED){
					parent->color=BLACK;
					x=tree->root;
				}
				else{
					x=parent;
					parent=parent->parent;
				}
			}
			else
			{
				if(w->right->color==RED)
				{
					leftRotate(tree,w);
					w=parent->left;
					w->color=BLACK;
					w->left->color=RED;
				}
				w->left->color=w->color;
				w->color=parent->color;
				parent->color=BLACK;
				rightRotate(tree,parent);
				x=tree->root;
			}
		}
	}
	x->color=BLACK;
}
void deleteNode(RBTree*tree,RBNode*node){
	RBNode*y=node;
	RBNode*x;
	RBNode*x_parent=y->parent;
	int orignal_color=y->color;
	if(node->left==NIL)
	{
		x=node->right;
		x_parent=node->parent;
		transPlant(tree,node,node->right);
	}
	else if(node->right==NIL)
	{
		x=node->left;
		x_parent=node->parent;
		transPlant(tree,node,node->left);
	}
	else
	{
		y=findMin(node->right);
		x=y->right;
		orignal_color=y->color;
		if(y->parent!=node){
			transPlant(tree,y,y->right);
			y->right=node->right;
			y->right->parent=y;
			x_parent = y->parent;
		}
		else
		{
			x_parent=y;
		}
		transPlant(tree,node,y);
		y->left=node->left;
		y->left->parent=y;
		y->color=node->color;
	}
	if(orignal_color==BLACK){
		fixDelete(tree,x,x_parent);
	}
}
void deleteData(RBTree*tree,int data){
	RBNode*x=tree->root;
	RBNode*y;
	printf("begin delete data %d:\n",data);
	while(x!=NIL)
	{
		if(data<x->data)
		{
			x=x->left;
		}
		else if(data>x->data)
		{
			x=x->right;
		}
		else
		{
			deleteNode(tree,x);
			return;
		}
	}
	printf("The number %d does not exit\n",data);
}
void initializeRBTree(RBTree*tree){
	tree->root=NIL;
}

int inoderPrint(RBNode*root,int level){
	if(root!=NIL){
		if(root->left != NIL && root->left->parent != root)
		{
			printf("node %d error\n",root->data);
			exit(-1);
		}
		if(root->right != NIL && root->right->parent != root)
		{
			printf("node %d error\n",root->data);
			exit(-1);
		}
		int blackNodes = 0;
		if( root->color == BLACK)
			blackNodes = 1;
		int leftNodes = inoderPrint(root->left,level+1);
		printf("(%d,%s,%d,%d) ",root->data,root->color==RED ? "R" : "B",level,root->parent->data);
		int rightNodes = inoderPrint(root->right,level+1);
		if( leftNodes != rightNodes )
		{
			printf("node %d error, red and black are not equal\n",root->data);
			exit(-1);
		}
		return blackNodes + leftNodes;
	}
	else
	{
		return 1;
	}
}

void inorderPrintTree(RBTree*tree)
{
	inoderPrint(tree->root,0);
	printf("\n");
}


int* generate_random_array(int n, int range) {
    // 动态分配内存
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("内存分配失败！\n");
        return NULL;
    }

    // 填充数组
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % range;  // 在指定范围内生成随机数
    }

    return arr;
}

// 函数：打乱数组顺序（Fisher-Yates Shuffle 算法）
void shuffle_array(int *arr, int n) {
    for (int i = n - 1; i > 0; i--) {
        // 生成 [0, i] 之间的随机索引
        int j = rand() % (i + 1);

        // 交换 arr[i] 和 arr[j]
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// 主函数，测试红黑树
int main()
{
	int len = 5000;
	int range = 10000;
	int * arr = generate_random_array(len,range);
	
	RBTree t;
	RBTree *tree = &t;
	initializeRBTree(tree);
	
	for( int i=0;i<len;i++ )
	{
		insert(tree,arr[i]); 
		inorderPrintTree(tree);
	}
	shuffle_array(arr,len);
	
	printf("\n\n\ninsert complete\n\n\n") ;
	
	for( int i=0;i<len;i++ )
	{
		deleteData(tree,arr[i]); 
		inorderPrintTree(tree);
	}
	
//	insert(tree,17);
//	inorderPrintTree(tree);
//
//	insert(tree,18);
//	inorderPrintTree(tree);
//
//
//	insert(tree,23);
//	inorderPrintTree(tree);
//
//
//	insert(tree,34);
//	inorderPrintTree(tree);
//
//
//	insert(tree,27);
//	inorderPrintTree(tree);
//
//
//	insert(tree,15);
//	inorderPrintTree(tree);
//
//
//	insert(tree,9);
//	inorderPrintTree(tree);
//
//
//	insert(tree,6);
//	inorderPrintTree(tree);
//
//
//	insert(tree,8);
//	inorderPrintTree(tree);
//
//
//	insert(tree,5);
//	inorderPrintTree(tree);
//
//	
//	insert(tree,25);	
//	inorderPrintTree(tree);
//
//	printf("insert complete,delete begin\n\n");
//
//	
//	deleteData(tree,17);
//	inorderPrintTree(tree);
//
//
//	deleteData(tree,18);
//	inorderPrintTree(tree);
//
//
//	deleteData(tree,23);
//	inorderPrintTree(tree);
//
//
//	deleteData(tree,34);
//	inorderPrintTree(tree);
//
//
//	deleteData(tree,27);
//	inorderPrintTree(tree);
//
//
//	deleteData(tree,15);
//	inorderPrintTree(tree);
//
//
//	deleteData(tree,9);
//	inorderPrintTree(tree);
//
//
//	deleteData(tree,6);
//	inorderPrintTree(tree);
//
//
//	deleteData(tree,8);
//	inorderPrintTree(tree);
//
//
//	deleteData(tree,5);
//	inorderPrintTree(tree);
//
//
//	deleteData(tree,25);
//	inorderPrintTree(tree);
//
//	
	
	
    return 0;
}

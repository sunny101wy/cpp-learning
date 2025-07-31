#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



#define RED 0     // 红色节点定义
#define BLACK 1   // 黑色节点定义

// 红黑树节点结构
typedef struct RBTreeNode {
    int data;                // 节点存储的数据
    int color;               // 节点颜色：RED 或 BLACK
    struct RBTreeNode *left;   // 左子节点
    struct RBTreeNode *right;  // 右子节点
    struct RBTreeNode *parent; // 父节点
} RBTreeNode;

// 红黑树结构
typedef struct RBTree {
    RBTreeNode *root;  // 树的根节点
    RBTreeNode *nil;   // 哨兵节点，表示叶子节点
} RBTree;

// 创建哨兵节点
RBTreeNode *createNilNode() {
    RBTreeNode *nilNode = (RBTreeNode *)malloc(sizeof(RBTreeNode));
    nilNode->color = BLACK;
    nilNode->left = nilNode->right = nilNode->parent = NULL;
    return nilNode;
}

// 创建红黑树
RBTree *createRBTree() {
    RBTree *tree = (RBTree *)malloc(sizeof(RBTree));
    tree->nil = createNilNode();  // 初始化哨兵节点
    tree->root = tree->nil;  // 初始化根节点为空
    return tree;
}

// 中序遍历红黑树
void inorderTraversal(RBTreeNode *node, RBTreeNode *nil) {
    if (node != nil) {
        inorderTraversal(node->left, nil);
        printf("%d ", node->data);
        inorderTraversal(node->right, nil);
    }
}

// 左旋操作：将节点x右旋，将其右子节点上提
void leftRotate(RBTree *tree, RBTreeNode *x) {
    RBTreeNode *y = x->right;  // 设置y为x的右子节点
    x->right = y->left;        // 将y的左子节点作为x的右子节点
    if (y->left != tree->nil)  // 如果y的左子节点存在，更新其父节点指针
        y->left->parent = x;
    y->parent = x->parent;     // 将y的父节点指向x的父节点
    if (x->parent == tree->nil) // 如果x是根节点，更新根节点为y
        tree->root = y;
    else if (x == x->parent->left)  // 如果x是左子节点，将y作为其父节点的左子节点
        x->parent->left = y;
    else  // 如果x是右子节点，将y作为其父节点的右子节点
        x->parent->right = y;
    y->left = x;  // 将x作为y的左子节点
    x->parent = y; // 更新x的父节点为y
}

// 右旋操作：将节点y左旋，将其左子节点上提
void rightRotate(RBTree *tree, RBTreeNode *y) {
    RBTreeNode *x = y->left;   // 设置x为y的左子节点
    y->left = x->right;        // 将x的右子节点作为y的左子节点
    if (x->right != tree->nil) // 如果x的右子节点存在，更新其父节点指针
        x->right->parent = y;
    x->parent = y->parent;     // 将x的父节点指向y的父节点
    if (y->parent == tree->nil) // 如果y是根节点，更新根节点为x
        tree->root = x;
    else if (y == y->parent->left) // 如果y是左子节点，将x作为其父节点的左子节点
        y->parent->left = x;
    else  // 如果y是右子节点，将x作为其父节点的右子节点
        y->parent->right = x;
    x->right = y;  // 将y作为x的右子节点
    y->parent = x; // 更新y的父节点为x
}


// 插入后修复红黑树的平衡
void insertFixUp(RBTree *tree, RBTreeNode *z) 
{	
    while (z->parent->color == RED) 
	{ // 如果父节点是红色，需要修复
        if (z->parent == z->parent->parent->left) 
		{  // 父节点是祖父节点的左子节点
            RBTreeNode *y = z->parent->parent->right; // y是祖父节点的右子节点（叔叔节点）
            if (y->color == RED) {  // Case 1: 叔叔节点是红色
                z->parent->color = BLACK;  // 将父节点设为黑色
                y->color = BLACK;          // 将叔叔节点设为黑色
                z->parent->parent->color = RED; // 将祖父节点设为红色
                z = z->parent->parent;     // 将z指向祖父节点
            } else {  // Case 2 或 3: 叔叔节点是黑色
                if (z == z->parent->right) {  // Case 2: z是右子节点
                    z = z->parent;
                    leftRotate(tree, z);  // 左旋父节点
                }
                z->parent->color = BLACK;  // Case 3: 将父节点设为黑色
                z->parent->parent->color = RED;  // 将祖父节点设为红色
                rightRotate(tree, z->parent->parent); // 右旋祖父节点
            }
        } 
		else 
		{  // 父节点是祖父节点的右子节点
            RBTreeNode *y = z->parent->parent->left;  // y是祖父节点的左子节点（叔叔节点）
            if (y->color == RED) {  // Case 1: 叔叔节点是红色
                z->parent->color = BLACK;  // 将父节点设为黑色
                y->color = BLACK;          // 将叔叔节点设为黑色
                z->parent->parent->color = RED; // 将祖父节点设为红色
                z = z->parent->parent;     // 将z指向祖父节点
            } else {  // Case 2 或 3: 叔叔节点是黑色
                if (z == z->parent->left) {  // Case 2: z是左子节点
                    z = z->parent;
                    rightRotate(tree, z); // 右旋父节点
                }
                z->parent->color = BLACK;  // Case 3: 将父节点设为黑色
                z->parent->parent->color = RED;  // 将祖父节点设为红色
                leftRotate(tree, z->parent->parent); // 左旋祖父节点
            }
        }
    }
    tree->root->color = BLACK; // 确保根节点始终为黑色
}


// 插入新节点到红黑树中
void insert(RBTree *tree, int data) {
    RBTreeNode *z = (RBTreeNode *)malloc(sizeof(RBTreeNode)); // 分配新节点内存
    z->data = data;                // 设置新节点数据
    z->left = z->right = z->parent = tree->nil; // 初始化新节点的左右子节点和父节点指针
    z->color = RED;  // 新插入的节点默认为红色

    RBTreeNode *y = tree->nil;   // y为树中的临时节点，用于找到插入位置
    RBTreeNode *x = tree->root;  // 从根节点开始查找插入位置


    while (x != tree->nil) {
        y = x;
        if (z->data == x->data) {
            // 节点已存在，处理方式可以是直接返回或更新数据
            printf("节点 %d 已存在，忽略插入。\n", data);
            free(z);
            return;  // 忽略插入
        }
        else if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }
//    while (x != tree->nil) {  // 查找插入位置
//        y = x;
//        if (z->data < x->data)
//            x = x->left;
//        else
//            x = x->right;
//    }

    z->parent = y;  // 设置新节点的父节点为找到的插入位置
    if (y == tree->nil)  // 如果树为空，新节点为根节点
        tree->root = z;
    else if (z->data < y->data)  // 如果新节点小于父节点，作为左子节点插入
        y->left = z;
    else  // 否则作为右子节点插入
        y->right = z;

    insertFixUp(tree, z);  // 修复红黑树的性质
}


// 删除节点后修复红黑树的平衡
void deleteFixUp(RBTree *tree, RBTreeNode *x) {
    while (x != tree->root && x->color == BLACK) {  // x是黑色且不为根节点，需要修复
        if (x == x->parent->left) {  // x是左子节点
            RBTreeNode *w = x->parent->right;  // w是x的兄弟节点
            if (w->color == RED) {  // Case 1: 兄弟节点是红色
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {  // Case 2: 兄弟节点的子节点都是黑色
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {  // Case 3: 兄弟节点的右子节点是黑色
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;  // Case 4: 兄弟节点的右子节点是红色
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(tree, x->parent);
                x = tree->root;
            }
        } else {  // x是右子节点
            RBTreeNode *w = x->parent->left;  // w是x的兄弟节点
            if (w->color == RED) {  // Case 1: 兄弟节点是红色
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {  // Case 2: 兄弟节点的子节点都是黑色
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {  // Case 3: 兄弟节点的左子节点是黑色
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;  // Case 4: 兄弟节点的左子节点是红色
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK; // 将x设为黑色
}

// 替换节点u和v
void rbTransplant(RBTree *tree, RBTreeNode *u, RBTreeNode *v) {
    if (u->parent == tree->nil)  // u是根节点，直接替换为v
        tree->root = v;
    else if (u == u->parent->left)  // u是左子节点，替换为v
        u->parent->left = v;
    else  // u是右子节点，替换为v
        u->parent->right = v;
    v->parent = u->parent;  // 更新v的父节点
}

// 删除红黑树中的节点
void delete(RBTree *tree, RBTreeNode *z) {
    RBTreeNode *y = z;  // y是待删除的节点
    RBTreeNode *x;      // x是用于修复的节点
    int y_original_color = y->color;  // 保存待删除节点的颜色

    if (z->left == tree->nil) {  // 如果z的左子节点为空，直接替换为右子节点
        x = z->right;
        rbTransplant(tree, z, z->right);
    } else if (z->right == tree->nil) {  // 如果z的右子节点为空，直接替换为左子节点
        x = z->left;
        rbTransplant(tree, z, z->left);
    } else {  // z有两个子节点
        y = z->right;
        while (y->left != tree->nil)  // 查找z的后继节点
            y = y->left;
        y_original_color = y->color;  // 保存后继节点的颜色
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            rbTransplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbTransplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_original_color == BLACK)  // 如果被删除的节点是黑色，需要修复
        deleteFixUp(tree, x);
    free(z);  // 释放删除的节点
}



// 主函数示例
int main() {
    RBTree *tree = createRBTree();
    insert(tree, 10);
    insert(tree, 20);
    insert(tree, 30);
    insert(tree, 15);

    printf("中序遍历红黑树: ");
    inorderTraversal(tree->root, tree->nil);
    printf("\n");

    delete(tree, tree->root->right);  // 删除节点

    printf("删除节点后的中序遍历红黑树: ");
    inorderTraversal(tree->root, tree->nil);
    printf("\n");

    return 0;
}


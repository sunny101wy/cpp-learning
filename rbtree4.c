#include <stdio.h>
#include <stdlib.h>

// 颜色定义
#define RED 0
#define BLACK 1

// 红黑树节点定义
typedef struct RBNode {
    int data;
    int color;
    struct RBNode *left, *right, *parent;
} RBNode;

// 红黑树定义
typedef struct RBTree {
    RBNode *root;
} RBTree;

// 全局唯一的NIL哨兵节点
RBNode NIL_NODE = {0, BLACK, NULL, NULL, NULL};
RBNode *NIL = &NIL_NODE;  // 所有空指针都指向这个NIL节点

// 创建新节点
RBNode* createNode(int data) {
    RBNode* newNode = (RBNode*)malloc(sizeof(RBNode));
    newNode->data = data;
    newNode->color = RED;  // 新插入节点默认是红色
    newNode->left = NIL;
    newNode->right = NIL;
    newNode->parent = NULL;
    return newNode;
}

// 左旋转
void leftRotate(RBTree *tree, RBNode *x) {
    RBNode *y = x->right;  // y是x的右孩子
    x->right = y->left;    // 将y的左孩子变成x的右孩子
    if (y->left != NIL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// 右旋转
void rightRotate(RBTree *tree, RBNode *y) {
    RBNode *x = y->left;   // x是y的左孩子
    y->left = x->right;    // 将x的右孩子变成y的左孩子
    if (x->right != NIL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL) {
        tree->root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

// 插入修正函数
void fixInsert(RBTree *tree, RBNode *z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode *y = z->parent->parent->right;
            if (y->color == RED) {  // Case 1: 叔叔节点是红色
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {  // 叔叔节点是黑色
                if (z == z->parent->right) {  // Case 2: z是右孩子
                    z = z->parent;
                    leftRotate(tree, z);
                }
                // Case 3: z是左孩子
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(tree, z->parent->parent);
            }
        } else {
            RBNode *y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

// 插入红黑树节点
void rbInsert(RBTree *tree, int data) {
    RBNode *z = createNode(data);
    RBNode *y = NULL;
    RBNode *x = tree->root;

    while (x != NIL) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == NULL) {
        tree->root = z;
    } else if (z->data < y->data) {
        y->left = z;
    } else {
        y->right = z;
    }

    z->left = NIL;
    z->right = NIL;
    z->color = RED;

    fixInsert(tree, z);
}

// 查找最小节点
RBNode* treeMinimum(RBNode *x) {
    while (x->left != NIL) {
        x = x->left;
    }
    return x;
}

// 删除节点的替换操作
void rbTransplant(RBTree *tree, RBNode *u, RBNode *v) {
    if (u->parent == NULL) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// 修正删除后的红黑树性质，增加parent参数处理NIL
// x: 传入的替代节点，可能为NIL
// parent: x的父节点
void fixDelete(RBTree *tree, RBNode *x, RBNode *parent) {
    // 当x不是根节点，且x为黑色时，需要进行修正
    while (x != tree->root && x->color == BLACK) {
        if (x == parent->left) { // 如果x是左孩子
            RBNode *w = parent->right; // w是x的兄弟节点
            // Case 1: 兄弟w是红色
            if (w->color == RED) {
                w->color = BLACK;           // 将w变黑
                parent->color = RED;        // 将parent变红
                leftRotate(tree, parent);   // 对parent左旋
                w = parent->right;          // 更新w为新的右孩子
            }
            // Case 2: 兄弟w的两个子节点都是黑色
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;             // 将w变红，合并黑色高度
                x = parent;                 // 继续向上调整
                parent = parent->parent;    // 更新parent为上一级节点
            } else
			 {
                // Case 3: 兄弟w的右子节点是黑色，左子节点是红色
                if (w->right->color == BLACK) {
                    w->left->color = BLACK; // 将w的左孩子变黑
                    w->color = RED;         // 将w变红
                    rightRotate(tree, w);   // 对w右旋
                    w = parent->right;      // 更新w为新的右孩子
                }
                // Case 4: 兄弟w的右子节点是红色
                w->color = parent->color;   // 将w的颜色设为parent的颜色
                parent->color = BLACK;      // 将parent设为黑色
                w->right->color = BLACK;    // 将w的右孩子设为黑色
                leftRotate(tree, parent);   // 对parent左旋
                x = tree->root;             // 终止循环，将x设为根节点
            }
        } else { // 如果x是右孩子，对称情况
            RBNode *w = parent->left; // w是x的兄弟节点
            // Case 1: 兄弟w是红色
            if (w->color == RED) {
                w->color = BLACK;           // 将w变黑
                parent->color = RED;        // 将parent变红
                rightRotate(tree, parent);  // 对parent右旋
                w = parent->left;           // 更新w为新的左孩子
            }
            // Case 2: 兄弟w的两个子节点都是黑色
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;             // 将w变红，合并黑色高度
                x = parent;                 // 继续向上调整
                parent = parent->parent;    // 更新parent为上一级节点
            } else 
			{
                // Case 3: 兄弟w的左子节点是黑色，右子节点是红色
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;// 将w的右孩子变黑
                    w->color = RED;         // 将w变红
                    leftRotate(tree, w);    // 对w左旋
                    w = parent->left;       // 更新w为新的左孩子
                }
                // Case 4: 兄弟w的左子节点是红色
                w->color = parent->color;   // 将w的颜色设为parent的颜色
                parent->color = BLACK;      // 将parent设为黑色
                w->left->color = BLACK;     // 将w的左孩子设为黑色
                rightRotate(tree, parent);  // 对parent右旋
                x = tree->root;             // 终止循环，将x设为根节点
            }
        }
    }
    // 将x设为黑色，以确保红黑树性质
    x->color = BLACK;
}


// 删除红黑树的节点
void rbDelete(RBTree *tree, RBNode *z) {
    RBNode *y = z;
    RBNode *x;
    RBNode *xParent;
    int originalColor = y->color;

    // Case 1: z只有右子节点或没有子节点
    if (z->left == NIL) {
        x = z->right;
        xParent = z->parent;
        rbTransplant(tree, z, z->right);
    }
    // Case 2: z只有左子节点
    else if (z->right == NIL) {
        x = z->left;
        xParent = z->parent;
        rbTransplant(tree, z, z->left);
    }
    // Case 3: z有两个子节点
    else {
        y = treeMinimum(z->right);  // 找到z的后继节点
        originalColor = y->color;
        x = y->right;
        xParent = y->parent;
        if (y->parent != z) {
            rbTransplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        } else {
            xParent = y;
        }
        rbTransplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (originalColor == BLACK) {
        fixDelete(tree, x, xParent);  // 删除黑色节点后需要修正
    }
}

// 初始化红黑树
void initializeRBTree(RBTree *tree) {
    tree->root = NIL;
}

// 打印红黑树，辅助调试
void inorderPrint(RBNode *root) {
    if (root != NIL) {
        inorderPrint(root->left);
        printf("%d(%s) ", root->data, root->color == RED ? "R" : "B");
        inorderPrint(root->right);
    }
}

// 主函数，测试红黑树
int main() {
    RBTree tree;
    initializeRBTree(&tree);

    // 插入节点
    rbInsert(&tree, 20);
    rbInsert(&tree, 15);
    rbInsert(&tree, 25);
    rbInsert(&tree, 10);
    rbInsert(&tree, 5);

    printf("红黑树插入后: ");
    inorderPrint(tree.root);
    printf("\n");

    // 删除节点
    rbDelete(&tree, tree.root->left);  // 删除15
    printf("删除15后: ");
    inorderPrint(tree.root);
    printf("\n");

    return 0;
}


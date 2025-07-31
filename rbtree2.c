#include <stdio.h>
#include <stdlib.h>

// 定义颜色
#define RED 0
#define BLACK 1

// 节点结构
typedef struct Node {
    int data;                // 节点的值
    int color;               // 节点的颜色：RED 或 BLACK
    struct Node* left;       // 左子节点
    struct Node* right;      // 右子节点
    struct Node* parent;     // 父节点
} Node;

// 红黑树结构
typedef struct RBTree {
    Node* root;              // 根节点
    Node* nil;               // NIL 节点，代表叶子
} RBTree;

// 创建一个新的节点
Node* createNode(RBTree* tree, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED;    // 新插入的节点初始为红色
    newNode->left = tree->nil;
    newNode->right = tree->nil;
    newNode->parent = NULL;
    return newNode;
}

// 创建一个新的红黑树
RBTree* createRBTree() {
    RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
    tree->nil = (Node*)malloc(sizeof(Node));
    tree->nil->color = BLACK;  // NIL 节点默认为黑色
    tree->root = tree->nil;    // 初始化时，根节点为 NIL
    return tree;
}

// 左旋函数
void leftRotate(RBTree* tree, Node* x) {
    Node* y = x->right;  // y 为 x 的右子节点
    x->right = y->left;  // 将 y 的左子树挂到 x 的右子树上
    if (y->left != tree->nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;  // 把 y 的父节点更新为 x 的父节点
    if (x->parent == tree->nil) {
        tree->root = y;  // 如果 x 是根节点，则 y 成为新根
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;  // 最后将 x 挂到 y 的左子节点
    x->parent = y;
}

// 右旋函数
void rightRotate(RBTree* tree, Node* y) {
    Node* x = y->left;  // x 为 y 的左子节点
    y->left = x->right; // 将 x 的右子树挂到 y 的左子树上
    if (x->right != tree->nil) {
        x->right->parent = y;
    }
    x->parent = y->parent;  // 把 x 的父节点更新为 y 的父节点
    if (y->parent == tree->nil) {
        tree->root = x;  // 如果 y 是根节点，则 x 成为新根
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;  // 最后将 y 挂到 x 的右子节点
    y->parent = x;
}

// 插入修复函数
void insertFixup(RBTree* tree, Node* z) {
    while (z->parent->color == RED) {  // 当 z 的父节点是红色时需要修复
        if (z->parent == z->parent->parent->left) {  // z 的父节点是祖父节点的左子节点
            Node* y = z->parent->parent->right;  // y 是 z 的叔节点
            if (y->color == RED) {  // Case 1: 叔节点是红色
                z->parent->color = BLACK;  // 将父节点设为黑色
                y->color = BLACK;  // 将叔节点设为黑色
                z->parent->parent->color = RED;  // 祖父节点设为红色
                z = z->parent->parent;  // 将 z 指向祖父节点，继续修复
            } else {
                if (z == z->parent->right) {  // Case 2: z 是右子节点
                    z = z->parent;  // 将 z 指向其父节点
                    leftRotate(tree, z);  // 左旋父节点
                }
                // Case 3: z 是左子节点
                z->parent->color = BLACK;  // 将父节点设为黑色
                z->parent->parent->color = RED;  // 将祖父节点设为红色
                rightRotate(tree, z->parent->parent);  // 右旋祖父节点
            }
        } else {  // 对称处理：z 的父节点是祖父节点的右子节点
            Node* y = z->parent->parent->left;  // y 是 z 的叔节点
            if (y->color == RED) {  // Case 1: 叔节点是红色
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {  // Case 2: z 是左子节点
                    z = z->parent;
                    rightRotate(tree, z);  // 右旋父节点
                }
                // Case 3: z 是右子节点
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(tree, z->parent->parent);  // 左旋祖父节点
            }
        }
    }
    tree->root->color = BLACK;  // 根节点必须为黑色
}

// 插入节点到红黑树中
void insert(RBTree* tree, int data) {
    Node* z = createNode(tree, data);  // 创建新节点
    Node* y = tree->nil;  // y 是 z 的父节点
    Node* x = tree->root;  // 从根节点开始查找插入位置

    while (x != tree->nil) {  // 找到合适的插入位置
        y = x;
        if (z->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;  // 设置 z 的父节点
    if (y == tree->nil) {
        tree->root = z;  // 树是空的，z 成为根节点
    } else if (z->data < y->data) {
        y->left = z;  // z 成为父节点的左子节点
    } else {
        y->right = z;  // z 成为父节点的右子节点
    }

    insertFixup(tree, z);  // 修复红黑树性质
}

// 中序遍历红黑树
void inorderTraversal(RBTree* tree, Node* node) {
    if (node != tree->nil) {
        inorderTraversal(tree, node->left);
        printf("%d ", node->data);
        inorderTraversal(tree, node->right);
    }
}


// 删除修复函数
void deleteFixup(RBTree* tree, Node* x) {
    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;  // w 是 x 的兄弟节点
            if (w->color == RED) {  // Case 1: 兄弟是红色
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {  // Case 2: 兄弟的两个子节点都是黑色
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {  // Case 3: 兄弟的右子节点是黑色
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(tree, w);
                    w = x->parent->right;
                }
                // Case 4: 兄弟的右子节点是红色
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(tree, x->parent);
                x = tree->root;
            }
        } else {  // x 是父节点的右子节点，处理对称情况
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;  // 最后将 x 设为黑色
}

// 替换节点函数
void rbTransplant(RBTree* tree, Node* u, Node* v) {
    if (u->parent == tree->nil) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// 查找最小值节点
Node* treeMinimum(RBTree* tree, Node* node) {
    while (node->left != tree->nil) {
        node = node->left;
    }
    return node;
}

// 删除节点函数
void deleteNode(RBTree* tree, Node* z) {
    Node* y = z;
    Node* x;
    int y_original_color = y->color;

    if (z->left == tree->nil) {  // z 没有左子节点
        x = z->right;
        rbTransplant(tree, z, z->right);
    } else if (z->right == tree->nil) {  // z 没有右子节点
        x = z->left;
        rbTransplant(tree, z, z->left);
    } else {  // z 有两个子节点
        y = treeMinimum(tree, z->right);  // 查找 z 的后继
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            rbTransplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbTransplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);  // 释放被删除节点的内存

    if (y_original_color == BLACK) {
        deleteFixup(tree, x);  // 如果删除的节点是黑色，修复红黑树
    }
}

// 删除值为 data 的节点
void deleteValue(RBTree* tree, int data) {
    Node* z = tree->root;
    while (z != tree->nil) {
        if (data == z->data) {
            deleteNode(tree, z);
            return;
        } else if (data < z->data) {
            z = z->left;
        } else {
            z = z->right;
        }
    }
}

// 中序遍历函数（与前面相同）
void inorderTraversal(RBTree* tree, Node* node) { /* 代码略 */ }

// 主函数
int main() {
    RBTree* tree = createRBTree();

    // 插入节点
    insert(tree, 10);
    insert(tree, 20);
    insert(tree, 30);
    insert(tree, 15);
    insert(tree, 25);
    insert(tree, 5);

    // 中序遍历
    printf("中序遍历: ");
    inorderTraversal(tree, tree->root);
    printf("\n");

    // 删除节点
    deleteValue(tree, 20);
    printf("删除20后的中序遍历: ");
    inorderTraversal(tree, tree->root);
    printf("\n");

    return 0;
}


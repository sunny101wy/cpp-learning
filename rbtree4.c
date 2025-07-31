#include <stdio.h>
#include <stdlib.h>

// ��ɫ����
#define RED 0
#define BLACK 1

// ������ڵ㶨��
typedef struct RBNode {
    int data;
    int color;
    struct RBNode *left, *right, *parent;
} RBNode;

// ���������
typedef struct RBTree {
    RBNode *root;
} RBTree;

// ȫ��Ψһ��NIL�ڱ��ڵ�
RBNode NIL_NODE = {0, BLACK, NULL, NULL, NULL};
RBNode *NIL = &NIL_NODE;  // ���п�ָ�붼ָ�����NIL�ڵ�

// �����½ڵ�
RBNode* createNode(int data) {
    RBNode* newNode = (RBNode*)malloc(sizeof(RBNode));
    newNode->data = data;
    newNode->color = RED;  // �²���ڵ�Ĭ���Ǻ�ɫ
    newNode->left = NIL;
    newNode->right = NIL;
    newNode->parent = NULL;
    return newNode;
}

// ����ת
void leftRotate(RBTree *tree, RBNode *x) {
    RBNode *y = x->right;  // y��x���Һ���
    x->right = y->left;    // ��y�����ӱ��x���Һ���
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

// ����ת
void rightRotate(RBTree *tree, RBNode *y) {
    RBNode *x = y->left;   // x��y������
    y->left = x->right;    // ��x���Һ��ӱ��y������
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

// ������������
void fixInsert(RBTree *tree, RBNode *z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode *y = z->parent->parent->right;
            if (y->color == RED) {  // Case 1: ����ڵ��Ǻ�ɫ
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {  // ����ڵ��Ǻ�ɫ
                if (z == z->parent->right) {  // Case 2: z���Һ���
                    z = z->parent;
                    leftRotate(tree, z);
                }
                // Case 3: z������
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

// ���������ڵ�
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

// ������С�ڵ�
RBNode* treeMinimum(RBNode *x) {
    while (x->left != NIL) {
        x = x->left;
    }
    return x;
}

// ɾ���ڵ���滻����
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

// ����ɾ����ĺ�������ʣ�����parent��������NIL
// x: ���������ڵ㣬����ΪNIL
// parent: x�ĸ��ڵ�
void fixDelete(RBTree *tree, RBNode *x, RBNode *parent) {
    // ��x���Ǹ��ڵ㣬��xΪ��ɫʱ����Ҫ��������
    while (x != tree->root && x->color == BLACK) {
        if (x == parent->left) { // ���x������
            RBNode *w = parent->right; // w��x���ֵܽڵ�
            // Case 1: �ֵ�w�Ǻ�ɫ
            if (w->color == RED) {
                w->color = BLACK;           // ��w���
                parent->color = RED;        // ��parent���
                leftRotate(tree, parent);   // ��parent����
                w = parent->right;          // ����wΪ�µ��Һ���
            }
            // Case 2: �ֵ�w�������ӽڵ㶼�Ǻ�ɫ
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;             // ��w��죬�ϲ���ɫ�߶�
                x = parent;                 // �������ϵ���
                parent = parent->parent;    // ����parentΪ��һ���ڵ�
            } else
			 {
                // Case 3: �ֵ�w�����ӽڵ��Ǻ�ɫ�����ӽڵ��Ǻ�ɫ
                if (w->right->color == BLACK) {
                    w->left->color = BLACK; // ��w�����ӱ��
                    w->color = RED;         // ��w���
                    rightRotate(tree, w);   // ��w����
                    w = parent->right;      // ����wΪ�µ��Һ���
                }
                // Case 4: �ֵ�w�����ӽڵ��Ǻ�ɫ
                w->color = parent->color;   // ��w����ɫ��Ϊparent����ɫ
                parent->color = BLACK;      // ��parent��Ϊ��ɫ
                w->right->color = BLACK;    // ��w���Һ�����Ϊ��ɫ
                leftRotate(tree, parent);   // ��parent����
                x = tree->root;             // ��ֹѭ������x��Ϊ���ڵ�
            }
        } else { // ���x���Һ��ӣ��Գ����
            RBNode *w = parent->left; // w��x���ֵܽڵ�
            // Case 1: �ֵ�w�Ǻ�ɫ
            if (w->color == RED) {
                w->color = BLACK;           // ��w���
                parent->color = RED;        // ��parent���
                rightRotate(tree, parent);  // ��parent����
                w = parent->left;           // ����wΪ�µ�����
            }
            // Case 2: �ֵ�w�������ӽڵ㶼�Ǻ�ɫ
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;             // ��w��죬�ϲ���ɫ�߶�
                x = parent;                 // �������ϵ���
                parent = parent->parent;    // ����parentΪ��һ���ڵ�
            } else 
			{
                // Case 3: �ֵ�w�����ӽڵ��Ǻ�ɫ�����ӽڵ��Ǻ�ɫ
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;// ��w���Һ��ӱ��
                    w->color = RED;         // ��w���
                    leftRotate(tree, w);    // ��w����
                    w = parent->left;       // ����wΪ�µ�����
                }
                // Case 4: �ֵ�w�����ӽڵ��Ǻ�ɫ
                w->color = parent->color;   // ��w����ɫ��Ϊparent����ɫ
                parent->color = BLACK;      // ��parent��Ϊ��ɫ
                w->left->color = BLACK;     // ��w��������Ϊ��ɫ
                rightRotate(tree, parent);  // ��parent����
                x = tree->root;             // ��ֹѭ������x��Ϊ���ڵ�
            }
        }
    }
    // ��x��Ϊ��ɫ����ȷ�����������
    x->color = BLACK;
}


// ɾ��������Ľڵ�
void rbDelete(RBTree *tree, RBNode *z) {
    RBNode *y = z;
    RBNode *x;
    RBNode *xParent;
    int originalColor = y->color;

    // Case 1: zֻ�����ӽڵ��û���ӽڵ�
    if (z->left == NIL) {
        x = z->right;
        xParent = z->parent;
        rbTransplant(tree, z, z->right);
    }
    // Case 2: zֻ�����ӽڵ�
    else if (z->right == NIL) {
        x = z->left;
        xParent = z->parent;
        rbTransplant(tree, z, z->left);
    }
    // Case 3: z�������ӽڵ�
    else {
        y = treeMinimum(z->right);  // �ҵ�z�ĺ�̽ڵ�
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
        fixDelete(tree, x, xParent);  // ɾ����ɫ�ڵ����Ҫ����
    }
}

// ��ʼ�������
void initializeRBTree(RBTree *tree) {
    tree->root = NIL;
}

// ��ӡ���������������
void inorderPrint(RBNode *root) {
    if (root != NIL) {
        inorderPrint(root->left);
        printf("%d(%s) ", root->data, root->color == RED ? "R" : "B");
        inorderPrint(root->right);
    }
}

// �����������Ժ����
int main() {
    RBTree tree;
    initializeRBTree(&tree);

    // ����ڵ�
    rbInsert(&tree, 20);
    rbInsert(&tree, 15);
    rbInsert(&tree, 25);
    rbInsert(&tree, 10);
    rbInsert(&tree, 5);

    printf("����������: ");
    inorderPrint(tree.root);
    printf("\n");

    // ɾ���ڵ�
    rbDelete(&tree, tree.root->left);  // ɾ��15
    printf("ɾ��15��: ");
    inorderPrint(tree.root);
    printf("\n");

    return 0;
}


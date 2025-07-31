#include <stdio.h>
#include <stdlib.h>

// ������ɫ
#define RED 0
#define BLACK 1

// �ڵ�ṹ
typedef struct Node {
    int data;                // �ڵ��ֵ
    int color;               // �ڵ����ɫ��RED �� BLACK
    struct Node* left;       // ���ӽڵ�
    struct Node* right;      // ���ӽڵ�
    struct Node* parent;     // ���ڵ�
} Node;

// ������ṹ
typedef struct RBTree {
    Node* root;              // ���ڵ�
    Node* nil;               // NIL �ڵ㣬����Ҷ��
} RBTree;

// ����һ���µĽڵ�
Node* createNode(RBTree* tree, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED;    // �²���Ľڵ��ʼΪ��ɫ
    newNode->left = tree->nil;
    newNode->right = tree->nil;
    newNode->parent = NULL;
    return newNode;
}

// ����һ���µĺ����
RBTree* createRBTree() {
    RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
    tree->nil = (Node*)malloc(sizeof(Node));
    tree->nil->color = BLACK;  // NIL �ڵ�Ĭ��Ϊ��ɫ
    tree->root = tree->nil;    // ��ʼ��ʱ�����ڵ�Ϊ NIL
    return tree;
}

// ��������
void leftRotate(RBTree* tree, Node* x) {
    Node* y = x->right;  // y Ϊ x �����ӽڵ�
    x->right = y->left;  // �� y ���������ҵ� x ����������
    if (y->left != tree->nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;  // �� y �ĸ��ڵ����Ϊ x �ĸ��ڵ�
    if (x->parent == tree->nil) {
        tree->root = y;  // ��� x �Ǹ��ڵ㣬�� y ��Ϊ�¸�
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;  // ��� x �ҵ� y �����ӽڵ�
    x->parent = y;
}

// ��������
void rightRotate(RBTree* tree, Node* y) {
    Node* x = y->left;  // x Ϊ y �����ӽڵ�
    y->left = x->right; // �� x ���������ҵ� y ����������
    if (x->right != tree->nil) {
        x->right->parent = y;
    }
    x->parent = y->parent;  // �� x �ĸ��ڵ����Ϊ y �ĸ��ڵ�
    if (y->parent == tree->nil) {
        tree->root = x;  // ��� y �Ǹ��ڵ㣬�� x ��Ϊ�¸�
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;  // ��� y �ҵ� x �����ӽڵ�
    y->parent = x;
}

// �����޸�����
void insertFixup(RBTree* tree, Node* z) {
    while (z->parent->color == RED) {  // �� z �ĸ��ڵ��Ǻ�ɫʱ��Ҫ�޸�
        if (z->parent == z->parent->parent->left) {  // z �ĸ��ڵ����游�ڵ�����ӽڵ�
            Node* y = z->parent->parent->right;  // y �� z ����ڵ�
            if (y->color == RED) {  // Case 1: ��ڵ��Ǻ�ɫ
                z->parent->color = BLACK;  // �����ڵ���Ϊ��ɫ
                y->color = BLACK;  // ����ڵ���Ϊ��ɫ
                z->parent->parent->color = RED;  // �游�ڵ���Ϊ��ɫ
                z = z->parent->parent;  // �� z ָ���游�ڵ㣬�����޸�
            } else {
                if (z == z->parent->right) {  // Case 2: z �����ӽڵ�
                    z = z->parent;  // �� z ָ���丸�ڵ�
                    leftRotate(tree, z);  // �������ڵ�
                }
                // Case 3: z �����ӽڵ�
                z->parent->color = BLACK;  // �����ڵ���Ϊ��ɫ
                z->parent->parent->color = RED;  // ���游�ڵ���Ϊ��ɫ
                rightRotate(tree, z->parent->parent);  // �����游�ڵ�
            }
        } else {  // �Գƴ���z �ĸ��ڵ����游�ڵ�����ӽڵ�
            Node* y = z->parent->parent->left;  // y �� z ����ڵ�
            if (y->color == RED) {  // Case 1: ��ڵ��Ǻ�ɫ
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {  // Case 2: z �����ӽڵ�
                    z = z->parent;
                    rightRotate(tree, z);  // �������ڵ�
                }
                // Case 3: z �����ӽڵ�
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(tree, z->parent->parent);  // �����游�ڵ�
            }
        }
    }
    tree->root->color = BLACK;  // ���ڵ����Ϊ��ɫ
}

// ����ڵ㵽�������
void insert(RBTree* tree, int data) {
    Node* z = createNode(tree, data);  // �����½ڵ�
    Node* y = tree->nil;  // y �� z �ĸ��ڵ�
    Node* x = tree->root;  // �Ӹ��ڵ㿪ʼ���Ҳ���λ��

    while (x != tree->nil) {  // �ҵ����ʵĲ���λ��
        y = x;
        if (z->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;  // ���� z �ĸ��ڵ�
    if (y == tree->nil) {
        tree->root = z;  // ���ǿյģ�z ��Ϊ���ڵ�
    } else if (z->data < y->data) {
        y->left = z;  // z ��Ϊ���ڵ�����ӽڵ�
    } else {
        y->right = z;  // z ��Ϊ���ڵ�����ӽڵ�
    }

    insertFixup(tree, z);  // �޸����������
}

// ������������
void inorderTraversal(RBTree* tree, Node* node) {
    if (node != tree->nil) {
        inorderTraversal(tree, node->left);
        printf("%d ", node->data);
        inorderTraversal(tree, node->right);
    }
}


// ɾ���޸�����
void deleteFixup(RBTree* tree, Node* x) {
    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;  // w �� x ���ֵܽڵ�
            if (w->color == RED) {  // Case 1: �ֵ��Ǻ�ɫ
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {  // Case 2: �ֵܵ������ӽڵ㶼�Ǻ�ɫ
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {  // Case 3: �ֵܵ����ӽڵ��Ǻ�ɫ
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(tree, w);
                    w = x->parent->right;
                }
                // Case 4: �ֵܵ����ӽڵ��Ǻ�ɫ
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(tree, x->parent);
                x = tree->root;
            }
        } else {  // x �Ǹ��ڵ�����ӽڵ㣬����Գ����
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
    x->color = BLACK;  // ��� x ��Ϊ��ɫ
}

// �滻�ڵ㺯��
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

// ������Сֵ�ڵ�
Node* treeMinimum(RBTree* tree, Node* node) {
    while (node->left != tree->nil) {
        node = node->left;
    }
    return node;
}

// ɾ���ڵ㺯��
void deleteNode(RBTree* tree, Node* z) {
    Node* y = z;
    Node* x;
    int y_original_color = y->color;

    if (z->left == tree->nil) {  // z û�����ӽڵ�
        x = z->right;
        rbTransplant(tree, z, z->right);
    } else if (z->right == tree->nil) {  // z û�����ӽڵ�
        x = z->left;
        rbTransplant(tree, z, z->left);
    } else {  // z �������ӽڵ�
        y = treeMinimum(tree, z->right);  // ���� z �ĺ��
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

    free(z);  // �ͷű�ɾ���ڵ���ڴ�

    if (y_original_color == BLACK) {
        deleteFixup(tree, x);  // ���ɾ���Ľڵ��Ǻ�ɫ���޸������
    }
}

// ɾ��ֵΪ data �Ľڵ�
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

// ���������������ǰ����ͬ��
void inorderTraversal(RBTree* tree, Node* node) { /* ������ */ }

// ������
int main() {
    RBTree* tree = createRBTree();

    // ����ڵ�
    insert(tree, 10);
    insert(tree, 20);
    insert(tree, 30);
    insert(tree, 15);
    insert(tree, 25);
    insert(tree, 5);

    // �������
    printf("�������: ");
    inorderTraversal(tree, tree->root);
    printf("\n");

    // ɾ���ڵ�
    deleteValue(tree, 20);
    printf("ɾ��20����������: ");
    inorderTraversal(tree, tree->root);
    printf("\n");

    return 0;
}


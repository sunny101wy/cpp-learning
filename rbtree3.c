#include <stdio.h>
#include <stdlib.h>

// ���������ڵ����ɫ
typedef enum { RED, BLACK } Color;

// ���������ڵ�ṹ
typedef struct Node {
    int data;
    Color color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

// ���������ṹ
typedef struct RBTree {
    Node* root;
} RBTree;

// ������������
Node* createNode(int data, Color color);
RBTree* createRBTree();
void leftRotate(RBTree* tree, Node* x);
void rightRotate(RBTree* tree, Node* y);
void rbTransplant(RBTree* tree, Node* u, Node* v);
Node* treeMinimum(RBTree* tree, Node* x);
void insertFixup(RBTree* tree, Node* z);
void deleteFixup(RBTree* tree, Node* x);
void insertNode(RBTree* tree, int data);
void deleteNode(RBTree* tree, Node* z);
void inorderTraversal(Node* root);
void freeTree(Node* root);

// �����µĽڵ�
Node* createNode(int data, Color color) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->color = color;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

// ���������
RBTree* createRBTree() {
    RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
    tree->root = NULL;
    return tree;
}

// ��������
void leftRotate(RBTree* tree, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
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

// ��������
void rightRotate(RBTree* tree, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL) {
        tree->root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

// �滻�ڵ� u Ϊ v
void rbTransplant(RBTree* tree, Node* u, Node* v) {
    if (u->parent == NULL) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// ����������С�ڵ�
Node* treeMinimum(RBTree* tree, Node* x) {
    while (x->left != NULL) {
        x = x->left;
    }
    return x;
}

// �����޸�����
void insertFixup(RBTree* tree, Node* z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(tree, z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
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

// ɾ���޸�����
void deleteFixup(RBTree* tree, Node* x) {
    while (x != tree->root && (x == NULL || x->color == BLACK)) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }
            if ((w->left == NULL || w->left->color == BLACK) && (w->right == NULL || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right == NULL || w->right->color == BLACK) {
                    if (w->left != NULL) {
                        w->left->color = BLACK;
                    }
                    w->color = RED;
                    rightRotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right != NULL) {
                    w->right->color = BLACK;
                }
                leftRotate(tree, x->parent);
                x = tree->root;
            }
        } else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }
            if ((w->right == NULL || w->right->color == BLACK) && (w->left == NULL || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left == NULL || w->left->color == BLACK) {
                    if (w->right != NULL) {
                        w->right->color = BLACK;
                    }
                    w->color = RED;
                    leftRotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left != NULL) {
                    w->left->color = BLACK;
                }
                rightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    if (x != NULL) {
        x->color = BLACK;
    }
}

// ����ڵ�
void insertNode(RBTree* tree, int data) {
    Node* z = createNode(data, RED);
    Node* y = NULL;
    Node* x = tree->root;

    while (x != NULL) {
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

    insertFixup(tree, z);
}

// ɾ���ڵ�
void deleteNode(RBTree* tree, Node* z) {
    Node* y = z;
    Node* x;
    Color y_original_color = y->color;

    if (z->left == NULL) {
        x = z->right;
        rbTransplant(tree, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        rbTransplant(tree, z, z->left);
    } else {
        y = treeMinimum(tree, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != NULL) {
                x->parent = y;
            }
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

    free(z);

    if (y_original_color == BLACK) {
        if (x == NULL) {
            x = tree->root;
        }
        deleteFixup(tree, x);
    }
}

// ���������
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// �ͷ������ڴ�
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// ��������ʾ
int main() {
    RBTree* tree = createRBTree();

    insertNode(tree, 10);
    insertNode(tree, 20);
    insertNode(tree, 30);
    insertNode(tree, 15);
    insertNode(tree, 25);

    printf("Inorder traversal of the tree:\n");
    inorderTraversal(tree->root);
    printf("\n");

    // Example of deleting a node
    Node* nodeToDelete = tree->root->left;  // Example: deleting a specific node
    deleteNode(tree, nodeToDelete);

    printf("Inorder traversal after deletion:\n");
    inorderTraversal(tree->root);
    printf("\n");

    freeTree(tree->root);
    free(tree);

    return 0;
}


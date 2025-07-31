#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



#define RED 0     // ��ɫ�ڵ㶨��
#define BLACK 1   // ��ɫ�ڵ㶨��

// ������ڵ�ṹ
typedef struct RBTreeNode {
    int data;                // �ڵ�洢������
    int color;               // �ڵ���ɫ��RED �� BLACK
    struct RBTreeNode *left;   // ���ӽڵ�
    struct RBTreeNode *right;  // ���ӽڵ�
    struct RBTreeNode *parent; // ���ڵ�
} RBTreeNode;

// ������ṹ
typedef struct RBTree {
    RBTreeNode *root;  // ���ĸ��ڵ�
    RBTreeNode *nil;   // �ڱ��ڵ㣬��ʾҶ�ӽڵ�
} RBTree;

// �����ڱ��ڵ�
RBTreeNode *createNilNode() {
    RBTreeNode *nilNode = (RBTreeNode *)malloc(sizeof(RBTreeNode));
    nilNode->color = BLACK;
    nilNode->left = nilNode->right = nilNode->parent = NULL;
    return nilNode;
}

// ���������
RBTree *createRBTree() {
    RBTree *tree = (RBTree *)malloc(sizeof(RBTree));
    tree->nil = createNilNode();  // ��ʼ���ڱ��ڵ�
    tree->root = tree->nil;  // ��ʼ�����ڵ�Ϊ��
    return tree;
}

// ������������
void inorderTraversal(RBTreeNode *node, RBTreeNode *nil) {
    if (node != nil) {
        inorderTraversal(node->left, nil);
        printf("%d ", node->data);
        inorderTraversal(node->right, nil);
    }
}

// �������������ڵ�x�������������ӽڵ�����
void leftRotate(RBTree *tree, RBTreeNode *x) {
    RBTreeNode *y = x->right;  // ����yΪx�����ӽڵ�
    x->right = y->left;        // ��y�����ӽڵ���Ϊx�����ӽڵ�
    if (y->left != tree->nil)  // ���y�����ӽڵ���ڣ������丸�ڵ�ָ��
        y->left->parent = x;
    y->parent = x->parent;     // ��y�ĸ��ڵ�ָ��x�ĸ��ڵ�
    if (x->parent == tree->nil) // ���x�Ǹ��ڵ㣬���¸��ڵ�Ϊy
        tree->root = y;
    else if (x == x->parent->left)  // ���x�����ӽڵ㣬��y��Ϊ�丸�ڵ�����ӽڵ�
        x->parent->left = y;
    else  // ���x�����ӽڵ㣬��y��Ϊ�丸�ڵ�����ӽڵ�
        x->parent->right = y;
    y->left = x;  // ��x��Ϊy�����ӽڵ�
    x->parent = y; // ����x�ĸ��ڵ�Ϊy
}

// �������������ڵ�y�������������ӽڵ�����
void rightRotate(RBTree *tree, RBTreeNode *y) {
    RBTreeNode *x = y->left;   // ����xΪy�����ӽڵ�
    y->left = x->right;        // ��x�����ӽڵ���Ϊy�����ӽڵ�
    if (x->right != tree->nil) // ���x�����ӽڵ���ڣ������丸�ڵ�ָ��
        x->right->parent = y;
    x->parent = y->parent;     // ��x�ĸ��ڵ�ָ��y�ĸ��ڵ�
    if (y->parent == tree->nil) // ���y�Ǹ��ڵ㣬���¸��ڵ�Ϊx
        tree->root = x;
    else if (y == y->parent->left) // ���y�����ӽڵ㣬��x��Ϊ�丸�ڵ�����ӽڵ�
        y->parent->left = x;
    else  // ���y�����ӽڵ㣬��x��Ϊ�丸�ڵ�����ӽڵ�
        y->parent->right = x;
    x->right = y;  // ��y��Ϊx�����ӽڵ�
    y->parent = x; // ����y�ĸ��ڵ�Ϊx
}


// ������޸��������ƽ��
void insertFixUp(RBTree *tree, RBTreeNode *z) 
{	
    while (z->parent->color == RED) 
	{ // ������ڵ��Ǻ�ɫ����Ҫ�޸�
        if (z->parent == z->parent->parent->left) 
		{  // ���ڵ����游�ڵ�����ӽڵ�
            RBTreeNode *y = z->parent->parent->right; // y���游�ڵ�����ӽڵ㣨����ڵ㣩
            if (y->color == RED) {  // Case 1: ����ڵ��Ǻ�ɫ
                z->parent->color = BLACK;  // �����ڵ���Ϊ��ɫ
                y->color = BLACK;          // ������ڵ���Ϊ��ɫ
                z->parent->parent->color = RED; // ���游�ڵ���Ϊ��ɫ
                z = z->parent->parent;     // ��zָ���游�ڵ�
            } else {  // Case 2 �� 3: ����ڵ��Ǻ�ɫ
                if (z == z->parent->right) {  // Case 2: z�����ӽڵ�
                    z = z->parent;
                    leftRotate(tree, z);  // �������ڵ�
                }
                z->parent->color = BLACK;  // Case 3: �����ڵ���Ϊ��ɫ
                z->parent->parent->color = RED;  // ���游�ڵ���Ϊ��ɫ
                rightRotate(tree, z->parent->parent); // �����游�ڵ�
            }
        } 
		else 
		{  // ���ڵ����游�ڵ�����ӽڵ�
            RBTreeNode *y = z->parent->parent->left;  // y���游�ڵ�����ӽڵ㣨����ڵ㣩
            if (y->color == RED) {  // Case 1: ����ڵ��Ǻ�ɫ
                z->parent->color = BLACK;  // �����ڵ���Ϊ��ɫ
                y->color = BLACK;          // ������ڵ���Ϊ��ɫ
                z->parent->parent->color = RED; // ���游�ڵ���Ϊ��ɫ
                z = z->parent->parent;     // ��zָ���游�ڵ�
            } else {  // Case 2 �� 3: ����ڵ��Ǻ�ɫ
                if (z == z->parent->left) {  // Case 2: z�����ӽڵ�
                    z = z->parent;
                    rightRotate(tree, z); // �������ڵ�
                }
                z->parent->color = BLACK;  // Case 3: �����ڵ���Ϊ��ɫ
                z->parent->parent->color = RED;  // ���游�ڵ���Ϊ��ɫ
                leftRotate(tree, z->parent->parent); // �����游�ڵ�
            }
        }
    }
    tree->root->color = BLACK; // ȷ�����ڵ�ʼ��Ϊ��ɫ
}


// �����½ڵ㵽�������
void insert(RBTree *tree, int data) {
    RBTreeNode *z = (RBTreeNode *)malloc(sizeof(RBTreeNode)); // �����½ڵ��ڴ�
    z->data = data;                // �����½ڵ�����
    z->left = z->right = z->parent = tree->nil; // ��ʼ���½ڵ�������ӽڵ�͸��ڵ�ָ��
    z->color = RED;  // �²���Ľڵ�Ĭ��Ϊ��ɫ

    RBTreeNode *y = tree->nil;   // yΪ���е���ʱ�ڵ㣬�����ҵ�����λ��
    RBTreeNode *x = tree->root;  // �Ӹ��ڵ㿪ʼ���Ҳ���λ��


    while (x != tree->nil) {
        y = x;
        if (z->data == x->data) {
            // �ڵ��Ѵ��ڣ�����ʽ������ֱ�ӷ��ػ��������
            printf("�ڵ� %d �Ѵ��ڣ����Բ��롣\n", data);
            free(z);
            return;  // ���Բ���
        }
        else if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }
//    while (x != tree->nil) {  // ���Ҳ���λ��
//        y = x;
//        if (z->data < x->data)
//            x = x->left;
//        else
//            x = x->right;
//    }

    z->parent = y;  // �����½ڵ�ĸ��ڵ�Ϊ�ҵ��Ĳ���λ��
    if (y == tree->nil)  // �����Ϊ�գ��½ڵ�Ϊ���ڵ�
        tree->root = z;
    else if (z->data < y->data)  // ����½ڵ�С�ڸ��ڵ㣬��Ϊ���ӽڵ����
        y->left = z;
    else  // ������Ϊ���ӽڵ����
        y->right = z;

    insertFixUp(tree, z);  // �޸������������
}


// ɾ���ڵ���޸��������ƽ��
void deleteFixUp(RBTree *tree, RBTreeNode *x) {
    while (x != tree->root && x->color == BLACK) {  // x�Ǻ�ɫ�Ҳ�Ϊ���ڵ㣬��Ҫ�޸�
        if (x == x->parent->left) {  // x�����ӽڵ�
            RBTreeNode *w = x->parent->right;  // w��x���ֵܽڵ�
            if (w->color == RED) {  // Case 1: �ֵܽڵ��Ǻ�ɫ
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {  // Case 2: �ֵܽڵ���ӽڵ㶼�Ǻ�ɫ
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {  // Case 3: �ֵܽڵ�����ӽڵ��Ǻ�ɫ
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;  // Case 4: �ֵܽڵ�����ӽڵ��Ǻ�ɫ
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(tree, x->parent);
                x = tree->root;
            }
        } else {  // x�����ӽڵ�
            RBTreeNode *w = x->parent->left;  // w��x���ֵܽڵ�
            if (w->color == RED) {  // Case 1: �ֵܽڵ��Ǻ�ɫ
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {  // Case 2: �ֵܽڵ���ӽڵ㶼�Ǻ�ɫ
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {  // Case 3: �ֵܽڵ�����ӽڵ��Ǻ�ɫ
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;  // Case 4: �ֵܽڵ�����ӽڵ��Ǻ�ɫ
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK; // ��x��Ϊ��ɫ
}

// �滻�ڵ�u��v
void rbTransplant(RBTree *tree, RBTreeNode *u, RBTreeNode *v) {
    if (u->parent == tree->nil)  // u�Ǹ��ڵ㣬ֱ���滻Ϊv
        tree->root = v;
    else if (u == u->parent->left)  // u�����ӽڵ㣬�滻Ϊv
        u->parent->left = v;
    else  // u�����ӽڵ㣬�滻Ϊv
        u->parent->right = v;
    v->parent = u->parent;  // ����v�ĸ��ڵ�
}

// ɾ��������еĽڵ�
void delete(RBTree *tree, RBTreeNode *z) {
    RBTreeNode *y = z;  // y�Ǵ�ɾ���Ľڵ�
    RBTreeNode *x;      // x�������޸��Ľڵ�
    int y_original_color = y->color;  // �����ɾ���ڵ����ɫ

    if (z->left == tree->nil) {  // ���z�����ӽڵ�Ϊ�գ�ֱ���滻Ϊ���ӽڵ�
        x = z->right;
        rbTransplant(tree, z, z->right);
    } else if (z->right == tree->nil) {  // ���z�����ӽڵ�Ϊ�գ�ֱ���滻Ϊ���ӽڵ�
        x = z->left;
        rbTransplant(tree, z, z->left);
    } else {  // z�������ӽڵ�
        y = z->right;
        while (y->left != tree->nil)  // ����z�ĺ�̽ڵ�
            y = y->left;
        y_original_color = y->color;  // �����̽ڵ����ɫ
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

    if (y_original_color == BLACK)  // �����ɾ���Ľڵ��Ǻ�ɫ����Ҫ�޸�
        deleteFixUp(tree, x);
    free(z);  // �ͷ�ɾ���Ľڵ�
}



// ������ʾ��
int main() {
    RBTree *tree = createRBTree();
    insert(tree, 10);
    insert(tree, 20);
    insert(tree, 30);
    insert(tree, 15);

    printf("������������: ");
    inorderTraversal(tree->root, tree->nil);
    printf("\n");

    delete(tree, tree->root->right);  // ɾ���ڵ�

    printf("ɾ���ڵ���������������: ");
    inorderTraversal(tree->root, tree->nil);
    printf("\n");

    return 0;
}


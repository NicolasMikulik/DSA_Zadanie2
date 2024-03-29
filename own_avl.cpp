//
// Created by nicolas on 27. 10. 2019.
//

/*
// uloha3-3.c -- Nicolas Mikulík, 9.10.2019 16:11

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

struct Node{
    unsigned int key;
    int height;
    struct Node *left;
    struct Node *right;
};

int max(int a, int b) {return (a>b ? a : b);}
unsigned int min(unsigned int a, unsigned int b) {return (a<b ? a : b);}

int getHeight(struct Node* node){
    if(node == NULL)
        return 0;
    else
        return node->height;
}

int getBalance(struct Node* node){
    if(node == NULL)
        return 0;
    return getHeight(node->right) - getHeight(node->left);
}

struct Node* newNode(unsigned int key){
    struct Node *node=(struct Node*)malloc(sizeof(struct Node));
    node->key=key;
    node->left=NULL;
    node->right=NULL;
    node->height=1;
    return node;
}

struct Node* rotateLeft(struct Node* pivot){
    struct Node* pivotRightchild = pivot->right;
    struct Node* leftchild = pivotRightchild->left;

    pivotRightchild->left = pivot;
    pivot->right = leftchild;

    pivot->height = 1 + max(pivot->left->height, pivot->right->height);
    pivotRightchild->height = 1 + max(pivotRightchild->left->height, pivotRightchild->right->height);
    return pivot;
}

struct Node* rotateRight(struct Node* pivot){
    struct Node* pivotLeftchild = pivot->left;
    struct Node* rightchild = pivotLeftchild->right;

    pivotLeftchild->right = pivot;
    pivot->left = rightchild;

    pivot->height = 1 + max(pivot->left->height, pivot->right->height);
    pivotLeftchild->height = 1 + max(pivotLeftchild->left->height, pivotLeftchild->right->height);
    return pivot;
}

struct Node* insert(struct Node* node, unsigned int key){
    if(node == NULL)
        return (newNode(key));
    if(key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    node->height =  + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if(balance < -1){ //left subtree is longer
        if(node->left->key > key){ //left child
            rotateRight(node);
        }
        if(key > node->left->key){ //right child
            rotateLeft(node->left);
            rotateRight(node);
        }
    }
    if(balance > 1){ //right subtree is longer
        if(node->right->key < key){ //right child
            rotateLeft(node);
        }
        if(key < node->right->key){ //left child
            rotateRight(node->right);
            rotateLeft(node);
        }
    }
    return node;
}

bool checkPresence(struct Node* node, unsigned int key){
    if(node == NULL){
        return false;}
    if(node->key == key){
        return true;}
    if(key < node->key){
        return checkPresence(node->left, key);}
    if(node->key < key){
        return checkPresence(node->right, key);}
    return false;
}

void inorderTraversal(struct Node *root, unsigned int * array, int *index){
    if(root == NULL)
        return;
    else{
        if(root != NULL){
            inorderTraversal(root->left, array, index);
            array[*index] = root->key;
            *index = *index + 1;
            inorderTraversal(root->right, array, index);
        }
    }
    return;
}


int main()
{
    // sem napis svoje riesenie
    unsigned int *array = (unsigned int *)malloc(100000*sizeof(unsigned int));
    int index = 0;
    unsigned int input = 0;
    scanf("%u",&input);
    struct Node *root=newNode(input);
    printf("-1\n");
    while((scanf("%u",&input))==1){
        if(!checkPresence(root,input)){
            insert(root,input);
            index = 0;
            inorderTraversal(root,array,&index);
            printClose(root,array,input,index);
        }
        else{
            printClose(root,array,input,index);
        }
        //printNear(root,input);
    }
    return 0;
}
 */

/*29 October 2019
struct Node{
    int key;
    int height;
    struct Node *left;
    struct Node *right;
};

int max(int a, int b) {return (a>b ? a : b);}
int min( int a,  int b) {return (a<b ? a : b);}

int getHeight(struct Node* node){
    if(node == NULL)
        return 0;
    else
        return node->height;
}

int getBalance(struct Node* node){
    if(node == NULL)
        return 0;
    return getHeight(node->right) - getHeight(node->left);
}

struct Node* newNode( int key){
    struct Node *node=(struct Node*)malloc(sizeof(struct Node));
    node->key=key;
    node->left=NULL;
    node->right=NULL;
    node->height=1;
    return node;
}

struct Node* rotateLeft(struct Node* pivot){
    struct Node* pivotRightchild = pivot->right;
    struct Node* leftchild = pivotRightchild->left;

    pivotRightchild->left = pivot;
    pivot->right = leftchild;

    pivot->height = 1 + max(pivot->left->height, pivot->right->height);
    pivotRightchild->height = 1 + max(pivotRightchild->left->height, pivotRightchild->right->height);
    return pivot;
}

struct Node* rotateRight(struct Node* pivot){
    struct Node* pivotLeftchild = pivot->left;
    struct Node* rightchild = pivotLeftchild->right;

    pivotLeftchild->right = pivot;
    pivot->left = rightchild;

    pivot->height = 1 + max(pivot->left->height, pivot->right->height);
    pivotLeftchild->height = 1 + max(pivotLeftchild->left->height, pivotLeftchild->right->height);
    return pivot;
}

struct Node* insert(struct Node* node, int key){
    if(node == NULL)
        return (newNode(key));
    if(key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if(balance < -1){ //left subtree is longer
        if(node->left->key > key){ //left child
            rotateRight(node);
        }
        if(key > node->left->key){ //right child
            rotateLeft(node->left);
            rotateRight(node);
        }
    }
    if(balance > 1){ //right subtree is longer
        if(node->right->key < key){ //right child
            rotateLeft(node);
        }
        if(key < node->right->key){ //left child
            rotateRight(node->right);
            rotateLeft(node);
        }
    }
    return node;
}

bool checkPresence(struct Node* node, int key){
    if(node == NULL){
        return false;}
    if(node->key == key){
        return true;}
    if(key < node->key){
        return checkPresence(node->left, key);}
    if(node->key < key){
        return checkPresence(node->right, key);}
    return false;
}

void inorderTraversal(struct Node *root, int * array, int *index){
    if(root == NULL)
        return;
    else{
        if(root != NULL){
            inorderTraversal(root->left, array, index);
            array[*index] = root->key;
            *index = *index + 1;
            inorderTraversal(root->right, array, index);
        }
    }
    return;
}
 */
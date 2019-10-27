#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

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
    struct Node* pivotRightChiu = pivot->right;
    struct Node* leftChiu = pivotRightChiu->left;

    pivotRightChiu->left = pivot;
    pivot->right = leftChiu;

    pivot->height = 1 + max(pivot->left->height, pivot->right->height);
    pivotRightChiu->height = 1 + max(pivotRightChiu->left->height, pivotRightChiu->right->height);
    return pivot;
}

struct Node* rotateRight(struct Node* pivot){
    struct Node* pivotLeftChiu = pivot->left;
    struct Node* rightChiu = pivotLeftChiu->right;

    pivotLeftChiu->right = pivot;
    pivot->left = rightChiu;

    pivot->height = 1 + max(pivot->left->height, pivot->right->height);
    pivotLeftChiu->height = 1 + max(pivotLeftChiu->left->height, pivotLeftChiu->right->height);
    return pivot;
}

struct Node* insert(struct Node* node, int key){
    if(node == NULL)
        return (newNode(key));
    if(key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    node->height =  + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if(balance < -1){ //left subtree is longer
        if(node->left->key > key){ //left chiu
            rotateRight(node);
        }
        if(key > node->left->key){ //right chiu
            rotateLeft(node->left);
            rotateRight(node);
        }
    }
    if(balance > 1){ //right subtree is longer
        if(node->right->key < key){ //right chiu
            rotateLeft(node);
        }
        if(key < node->right->key){ //left chiu
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

// ukazkovy test
int main(void)
{

    int index = 0, key = 0, numberSet[500];;
    FILE *source = fopen("./one_thousand_Source.txt", "r");
    FILE *search = fopen("./one_thousand_Search.txt","r");
    if(source == nullptr){printf("Unsuccessful opening of source file.\n"); exit(1);}
    if(search == nullptr){printf("Unsuccessful opening of search file.\n"); exit(1);}
    fscanf(source, "%d", &key);
    struct Node *root=newNode(key);
    while(fscanf(source, "%d", &key) == 1){
        printf("%d\n", key);
        if(!checkPresence(root,key))
            insert(root,key);
        else
            printf("Key %d already present in AVL tree.\n");
    }

    index=0;
    while(fscanf(search, "%d", &numberSet[index]) == 1){
        printf("%d ", numberSet[index]);
        index++;}
    for (index = 0; index < 500; index++)
        if(!checkPresence(root,numberSet[index]))
            printf("Key %d is not present in AVL tree.\n");
        else
            printf("Key %d FOUND in AVL tree.\n");
    fclose(source);
    fclose(search);
    return 0;
}
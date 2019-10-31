// uloha3-1.c -- Nicolas Mikulík, 7.10.2019 08:16

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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

struct Node* newNode(int key){
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
    //printf("Height of root is %d.\n", getHeight);
    if(node == NULL)
        return newNode(key);
    if(key < node->key){
        printf("INserting %d to the left of %d\n", key, node->key);
        node->left = insert(node->left, key);}
    else{
        printf("INserting %d to the RIGHT of %d\n", key, node->key);
        node->right = insert(node->right, key);}
    node->height =  + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if(balance < -1){ //left subtree is longer
        if(node->left->key > key){ //left chiu
            rotateRight(node);
        }
        else{ //right chiu
            rotateLeft(node->left);
            rotateRight(node);
        }
    }
    if(balance > 1){ //right subtree is longer
        if(node->right->key < key){ //right chiu
            rotateLeft(node);
        }
        else{ //left chiu
            rotateRight(node->right);
            rotateLeft(node);
        }
    }
    return node;
}

struct Node* checkPresence(struct Node* node, int key){
    if(node == NULL || node->key == key){
        return node;}
    if(key < node->key){
        return checkPresence(node->left, key);}
    return checkPresence(node->right, key);
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
    /*struct Node *root=newNode(277);
    //root = insert(root,-117);
    printf("root %d\n", root->key);
    insert(root,386);
    insert(root, -156);
    insert(root, -117);
    printf("root->left %d root %d root->right %d\n", root->left->key, root->key, root->left->right->key);*/
    //unsigned int *array = (unsigned int *)malloc(100000*sizeof(unsigned int));
    int index = 0, key = 0, numberSet[500];
    struct timespec tstart={0,0}, tend={0,0};
    FILE *source = fopen("./one_thousand_Source.txt", "r");
    FILE *searchInput = fopen("./one_thousand_Search.txt","r");
    FILE *insertRecord = fopen("./one_thousand_AVL_times.txt", "w");
    if(source == NULL){printf("Unsuccessful opening of source file.\n"); exit(1);}
    if(searchInput == NULL){printf("Unsuccessful opening of search file.\n"); exit(1);}
    if(insertRecord == NULL){printf("Unsuccessful opening of recording file.\n"); exit(1);}
    fscanf(source, "%d", &key);
    struct Node *root=newNode(key);
    while(fscanf(source, "%d", &key) == 1){
        printf("%d\n", key);
        clock_gettime(CLOCK_MONOTONIC, &tstart);
        if(NULL == checkPresence(root,key)){
            insert(root,key);
            clock_gettime(CLOCK_MONOTONIC, &tend);
            fprintf(insertRecord, "%.9f\n", ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) -
                                            ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));
        }
        else{
            clock_gettime(CLOCK_MONOTONIC, &tend);
            printf("Key %d already present in AVL tree.\n", key);
            fprintf(insertRecord, "%.9f\n", ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) -
                                            ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));
        }
    }
    /*index = 0;
    inorder(root);
    for(int i = 0; i < index; i++)
        printf("%d < ",array[index]);*/
    index=0;
    while(fscanf(searchInput, "%d", &numberSet[index]) == 1){
        printf("%d ", numberSet[index]);
        index++;}

    for (index = 0; index < 500; index++){
        if(NULL == checkPresence(root,numberSet[index]))
            printf("Key %d is not present in AVL tree.\n",numberSet[index]);
        else
            printf("Key %d FOUND in AVL tree.\n",numberSet[index]);
    }
    fclose(source);
    fclose(searchInput);
    fclose(insertRecord);
    return 0;
}
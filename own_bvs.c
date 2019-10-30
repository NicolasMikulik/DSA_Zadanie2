//
// Created by nicolas on 29. 10. 2019.
//
/*
// uloha3-1.c -- Nicolas Mikulík, 7.10.2019 08:16

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node{
    int value;
    struct node *left;
    struct node *right;
};

struct node* newNode(int value){
    struct node *node=(struct node*)malloc(sizeof(struct node));
    node->value=value;
    node->left=NULL;
    node->right=NULL;
    return node;
}

bool checkPresence(struct node* node, int value, int depth){
    if(node == NULL)
        return false;
    if(node->value == value){
        printf("%d\n",depth);
        return true;
    }
    bool leftPresence = checkPresence(node->left, value, depth+1);
    bool rightPresence = checkPresence(node->right, value, depth+1);
    return leftPresence || rightPresence;
}
void addNode(struct node* node, int value, int depth){
    if(node == NULL){
        node = newNode(value);
        printf("%d\n",depth+1);
        return;
    }
    if(node->value > value && node->left == NULL){
        printf("%d\n",depth+1);
        node->left = newNode(value);
        return;
    }
    if(node->value > value && node->left != NULL){
        addNode(node->left,value,depth+1);
        return;
    }
    if(node->value < value && node->right == NULL){
        node->right = newNode(value);
        printf("%d\n",depth+1);
        return;
    }
    if(node->value < value && node->right != NULL){
        addNode(node->right,value,depth+1);
        return;
    }
}
int main()
{
    // sem napis svoje riesenie
    int input = 0;
    scanf("%d",&input);
    struct node *root=newNode(input);
    printf("0\n");
    while((scanf("%d",&input))==1){
        if(!checkPresence(root,input,0)){
            addNode(root,input,0);
        }
    }
    return 0;
}
 */

/*vlastny main pre meranie casu vlozenia vlastneho BVS
int main(void)
{
    //unsigned int *array = (unsigned int *)malloc(100000*sizeof(unsigned int));
    int index = 0, key = 0, numberSet[25000];
    struct timespec tstart={0,0}, tend={0,0};
    FILE *source = fopen("./fifty_thousand_Source.txt", "r");
    FILE *searchInput = fopen("./fifty_thousand_Search.txt","r");
    FILE *insertRecord = fopen("./fifty_thousand_BST_times.txt", "w");
    if(source == NULL){printf("Unsuccessful opening of source file.\n"); exit(1);}
    if(searchInput == NULL){printf("Unsuccessful opening of search file.\n"); exit(1);}
    fscanf(source, "%d", &key);
    struct node *root=newNode(key);
    while(fscanf(source, "%d", &key) == 1){
        printf("%d\n", key);
        clock_gettime(CLOCK_MONOTONIC, &tstart);
        if(checkPresence(root,key) == NULL){
            //printf("Adding key %d into the BST.\n",key);
            addNode(root,key);
            clock_gettime(CLOCK_MONOTONIC, &tend);
            fprintf(insertRecord, "%.9f\n", ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) -
                                            ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));
        }
        else{
            clock_gettime(CLOCK_MONOTONIC, &tend);
            fprintf(insertRecord, "%.9f\n", ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) -
                                        ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));
            printf("Key %d already present in BST.\n",key);
        }
    }

    index=0;
    while(fscanf(searchInput, "%d", &numberSet[index]) == 1){
        printf("%d ", numberSet[index]);
        index++;}

    for (index = 0; index < 25000; index++){
        if(checkPresence(root, numberSet[index]) == NULL)
            printf("Key %d is not present in BST.\n", numberSet[index]);
        else
            printf("Key %d FOUND in BST.\n", numberSet[index]);
        }
fclose(source);
fclose(searchInput);
fclose(insertRecord);
return 0;
}
 */
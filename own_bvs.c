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
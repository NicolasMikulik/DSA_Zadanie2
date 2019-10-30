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

struct node *checkPresence(struct node* node, int value){
    if(node == NULL || node->value == value){
        return node;
    }
    if(node->value > value){
        return checkPresence(node->left,value);
    }
    return checkPresence(node->right,value);
}
void addNode(struct node* node, int value){
    if(node == NULL){
        node = newNode(value);
        return;
    }
    if(node->value > value && node->left == NULL){
        node->left = newNode(value);
        return;
    }
    if(node->value > value && node->left != NULL){
        addNode(node->left,value);
        return;
    }
    if(node->value < value && node->right == NULL){
        node->right = newNode(value);
        return;
    }
    if(node->value < value && node->right != NULL){
        addNode(node->right,value);
        return;
    }
}

void inorderTraversal(struct node *root, unsigned int * array, int *index){
    if(root == NULL)
        return;
    else{
        inorderTraversal(root->left, array, index);
        array[*index] = root->value;
        *index = *index + 1;
        inorderTraversal(root->right, array, index);
    }
}

void inorder(struct node *root){
    if(root == NULL)
        return;
    else{
        inorder(root->left);
        printf("%d < ", root->value);
        inorder(root->right);
    }
}

// ukazkovy test
int main(void)
{   /*struct node *root=newNode(15);
    addNode(root,10);
    addNode(root, 20);
    addNode(root, 2);
    addNode(root, 19);
    inorder(root);
    if(checkPresence(root,19) == NULL){
        printf("19 not in BST\n");
    }
    else
        printf("19 FOUND\n");
    if(checkPresence(root,3) == NULL){
        printf("3 not in BST\n");
    }
    else
        printf("3 FOUND\n");
    if(checkPresence(root,-20) == NULL){
        printf("-20 not in BST\n");
    }
    else
        printf("-20 FOUND\n");*/

    unsigned int *array = (unsigned int *)malloc(100000*sizeof(unsigned int));
    int index = 0, key = 0, numberSet[500];;
    FILE *source = fopen("./one_thousand_Source.txt", "r");
    FILE *searchInput = fopen("./one_thousand_Search.txt","r");
    if(source == NULL){printf("Unsuccessful opening of source file.\n"); exit(1);}
    if(searchInput == NULL){printf("Unsuccessful opening of search file.\n"); exit(1);}
    fscanf(source, "%d", &key);
    struct node *root=newNode(key);
    while(fscanf(source, "%d", &key) == 1){
        printf("%d\n", key);
        if(checkPresence(root,key) == NULL){
            printf("Adding key %d into the BST.\n",key);
            addNode(root,key);
        }
        else
            printf("Key %d already present in BST.\n",key);
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
        if(checkPresence(root, numberSet[index]) == NULL)
            printf("Key %d is not present in BST.\n", numberSet[index]);
        else
            printf("Key %d FOUND in BST.\n", numberSet[index]);
    }
    fclose(source);
    fclose(searchInput);

    return 0;
}
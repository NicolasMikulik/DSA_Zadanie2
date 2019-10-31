#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// uloha5-1.c -- Nicolas Mikulík, 20.10.2019 20:47

#include <stdio.h>
#include <stdlib.h>
#define SIZE 50000

struct Item{
    int key;
    struct Item *next;
};

int hashFunctionOne(int key){
    if(key < 1){
        key = key * (-1);
    }
    int number = key, hash = 0;
    while(number > 10){
        hash = 31*hash + number%10;
        number /= 10;
    }
    return hash;
}

int compressFunctionTwo(int key){
    int hash = hashFunctionOne(key);
    int a = 24, b = 5, N = 49999;
    return (a*hash + b) % N;
}

void insert(struct Item **hashArray, int key) {
    //printf("Inserting %d\n",key);
    int hashIndex = compressFunctionTwo(key);
    if(hashArray[hashIndex] == NULL){
        hashArray[hashIndex] = (struct Item *)malloc(sizeof(struct Item));
        hashArray[hashIndex]->next = hashArray[hashIndex];
        hashArray[hashIndex]->key = key;
        //printf("Inserted key %d into an empty linked list at index %d.\n", key, hashIndex);
        return;
    }
    else{
        struct Item *start = hashArray[hashIndex];
        struct Item *traversing = hashArray[hashIndex];
        while(traversing->next != start){
            if(traversing->key == key){
                //printf("Key %d already present in own hash table at index %d.\n", key, hashIndex);
                return;
            }
            traversing = traversing->next;
        }
        struct Item *added = (struct Item *)malloc(sizeof(struct Item));
        added->key = key;
        added->next = start;
        traversing->next = added;
        //printf("Inserted key %d into an existing linked list at index %d.\n", key, hashIndex);
        return;
    }
}


struct Item *find(struct Item **hashArray, int key) {
    int hashIndex = compressFunctionTwo(key);
    if(hashArray[hashIndex] == NULL){
        //printf("Key %d not present in own hash table.\n",key);
        return NULL;
    }
    if(hashArray[hashIndex]->key == key){
        //printf("Key %d found in own hash table on index %d.\n", key, hashIndex);
        return hashArray[hashIndex];
    }
    else{
        struct Item *start = hashArray[hashIndex];
        struct Item *traversing = hashArray[hashIndex]->next;
        while(traversing->next != start){
            if(traversing->key == key){
                //printf("Key %d found in own hash table at index %d.\n", key, hashIndex);
                return hashArray[hashIndex];
            }
            traversing = traversing->next;
        }
        //printf("Key %d not present in own hash table.\n",key);
        return NULL;
    }
}

// ukazkovy test
int main(void)
{
    int index = 0, key = 0, numberSet[25000];
    struct Item *hashArray[SIZE];
    for(index=0;index<SIZE;index++)
        hashArray[index] = NULL;
    struct timespec tstart={0,0}, tend={0,0};
    FILE *source = fopen("./fifty_thousand_Source.txt", "r");
    FILE *searchInput = fopen("./fifty_thousand_Search.txt","r");
    FILE *insertRecord = fopen("./fifty_thousand_ownHash_times.txt", "w");
    if(source == NULL){printf("Unsuccessful opening of source file.\n"); exit(1);}
    if(searchInput == NULL){printf("Unsuccessful opening of search file.\n"); exit(1);}
    if(insertRecord == NULL){printf("Unsuccessful opening of recording file.\n"); exit(1);}
    //fscanf(source, "%d", &key);
    struct node *root=NULL;//newNode(key);
    while(fscanf(source, "%d", &key) == 1){
        printf("%d\n", key);
        clock_gettime(CLOCK_MONOTONIC, &tstart);
        insert(hashArray,key);
        clock_gettime(CLOCK_MONOTONIC, &tend);
        fprintf(insertRecord, "%.9f\n", ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) -
                                            ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));
    }
    /*index = 0;
    inorder(root);
    for(int i = 0; i < index; i++)
        printf("%d < ",array[index]);*/
    index=0;
    while(fscanf(searchInput, "%d", &numberSet[index]) == 1){
        printf("%d ", numberSet[index]);
        index++;}

    for (index = 0; index < 25000; index++){
        find(hashArray, numberSet[index]);}
    fclose(source);
    fclose(searchInput);
    fclose(insertRecord);
    return 0;
}
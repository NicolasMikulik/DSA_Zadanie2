#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 1000

struct DataItem {
    int data;
    int key;
};

struct DataItem* hashArray[SIZE];
struct DataItem* dummyItem;
struct DataItem* item;

int hashCode(int key) {
    if(key < 0)
        key *= -1;
    return key % SIZE;
}

struct DataItem *search(int key) {
    //get the hash
    int hashIndex = hashCode(key);
    int checkedValue = hashArray[hashIndex], first = 0;
    //move in array until an empty
    while(hashArray[hashIndex] != NULL) {
        if(hashArray[hashIndex]->key == key)
            return hashArray[hashIndex];
        if(hashArray[hashIndex] == checkedValue){
            if(first == 0)
                first++;
            else {
                printf("%d is not present in hash table with linear probing.\n", key);
                break;
            }
        }
        //go to next cell
        ++hashIndex;
        //wrap around the table
        hashIndex %= SIZE;
    }
    return NULL;
}

void insert(int key,int data) {
    struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
    item->data = data;
    item->key = key;
    //printf("Key %d Data %d \n", item->key, item->data);
    //get the hash
    int hashIndex = hashCode(key);

    //move in array until an empty or deleted cell
    while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
        if(hashArray[hashIndex]->key == key || hashArray[hashIndex]->data == data){
            printf("%d already present in hash table with linear probing.\n", hashArray[hashIndex]->data);
            return;
        }
        //go to next cell
        ++hashIndex;
        //wrap around the table
        hashIndex %= SIZE;
    }
    hashArray[hashIndex] = item;
}

struct DataItem* delete(struct DataItem* item) {
    int key = item->key;
    //get the hash
    int hashIndex = hashCode(key);
    //move in array until an empty
    while(hashArray[hashIndex] != NULL) {
        if(hashArray[hashIndex]->key == key) {
            struct DataItem* temp = hashArray[hashIndex];
            //assign a dummy item at deleted position
            hashArray[hashIndex] = dummyItem;
            return temp;
        }
        //go to next cell
        ++hashIndex;
        //wrap around the table
        hashIndex %= SIZE;
    }
    return NULL;
}

void display() {
    int i = 0;
    for(i = 0; i<SIZE; i++) {
        if(hashArray[i] != NULL)
            printf(" (%d,%d)",hashArray[i]->key,hashArray[i]->data);
        else
            printf(" ~~ ");
    }
    printf("\n");
}
// ukazkovy test
int main(void)
{
    int index = 0, key = 0, numberSet[500];;
    FILE *source = fopen("./one_thousand_Source.txt", "r");
    FILE *searchInput = fopen("./one_thousand_Search.txt","r");
    if(source == NULL){printf("Unsuccessful opening of source file.\n"); exit(1);}
    if(searchInput == NULL){printf("Unsuccessful opening of search file.\n"); exit(1);}
    dummyItem = (struct DataItem*) malloc(sizeof(struct DataItem));
    dummyItem->data = -1;
    dummyItem->key = -1;
    //fscanf(source, "%d", &key);
    struct node *root=NULL;
    while(fscanf(source, "%d", &key) == 1){
        printf("%d\n", key);
        insert(key,key);
    }
    index=0;
    while(fscanf(searchInput, "%d", &numberSet[index]) == 1){
        printf("%d ", numberSet[index]);
        index++;}

    for (index = 0; index < 500; index++){
        if(search(numberSet[index]) == NULL)
            printf("Key %d is not present in hash table with linear probing.\n", numberSet[index]);
        else
            printf("Key %d FOUND in hash table with linear probing.\n", numberSet[index]);
    }
    fclose(source);
    fclose(searchInput);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// uloha5-1.c -- Nicolas Mikulík, 20.10.2019 20:47

#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000

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

int compressFunctionTwo(int key, int size){
    int hash = hashFunctionOne(key);
    int a = 24, b = 5, N = 2003;
    return (a*hash + b) % N;
}

void insert(struct Item **hashArray, int key) {
    //printf("Inserting %d\n",key);
    int hashIndex = compressFunctionTwo(key, SIZE);
    if(hashArray[hashIndex] == nullptr){
        hashArray[hashIndex] = (struct Item *)malloc(sizeof(struct Item));
        hashArray[hashIndex]->next = hashArray[hashIndex];
        hashArray[hashIndex]->key = key;
        printf("Inserted key %d into an empty linked list at index %d.\n", key, hashIndex);
        return;
    }
    else{
        struct Item *start = hashArray[hashIndex];
        struct Item *traversing = hashArray[hashIndex];
        while(traversing->next != start){
            if(traversing->key == key){
                printf("Key %d already present in hash table at index %d.\n", key, hashIndex);
                return;
            }
            traversing = traversing->next;
        }
        struct Item *added = (struct Item *)malloc(sizeof(struct Item));
        added->key = key;
        added->next = start;
        traversing->next = added;
        printf("Inserted key %d into an existing linked list at index %d.\n", key, hashIndex);
        return;
    }
}


struct Item *find(struct Item **hashArray, int key) {
    int hashIndex = compressFunctionTwo(key, SIZE);
    if(hashArray[hashIndex] == nullptr){
        printf("Key %d not present in hash table.\n",key);
        return nullptr;
    }
    if(hashArray[hashIndex]->key == key){
        printf("Key %d found in hash table on index %d.\n", key, hashIndex);
        return hashArray[hashIndex];
    }
    else{
        struct Item *start = hashArray[hashIndex];
        struct Item *traversing = hashArray[hashIndex]->next;
        while(traversing->next != start){
            if(traversing->key == key){
                printf("Key %d found in hash table at index %d.\n", key, hashIndex);
                return hashArray[hashIndex];
            }
            traversing = traversing->next;
        }
        printf("Key %d not present in hash table.\n",key);
        return nullptr;
    }
}

// ukazkovy test
int main(void)
{
    int index = 0, read[SIZE], numberSet[SIZE];
    struct Item *hashArray[SIZE]; // = (struct Item*)malloc(SIZE*sizeof(struct Item));
    for(index=0;index<SIZE;index++)
        hashArray[index] = nullptr;
    FILE *source = fopen("./one_thousand_Source.txt", "r");
    FILE *search = fopen("./one_thousand_Search.txt","r");
    if(source == nullptr){printf("Unsuccessful opening of source file.\n"); exit(1);}
    if(search == nullptr){printf("Unsuccessful opening of search file.\n"); exit(1);}
    for (index = 0; index < SIZE; index++){
        fscanf(source, "%d", &read[index]);
        printf("%d\n",read[index]);
    }
    for (index = 0; index < SIZE; index++)
        insert(hashArray, read[index]);

    index=0;
    while(fscanf(search, "%d", &numberSet[index]) == 1){
        printf("%d ", numberSet[index]);
        index++;}
    for (index = 0; index < (SIZE/2); index++)
        find(hashArray, numberSet[index]);
    fclose(source);
    fclose(search);
    return 0;
}
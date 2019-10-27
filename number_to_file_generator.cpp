//
// Created by nicolas on 27. 10. 2019.
//

/*#include <stdio.h>
#include <stdlib.h>
#define COUNT 250

int main(){
    FILE *filepointer = fopen("./one_thousand_Search.txt", "w");
    if(filepointer == nullptr){printf("Unsuccessful opening of a file.\n"); exit(1);}
    int index = 0, number = 0, randomIndex = 0;
    int array[2*COUNT];
    for(index = -COUNT; index < COUNT; index++)
        array[index + COUNT] = index;
    for (index = 0; index < (2*COUNT); index++) {
        number = array[index];
        randomIndex = rand() % (2*COUNT);
        array[index] = array[randomIndex];
        array[randomIndex] = number;
        printf("%d\n", array[index]);
        fprintf(filepointer, "%d\n", array[index]);
    }
    fclose(filepointer);
    return 0;
}*/

/*void printRandoms(int lower, int upper, int count)
{
    int i;
    for (i = 0; i < count; i++) {
        int num = (rand() %
                   (upper - lower + 1)) + lower;
        printf("%d ", num);
    }
}*/

/*
// uloha5-1.c -- Nicolas Mikulík, 20.10.2019 20:47

#include <stdio.h>
#include <stdlib.h>
#define SIZE 100000

struct DataItem{
    int key;
};

int hashCode(int key){
    if(key < 1){
        key = key * (-1);
    }
    return key % SIZE;
}

void insert(struct DataItem **hashArray, int key) {
    //printf("Inserting %d\n",key);
    struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
    item->key = key;
    int hashIndex = hashCode(key);
    while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
        ++hashIndex;
        hashIndex %= SIZE;
    }
    hashArray[hashIndex] = item;
}


struct DataItem *search(struct DataItem **hashArray, int key) {
    int hashIndex = hashCode(key);
    while(hashArray[hashIndex] != NULL) {
        if(hashArray[hashIndex]->key == key)
            return hashArray[hashIndex];

        ++hashIndex;
        hashIndex %= SIZE;
    }
    return NULL;
}

// vrati 1 ak 's' je podmnozina 't', inak vrati 0.
int is_subset(int s[], int n, int t[], int m)
{
    //printf("Velkost t %d velkost s %d\n", m, n);
    //printf("sizeof struct DataItem %d\n",sizeof(struct DataItem));
    struct DataItem **hashArray=(struct DataItem**)malloc(SIZE*sizeof(struct DataItem*));
    if(hashArray == NULL){
        printf("Unsuccessfull malloc.\n");
        return 1;
    }
    for(int index=0;index<SIZE;index++){
        hashArray[index]==NULL;
    }
    for(int index=0; index<m; index++){
        insert(hashArray, t[index]);
    }
    for(int i=0; i<n; i++){
        if(search(hashArray,s[i])==NULL)
            return 0;
    }
    return 1;
}

// ukazkovy test
int main(void)
{
    int i, a[10], na, b[10], nb;
    scanf("%d", &na);
    for (i = 0; i < na; i++)
        scanf("%d", &a[i]);
    scanf("%d", &nb);
    for (i = 0; i < nb; i++)
        scanf("%d", &b[i]);
    if (is_subset(a, na, b, nb))
        printf("PODMNOZINA\n");
    else
        printf("NIE\n");
    return 0;
}
*/
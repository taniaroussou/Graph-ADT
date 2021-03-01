#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashInterface.h"

static int Hash(char *K,HTHash *hash){
    int h=0, a=33;
    for (; *K!='\0'; K++)
        h=(a*h + *K) % hash->size;
    return h;
}

HTHash* HTCreate(){
    HTHash* hash_table = malloc(sizeof(HTHash));    //hash table
    hash_table->table = malloc(sizeof(Bucket*)*HASH_SIZE); //10 pointers
    for(int i=0; i<HASH_SIZE; i++){
        hash_table->table[i] = malloc(sizeof(Bucket));  //10 Buckets
        hash_table->table[i]->head = NULL;
        hash_table->table[i]->current_nodes = 0;
    }
    hash_table->current_entries = 0;
    hash_table->size = HASH_SIZE;
    return hash_table;
}

int HTSize(HTHash* hash){
    return hash->current_entries;
}

Entry* HTSearch(HTHash* hash, char* key){
    if (hash->current_entries!=0){
        int h = Hash(key,hash);
        Entry *tmp = hash->table[h]->head;  //tmp points to first entry in ith position
        while (tmp!=NULL){
            if (strcmp(key,tmp->key)==0)
                return tmp;
            tmp = tmp->next;
        }
    }
    return NULL;    //hash table is empty or key not found
}

//Successful 1, unsuccessfull 0
int HTGet(HTHash* hash, char* key, HTItem** pitem){
    Entry *tmp = HTSearch(hash,key);
    if (tmp!=NULL){
        *pitem = &(tmp->item);
        return 1;
    }
    else
        return 0;
}

static HTHash* rehash(HTHash *hash){
    HTHash* hash_table = malloc(sizeof(HTHash));    //hash table
    hash_table->table = malloc(sizeof(Bucket*)*2*hash->size); //10 pointers
    for(int i=0; i<2*hash->size; i++){
        hash_table->table[i] = malloc(sizeof(Bucket));  //10 Buckets
        hash_table->table[i]->head = NULL;
        hash_table->table[i]->current_nodes = 0;
    }
    hash_table->current_entries = 0;
    hash_table->size = 2*hash->size;
    Entry *tmp,*tmp2;
    for(int i=0; i<hash->size; i++){
        tmp = hash->table[i]->head;
        for(int j=1; j<=hash->table[i]->current_nodes; j++){
            tmp2 = HTSearch(hash,tmp->key);
            HTInsert(hash_table,tmp2->key,tmp2->item);
            tmp = tmp->next;
        }
    }
    return hash_table;
}


HTHash* HTInsert(HTHash* hash, char* key, HTItem item){
    int h = Hash(key,hash);
    Entry *tmp = HTSearch(hash,key);    //search if key already exists
    if (tmp==NULL){             //hash table is empty or key not found
        Entry *new = malloc(sizeof(struct entry));
        new->item = item;
        new->key = strdup(key);
        new->next = NULL;
        if (hash->table[h]->current_nodes==0){   //bucket is empty, insert first entry
            hash->table[h]->head = new;
        }
        else{   //insert new entry at bottom of list
            Entry *tmp2 = hash->table[h]->head;
            while(tmp2->next!=NULL)
                tmp2 = tmp2->next;
            tmp2->next = new;
        }
        hash->current_entries++;
        hash->table[h]->current_nodes++;
    }
    else{
        //replace
        tmp->key = strdup(key);
        tmp->item = item;
    }
    double loadFactor = (double)hash->current_entries/hash->size;
    if (loadFactor>0.75){
        HTHash *temp = hash;
        hash = rehash(hash);
        HTDestroy(temp);    //delete old table
    }
    return hash;
}

void HTRemove(HTHash *hash, char* key){
    int h = Hash(key,hash);
    Entry *tmp = HTSearch(hash,key);
    if (tmp!=NULL){     //if key exists
        if (hash->table[h]->head==tmp){         //if entry is at the top of the list
            hash->table[h]->head = tmp->next;   //make the second entry the first entry
            free(tmp->key);
            free(tmp);
        }
        else{
            Entry *tmp2 = hash->table[h]->head;
            Entry *prev = tmp2;
            while(tmp2!=tmp){
                prev = tmp2;
                tmp2 = tmp2->next;
            }
            prev->next = tmp2->next;
            free(tmp2->key);
            free(tmp2);
        }
        hash->table[h]->current_nodes--;
        hash->current_entries--;
    }
}

void HTVisit(HTHash *hash , Visit visit){
    if (HTSize(hash)==0)    //empty table, don't do anything
        return;
    Entry *tmp;
    for(int i=0; i<hash->size; i++){
        tmp = hash->table[i]->head;
        for(int j=1; j<=hash->table[i]->current_nodes; j++){
            visit(hash,tmp->key,tmp->item);
            tmp = tmp->next;
        }
    }
}

void HTDestroy(HTHash *hash){
    Entry *tmp,*tmp2;
    for(int i=0; i<hash->size; i++){
        if (hash->table[i]->current_nodes!=0){  //if bucket not empty
            tmp = hash->table[i]->head;
            while(tmp!=NULL){
                tmp2=tmp;
                tmp = tmp->next;
                free(tmp2->key);
                free(tmp2);
            }
        }
        free(hash->table[i]);
    }
    free(hash->table);
    free(hash);
}

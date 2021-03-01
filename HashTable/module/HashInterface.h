#include "HashTypes.h"
#define HASH_SIZE 10

typedef struct entry{
    char* key;
    HTItem item;
    struct entry *next;
} Entry;

typedef struct {
    Entry *head;
    int current_nodes;
} Bucket;

typedef struct {
    int size;       //number of buckets
    int current_entries;
    Bucket **table;
} HTHash;

typedef void (*Visit)(HTHash*,char*,HTItem);

HTHash* HTCreate();
int HTSize(HTHash* );
int HTGet(HTHash* , char* , HTItem** );
HTHash* HTInsert(HTHash* , char* , HTItem );
void HTRemove(HTHash* , char* );
void HTVisit(HTHash* , Visit );
void HTDestroy(HTHash* );

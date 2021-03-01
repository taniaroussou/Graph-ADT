#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashInterface.h"

void visitInt(HTHash* ht, char* key, HTItem item) {
	printf("Key is: %s,item is: %d\n",key, *((int*)item));
}

void visitStr(HTHash *hash, char* key, HTItem item){
	printf("Key is: %s,item is: %s\n", key,  (char *)item);
}

void random_str(char *s, const int len) {
	static const char x[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	for (int i=0; i<len; i++) {
		s[i] = x[rand() % (sizeof(x) - 1)];
	}
	s[len] = 0;
}

int main(){
	//Create a hash table with type int entries
	printf("Creating a hash table with type int entries\n");
	HTHash *table = HTCreate();
	int rand_key = rand() % 8;
	int i;
	for(i=0; i<8; i++){
		char str[] = { [5] = '\0' };
		random_str(str, sizeof str - 1);
		table = HTInsert(table, str, &i);
		if (i == rand_key){
			printf("Now removing key '%s'\n", str);
			HTRemove(table, str);
		}
	}
	int size = HTSize(table);
	printf("Size of hash table is: %d\n", size);

	HTItem* get = NULL;
	char* key = strdup("pkLoR");
	if(HTGet(table, key, &get)){
		printf("Found key '%s' and now visiting key::", key);
		visitInt(table, key, *get);
	}
	else
		printf("Didn't find key '%s'\n", key);
	free(key);

	printf("Now calling HTVisit\n");
	HTVisit(table, visitInt);

	printf("Now destroying the hash table\n\n\n");
	HTDestroy(table);

	//Create a hash table with type string entries
	printf("Creating a hash table with type string entries\n");
	table = HTCreate();
	rand_key = rand() % 8;
	for(i=0; i<8; i++){
		char str[] = { [5] = '\0' };
		random_str(str, sizeof str - 1);
		table = HTInsert(table, str, str);
		if (i == rand_key){
			printf("Now removing key '%s'\n", str);
			HTRemove(table, str);
		}
	}
	size = HTSize(table);
	printf("Size of hash table is: %d\n", size);

	get = NULL;
	key = strdup("abcd");
	if(HTGet(table, key, &get))
		printf("Found key '%s'\n", key);
	else
		printf("Didn't find key '%s'\n", key);
	free(key);

	printf("Now calling HTVisit\n");
	HTVisit(table, visitStr);

	printf("Now destroying the hash table\n");
	HTDestroy(table);

	return 0;
}

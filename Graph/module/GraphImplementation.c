#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "GraphInterface.h"
#include "list.h"

int compare_strings(void *a, void *b) {	// the params need to be void* !
	return strcmp(a, b);	// auto cast void* -> char*
}

UGGraph* UGCreate(){
    UGGraph* graph = HTCreate();
    return graph;
}

UGGraph* UGAddVertex(UGGraph* graph, char* vertex){
    LLList list = LLCreate();
    graph = HTInsert(graph,vertex,list);
    return graph;
}

void UGRemoveVertex(UGGraph* graph, char* vertex){
    HTItem* list = NULL;
    if(HTGet(graph,vertex,&list)){
        LLDestroy(*list);
        HTRemove(graph,vertex);
    }
}

void UGAddEdge(UGGraph* graph, char* vertex1, char* vertex2){
    HTItem* list1 = NULL;
    if(HTGet(graph,vertex1,&list1)){
		LLInsertAfter(*list1,LL_NIL,vertex2);  //insert vertex2 at top of list
	}
    HTItem* list2 = NULL;
    if(HTGet(graph,vertex2,&list2)){
		LLInsertAfter(*list2,LL_NIL,vertex1);  //insert vertex1 at top of list
	}
}

void UGRemoveEdge(UGGraph* graph, char* vertex1, char* vertex2){
    HTItem* list1 = NULL;
    if(HTGet(graph,vertex1,&list1)){
        LLNode node = LLFind(*list1,vertex2,compare_strings);
        if (node!=LL_NIL){
			LLRemove(*list1,node);
		}
    }
    HTItem* list2 = NULL;
    if(HTGet(graph,vertex2,&list2)){
        LLNode node = LLFind(*list2,vertex1,compare_strings);
        if (node!=LL_NIL)
            LLRemove(*list2,node);
    }
}

LLList UGGetAdjacent(UGGraph* graph, char* vertex){
	HTItem* list = NULL;
	if(HTGet(graph,vertex,&list)){
		return *list;
	}
	return NULL;
}

static int Hash(char *K,HTHash *hash){
    int h=0, a=33;
    for (; *K!='\0'; K++)
        h=(a*h + *K) % hash->size;
    return h;
}

Entry* Search(HTHash* hash, char* key){
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

LLList UGShortestPath(UGGraph* graph, char* vertex1, char* vertex2){
	char* src = vertex1;
	char* dest = vertex2;
	HTHash* w = HTCreate();
	HTHash* dist = HTCreate();
	HTHash* prev = HTCreate();
	Entry *tmp, *tmp2, *tmp3, *pr=NULL;
	char *u = malloc(sizeof(char*)*1024);
	int zero=0,one=1,max=INT_MAX,best_cost=INT_MAX;
	LLList best_path = LLCreate();
	for(int i=0; i<graph->size; i++){
            tmp = graph->table[i]->head;
			for(int j=1; j<=graph->table[i]->current_nodes; j++){
	            tmp2 = Search(graph,tmp->key);
	           	w = HTInsert(w,tmp2->key,&zero);
				dist = HTInsert(dist,tmp2->key,&max);
				prev = HTInsert(prev,tmp2->key,pr);
	            tmp = tmp->next;
	        }
    }
	tmp2 = Search(dist,src);
	tmp2->item = &zero;		//dist[src] = 0
	while (1){
		int min_dist = INT_MAX;
		for(int i=0; i<w->size; i++){
			tmp = w->table[i]->head;
			for(int j=1; j<=w->table[i]->current_nodes; j++){
				tmp2 = Search(w,tmp->key);	//W[v]
				tmp3 = Search(dist,tmp->key); //dist[v]
				if (min_dist>*((int*)tmp3->item) && tmp2->item==&zero){
					min_dist = *((int*)tmp3->item);
					u = strdup(tmp3->key);
				}
				tmp = tmp->next;
			}
		}
		tmp2 = Search(w,u);
		tmp2->item = &one;		
		tmp2 = Search(dist,u);
		if (strcmp(u,dest)==0){
			best_cost = *((int*)tmp2->item);		// best cost = dist[dest]
			if (best_cost!=INT_MAX){
				pr = Search(prev,dest);
				LLInsertAfter(best_path,LL_NIL,dest);	//insert dest in best_path
				while (strcmp(pr->item,src)!=0){
					LLInsertAfter(best_path,LL_NIL,pr->item);
					pr = Search(prev,pr->item);
				}
				LLInsertAfter(best_path,LL_NIL,pr->item);	//insert src in best_path
			}
			break;
		}
		LLList neighbors = UGGetAdjacent(graph,u);
		LLNode neighbor = LLNext(neighbors,LL_NIL);		//first neighbor
		for(LLNode node = neighbor; node != NULL; node = node->next){		//for each neighbor v of u:
			int cost = 0;
			tmp3 = Search(w,node->item);		
			tmp2 = Search(dist,tmp3->key);		
			if (*((int*)tmp3->item)==1)	
	            continue;
			tmp = Search(dist,u);
			cost = *((int*)tmp->item) + 1;	
	        if (cost < *((int*)tmp2->item)){
				tmp2->item = &cost;
				pr = Search(prev,tmp3->key);
				pr->item = strdup(u);		
			}
		}
	}
	HTDestroy(w);
	HTDestroy(dist);
	HTDestroy(prev);
	return best_path;
}

void UGDestroy(UGGraph* graph){
	Entry *tmp, *tmp2;
	for(int i=0; i<graph->size; i++){
		if (graph->table[i]->current_nodes!=0){  //if bucket not empty
            tmp = graph->table[i]->head;
            while(tmp!=NULL){
                tmp2=tmp;
                tmp = tmp->next;
				LLDestroy(tmp2->item);
            }
        }
	}
	HTDestroy(graph);
}

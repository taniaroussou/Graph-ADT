#include <stdio.h>
#include "GraphInterface.h"
#include "list.h"

void visit_string(LLList list, LLNode node) {
	char *s = LLGetItem(list, node);		// auto cast void* -> char*
	printf("%s ", s);
}

/*example graph:              
		   piz
                  /    \
		 /  	\
                foo------bar
	          \      /
		   \    /
	  abc-------izi
*/

int main(){
	UGGraph *graph = UGCreate();
	graph = UGAddVertex(graph, "foo");
	graph = UGAddVertex(graph, "bar");
	graph = UGAddVertex(graph, "abc");
	graph = UGAddVertex(graph, "izi");
	graph = UGAddVertex(graph, "piz");
	UGAddEdge(graph, "foo", "bar");
	UGAddEdge(graph, "foo", "piz");
	UGAddEdge(graph, "foo", "izi");
	UGAddEdge(graph, "piz", "bar");
	UGAddEdge(graph, "izi", "bar");
	UGAddEdge(graph, "izi", "abc");
	LLList list = UGGetAdjacent(graph, "foo");
	printf("List of vertices adjacent to foo is : ");
	LLVisit(list, visit_string);

	printf("\n");
	//UGRemoveVertex(graph,"foo");
	//UGRemoveEdge(graph,"foo","bar");
	list = UGGetAdjacent(graph, "bar");
	printf("List of vertices adjacent to bar is : ");
	LLVisit(list, visit_string);

	printf("\n");
	list = UGGetAdjacent(graph, "abc");
	printf("List of vertices adjacent to abc is : ");
	LLVisit(list, visit_string);

	printf("\n");
	list = UGGetAdjacent(graph, "izi");
	printf("List of vertices adjacent to izi is : ");
	LLVisit(list, visit_string);

	printf("\n");
	list = UGGetAdjacent(graph, "piz");
	printf("List of vertices adjacent to piz is : ");
	LLVisit(list, visit_string);

	printf("\n");
	LLList path = UGShortestPath(graph, "abc", "piz");
	if (LLLength(path) == 0)
		printf("There's no path\n");
	else{
		printf("Path is: ");
		LLVisit(path, visit_string);
	}

	printf("\n");
	LLDestroy(path);
	UGDestroy(graph);
	return 0;
}

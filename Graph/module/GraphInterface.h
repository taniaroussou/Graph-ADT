#pragma once
#include "HashInterface.h"
#include "list.h"

typedef HTHash UGGraph;

UGGraph* UGCreate();
UGGraph* UGAddVertex(UGGraph*, char*);
void UGRemoveVertex(UGGraph*, char*);
void UGAddEdge(UGGraph*, char*, char*);
void UGRemoveEdge(UGGraph*, char*, char*);
LLList UGGetAdjacent(UGGraph*, char*);
LLList UGShortestPath(UGGraph*, char*, char*);
void UGDestroy(UGGraph*);

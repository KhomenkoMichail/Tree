#ifndef TREE_FUNCTIONS_H
#define TREE_FUNCTIONS_H

#include "structsAndConsts.h"

node_t* treeNodeCtor (treeElem_t dataValue);

int printNode (node_t* node);

int fprintfTreeGraphDump (node_t* treeNode, const char* textGraphFileName);

int fprintfNodeGraph (node_t* node, int rank, FILE* textFile);

int fprintfNodeLinksForGraph (node_t* node, FILE* graphFile);

#endif

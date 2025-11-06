#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "treeFunctions.h"
#include "nodeAccessFunctions.h"
#include "structsAndConsts.h"

node_t* treeNodeCtor (treeElem_t dataValue) {
    node_t* newNode = (node_t*)calloc(1, sizeof(node_t));

    *(nodeData(newNode)) = dataValue;
    *(nodeLeft(newNode)) = NULL;
    *(nodeRight(newNode)) = NULL;

    return newNode;
}

int printNode (node_t* node) {
    assert(node);

    printf("(");

    node_t** left = nodeLeft(node);
    if((left != NULL) && (*left != NULL))
        printNode(*nodeLeft(node));

    printf("%d", *nodeData(node));

    node_t** right = nodeRight(node);
    if((right != NULL) && (*right != NULL))
        printNode(*nodeRight(node));

    printf(")");

    return 0;
}

#include <assert.h>
#include <stdio.h>

#include "nodeAccessFunctions.h"
#include "structsAndConsts.h"

treeElem_t* nodeData (node_t* node) {
    assert (node);

    return &(node->data);
}

node_t** nodeLeft (node_t* node) {
    assert(node);

    return &(node->left);
}

node_t** nodeRight (node_t* node) {
    assert(node);

    return &(node->right);
}

node_t** treeRoot (tree_t* treePtr) {
    assert(treePtr);

    return &(treePtr->rootNode);
}

size_t* treeSize (tree_t* treePtr) {
    assert(treePtr);

    return &(treePtr->size);
}

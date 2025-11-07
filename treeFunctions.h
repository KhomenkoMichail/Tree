#ifndef TREE_FUNCTIONS_H
#define TREE_FUNCTIONS_H

#include "structsAndConsts.h"

#define TreeInsert(treeAddress, dataValue, dumpInfoAddress) ({\
    (dumpInfoAddress)->nameOfFile = __FILE__;\
    (dumpInfoAddress)->numOfLine = __LINE__;\
    node_t* returnableValue = treeInsert(treeAddress, dataValue, dumpInfoAddress);\
    returnableValue;\
})

#define TreeCtor(treeAddress, rootDataValue, dumpInfoAddress) ({\
    (dumpInfoAddress)->nameOfFile = __FILE__;\
    (dumpInfoAddress)->numOfLine = __LINE__;\
    tree_t* returnableValue = treeCtor(treeAddress, rootDataValue, dumpInfoAddress);\
    returnableValue;\
})

node_t* treeNodeCtor (treeElem_t dataValue);

int printNode (node_t* node, size_t* nodesPassed, size_t treeSize);

int fprintfTreeGraphDump (tree_t* tree, const char* textGraphFileName);

int fprintfNodeGraph (node_t* node, int rank, FILE* textFile, size_t* nodesPassed, size_t treeSize);

int fprintfNodeLinksForGraph (node_t* node, FILE* graphFile, size_t* nodesPassed, size_t treeSize);

void treeDump (struct tree_t* tree, struct dump* dumpInfo, const char* message);

void createGraphImageForDump (struct tree_t* tree, FILE* dumpFile, const char* nameOfTextGraphFile);

node_t* treeInsert (tree_t* tree, treeElem_t dataValue, struct dump* dumpInfo);

tree_t* treeCtor (tree_t* tree, treeElem_t rootDataValue, dump* dumpInfo);

int deleteNode (node_t* node, size_t* nodesPassed, size_t treeSize);

void fprintfTreeErrorsForDump (struct tree_t* tree, FILE* dumpFile, struct dump* dumpInfo);

int nodeVerifier (node_t* node, int* errorCode, size_t* nodesPassed, size_t treeSize);

int treeVerifier (tree_t* tree);

int deleteTree (tree_t* tree);

int treeSort (treeElem_t* inputDataArr, size_t arrSize);

#endif

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <TXLib.h>

#include "treeFunctions.h"
#include "nodeAccessFunctions.h"
#include "structsAndConsts.h"


node_t* treeNodeCtor (treeElem_t dataValue) {
    node_t* newNode = (node_t*)calloc(1, sizeof(node_t));

    newNode->canary = SIGNATURE;
    *(nodeData(newNode)) = dataValue;
    *(nodeLeft(newNode)) = NULL;
    *(nodeRight(newNode)) = NULL;

    return newNode;
}

int printNode (node_t* node) {
    assert(node);

    printf("(");

    node_t** left = nodeLeft(node);
    if((left != NULL) && (*left != NULL) && ((*left)->canary == SIGNATURE))
        printNode(*nodeLeft(node));

    printf("%d", *nodeData(node));

    node_t** right = nodeRight(node);
    if((right != NULL) && (*right != NULL) && ((*right)->canary == SIGNATURE))
        printNode(*nodeRight(node));

    printf(")");

    return 0;
}

int fprintfTreeGraphDump (node_t* rootNode, const char* textGraphFileName) {
    assert(rootNode);
    assert(textGraphFileName);

    FILE* graphFile = fopen(textGraphFileName, "w");

    if (graphFile == NULL) {
        fprintf(stderr, "Error of opening file \"%s\"", textGraphFileName);
        perror("");
        return 1;
    }

    fprintf(graphFile, "digraph Tree {\n");
    fprintf(graphFile, "    rankdir = TB;\n");
    fprintf(graphFile, "    node [shape = Mrecord, color = black];\n");

    fprintfNodeGraph(rootNode, 0, graphFile);
    fprintfNodeLinksForGraph(rootNode, graphFile);

    fprintf(graphFile, " }\n");
    if (fclose(graphFile) != 0) {
        fprintf(stderr, "Error of closing file \"%s\"", textGraphFileName);
        perror("");
        return 1;
    }

    return 0;
}

int fprintfNodeGraph (node_t* node, int rank, FILE* graphFile) {
    assert(node);
    assert(graphFile);

    if(node->canary != SIGNATURE) {
        fprintf(graphFile, "    errorNode0x%p [rank = %d, label = \"{ ERRROR!| 0x%p }\", style = filled, fillcolor = \"#be3131ff\", color = black, shape = doubleoctagon];\n",
                node, rank, node);
        return 0;
    }

    fprintf(graphFile, "    node0x%p [rank = %d, label = \"{ <addr>0x%p| data = %d|CANARY = %X|{<left>LEFT\\n 0x%p| <right>RIGHT\\n 0x%p}}\", style = filled, fillcolor = \"#c1e0a7ff\", color = black];\n",
                node, rank, node, *nodeData(node), node->canary,*(nodeLeft(node)), *(nodeRight(node)));

    node_t** left = nodeLeft(node);
    if((left != NULL) && (*left != NULL) && !(_txIsBadReadPtr(*left)) && ((*left)->canary == SIGNATURE))
        fprintfNodeGraph(*nodeLeft(node), rank + 1, graphFile);

    node_t** right = nodeRight(node);
    if((right != NULL) && (*right != NULL) && !(_txIsBadReadPtr(*right)) && ((*right)->canary == SIGNATURE))
        fprintfNodeGraph(*nodeRight(node), rank + 1, graphFile);

    return 0;
}

int fprintfNodeLinksForGraph (node_t* node, FILE* graphFile) {
    assert(node);
    assert(graphFile);

    node_t** left = nodeLeft(node);
    if((left != NULL) && (*left != NULL) && !(_txIsBadReadPtr(*left)) && ((*left)->canary == SIGNATURE)) {
        fprintf(graphFile, "    node0x%p:left -> node0x%p:addr [color = \"#5d510cff\"];\n", node, *nodeLeft(node));
        fprintfNodeLinksForGraph(*nodeLeft(node), graphFile);
    }

    if((left != NULL) && (*left != NULL) && (_txIsBadReadPtr(*left))) {
        fprintf(graphFile, "    errorNode0x%p [label = \"ERRROR!\\n 0x%p \", style = filled, fillcolor = \"#be3131ff\", color = black, fontcolor = white, shape = doubleoctagon];\n",
                *left, *left);
        fprintf(graphFile, "    node0x%p:left -> errorNode0x%p [color = \"#f90d0dff\"];\n", node, *left);
    }

    node_t** right = nodeRight(node);
    if((right != NULL) && (*right != NULL) && !(_txIsBadReadPtr(*right)) && ((*right)->canary == SIGNATURE)) {
        fprintf(graphFile, "    node0x%p:right -> node0x%p:addr [color = \"#5d510cff\"];\n", node, *nodeRight(node));
        fprintfNodeLinksForGraph(*nodeRight(node), graphFile);
    }

    if((right != NULL) && (*right != NULL) && (_txIsBadReadPtr(*right))) {
        fprintf(graphFile, "    errorNode0x%p [label = \"ERRROR!\\n 0x%p \", style = filled, fillcolor = \"#be3131ff\", color = black, fontcolor = white, shape = doubleoctagon];\n",
                *right, *right);
        fprintf(graphFile, "    node0x%p:right -> errorNode0x%p [color = \"#f90d0dff\"];\n", node, *right);
    }

    return 0;
}

void treeDump (struct tree_t* tree, struct dump* dumpInfo, const char* message) {
    assert(tree);
    assert(dumpInfo);
    assert(message);

    const char* nameOfTextGraphFile = dumpInfo->nameOfGraphFile;

    FILE* dumpFile = 0;
    if(dumpInfo->dumpFileWasOpened)
        dumpFile = fopen(dumpInfo->nameOfDumpFile, "a");
    else {
        dumpFile = fopen(dumpInfo->nameOfDumpFile, "w");
        dumpInfo->dumpFileWasOpened = 1;
    }

    if (dumpFile == NULL) {
        fprintf(stderr, "Error of opening file \"%s\"", dumpInfo->nameOfDumpFile);
        perror("");
        return;
    }

    fprintf(dumpFile, "<pre>\n");
    fprintf(dumpFile, "<h3>listDump() <font color=red>from %s at %s:%d</font></h3>\n",
    dumpInfo->nameOfFunc, dumpInfo->nameOfFile, dumpInfo->numOfLine);

    fprintf(dumpFile, "<h2><font color=blue>%s</font></h2>\n", message);

    createGraphImageForDump (tree, dumpFile, nameOfTextGraphFile);

    if (fclose(dumpFile) != 0) {
        fprintf(stderr, "Error of closing file \"%s\"", dumpInfo->nameOfGraphFile);
        perror("");
        return;
    }
}

void createGraphImageForDump (struct tree_t* tree, FILE* dumpFile, const char* nameOfTextGraphFile) {
    assert(tree);
    assert(dumpFile);
    assert(nameOfTextGraphFile);

    static int graphImageCounter = 0;
    graphImageCounter++;

    node_t* rootNode = *treeRoot(tree);
    fprintfTreeGraphDump(rootNode, nameOfTextGraphFile);

    char graphvizCallCommand[STR_SIZE] = {};
    snprintf(graphvizCallCommand, sizeof(graphvizCallCommand), "dot -Tpng %s -o PNG_DUMPS/graph%d.png", nameOfTextGraphFile, graphImageCounter);
    system(graphvizCallCommand);
    fprintf(dumpFile, "Image:\n <img src=PNG_DUMPS/graph%d.png width=1000px>\n", graphImageCounter);
}

node_t* treeInsert (tree_t* tree, treeElem_t dataValue, struct dump* dumpInfo) {
    assert(tree);

    dumpInfo->nameOfFunc = __func__;
    char beforeMessage[STR_SIZE] =  {};
    char afterMessage[STR_SIZE]= {};
    snprintf(beforeMessage, sizeof(beforeMessage), "BEFORE insert \"%d\" in tree", dataValue);
    snprintf(afterMessage, sizeof(afterMessage), "AFTER insert \"%d\" in tree", dataValue);

    node_t* newNode = NULL;

    treeDump(tree, dumpInfo, beforeMessage);

    for (node_t* node = *treeRoot(tree); ; ) {
        if (dataValue <= *nodeData(node)) {
            if (*nodeLeft(node) == NULL) {
                *nodeLeft(node) = treeNodeCtor(dataValue);
                newNode = *nodeLeft(node);
                break;
            }
            else {
                node = *nodeLeft(node);
                continue;
            }
        }
        else {
            if (*nodeRight(node) == NULL) {
                *nodeRight(node) = treeNodeCtor(dataValue);
                newNode = *nodeRight(node);
                break;
            }
            else {
                node = *nodeRight(node);
                continue;
            }
        }
    }
    *treeSize(tree) += 1;

    treeDump(tree, dumpInfo, afterMessage);

    return newNode;
}

tree_t* treeCtor(tree_t* tree, treeElem_t rootDataValue, dump* dumpInfo) {
    assert(tree);

    *treeRoot(tree) = treeNodeCtor(rootDataValue);
    *treeSize(tree) = 1;

    dumpInfo->nameOfFunc = __func__;
    treeDump(tree, dumpInfo, "AFTER creation of the tree");

    return tree;
}

int deleteNode(node_t* node) {
    assert(node);

    node_t** left = nodeLeft(node);
    if((left != NULL) && (*left != NULL) && ((*left)->canary == SIGNATURE))
        deleteNode(*nodeLeft(node));

    node_t** right = nodeRight(node);
    if((right != NULL) && (*right != NULL) && ((*right)->canary == SIGNATURE))
        deleteNode(*nodeRight(node));

    node->canary = 0xDEADBABE;
    free(node);
    return 0;
}

int nodeVerifier (node_t* node, int* errorCode) {
    assert(node);

    if (node->canary != SIGNATURE)
        (*errorCode) |= deadCanary;

    if (_txIsBadReadPtr(*nodeRight(node)))
        (*errorCode) |= badRight;

    if (_txIsBadReadPtr(*nodeLeft(node)))
        (*errorCode) |= badLeft;

    if  (!(_txIsBadReadPtr(*nodeRight(node))))
        nodeVerifier(*nodeRight(node), errorCode);

    if  (!(_txIsBadReadPtr(*nodeRight(node))))
        nodeVerifier(*nodeRight(node), errorCode);

    if  (!(_txIsBadReadPtr(*nodeLeft(node))))
        nodeVerifier(*nodeLeft(node), errorCode);

    return (*errorCode);
}

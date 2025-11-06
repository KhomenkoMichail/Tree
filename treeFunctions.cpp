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

    fprintf(graphFile, "    node0x%p [rank = %d, label = \"{ <addr>0x%p| data = %d|{<left>LEFT\\n 0x%p| <right>RIGHT\\n 0x%p}}\", style = filled, fillcolor = \"#c1e0a7ff\", color = black];\n",
                node, rank, node, *nodeData(node), *(nodeLeft(node)), *(nodeRight(node)));

    node_t** left = nodeLeft(node);
    if((left != NULL) && (*left != NULL))
        fprintfNodeGraph(*nodeLeft(node), rank + 1, graphFile);

    node_t** right = nodeRight(node);
    if((right != NULL) && (*right != NULL))
        fprintfNodeGraph(*nodeRight(node), rank + 1, graphFile);

    return 0;
}

int fprintfNodeLinksForGraph (node_t* node, FILE* graphFile) {
    assert(node);
    assert(graphFile);

    node_t** left = nodeLeft(node);
    if((left != NULL) && (*left != NULL)) {
        fprintf(graphFile, "    node0x%p:left -> node0x%p:addr [color = \"#5d510cff\"];\n", node, *nodeLeft(node));
        fprintfNodeLinksForGraph(*nodeLeft(node), graphFile);
    }

    node_t** right = nodeRight(node);
    if((right != NULL) && (*right != NULL)) {
        fprintf(graphFile, "    node0x%p:right -> node0x%p:addr [color = \"#5d510cff\"];\n", node, *nodeRight(node));
        fprintfNodeLinksForGraph(*nodeRight(node), graphFile);
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

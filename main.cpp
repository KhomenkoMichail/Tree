#include <stdio.h>
#include <stdlib.h>

#include "structsAndConsts.h"
#include "nodeAccessFunctions.h"
#include "treeFunctions.h"


int main (void) {

    struct dump dumpInfo = {};
    struct tree_t tree = {};
    dumpInfo.nameOfGraphFile = "treeGraph.txt";
    dumpInfo.nameOfDumpFile = "dump.html";


    node_t* node10 = treeNodeCtor(10);

    node_t* node5 = treeNodeCtor(5);

    node_t* node3 = treeNodeCtor(3);

    node_t* node7 = treeNodeCtor(7);

    node_t* node20 = treeNodeCtor(20);
    node_t* node15 = treeNodeCtor(15);

    node10->left = node5;
    node10->right = node20;

    node5->left = node3;
    node5->right = node7;

    node20->left = node15;

    printNode(node10);
    //fprintfTreeGraphDump (node10, "treeGraph.txt");
    tree.rootNode = node10;
    treeDump(&tree, &dumpInfo, "trying");

    free(node10);
    free(node5);
    free(node3);
    free(node7);
    free(node20);
    free(node15);



    return 0;
}

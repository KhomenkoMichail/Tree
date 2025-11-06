#include <stdio.h>
#include <stdlib.h>
#include <TXLib.h>

#include "structsAndConsts.h"
#include "nodeAccessFunctions.h"
#include "treeFunctions.h"


int main (void) {

    struct dump dumpInfo = {};
    struct tree_t tree = {};
    dumpInfo.nameOfGraphFile = "treeGraph.txt";
    dumpInfo.nameOfDumpFile = "dump.html";

    TreeCtor(&tree, 10, &dumpInfo);
    TreeInsert (&tree, 40, &dumpInfo);
    node_t* node2 = TreeInsert (&tree, 2, &dumpInfo);
    node2->right = (node_t*)0x12345678;
    node2->left = (node_t*)0x67693123;
    TreeInsert (&tree, 17, &dumpInfo);
    TreeInsert (&tree, 5, &dumpInfo);
    TreeInsert (&tree, 6, &dumpInfo);
    TreeInsert (&tree, 99, &dumpInfo);

    //printf("%p\n", node2);
    //free(node2);
    //deleteNode(node2);
    //treeDump(&tree, &dumpInfo, "afterDelete 2");




    printNode(*treeRoot(&tree));



    return 0;
}

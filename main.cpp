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
    TreeInsert (&tree, 17, &dumpInfo);
    TreeInsert (&tree, 12, &dumpInfo);
    TreeInsert (&tree, 20, &dumpInfo);
    TreeInsert (&tree, 65, &dumpInfo);
    TreeInsert (&tree, 52, &dumpInfo);
    TreeInsert (&tree, 6, &dumpInfo);
    TreeInsert (&tree, 8, &dumpInfo);
    TreeInsert (&tree, 9, &dumpInfo);
    TreeInsert (&tree, 13, &dumpInfo);
    TreeInsert (&tree, 1, &dumpInfo);
    TreeInsert (&tree, 80, &dumpInfo);
    TreeInsert (&tree, 33, &dumpInfo);
    TreeInsert (&tree, 22, &dumpInfo);
    TreeInsert (&tree, 12, &dumpInfo);
    TreeInsert (&tree, 77, &dumpInfo);
    TreeInsert (&tree, 14, &dumpInfo);
    TreeInsert (&tree, 71, &dumpInfo);
    TreeInsert (&tree, 9, &dumpInfo);
    node_t* node2 = TreeInsert (&tree, 2, &dumpInfo);
    node2->right = (node_t*)0x12345678;
    node2->left = (node_t*)0x67693123;
    //int x = treeVerifier(&tree);
    //printf("x == %d\n", x);
    //treeDump (&tree, &dumpInfo, "errorCheck");
    TreeInsert (&tree, 17, &dumpInfo);
    TreeInsert (&tree, 5, &dumpInfo);
    //TreeInsert (&tree, 6, &dumpInfo);
    //TreeInsert (&tree, 99, &dumpInfo);

    //printf("%p\n", node2);
    //free(node2);
    //deleteNode(node2);
    //treeDump(&tree, &dumpInfo, "afterDelete 2");
    deleteTree(&tree);



    //printNode(*treeRoot(&tree));



    return 0;
}

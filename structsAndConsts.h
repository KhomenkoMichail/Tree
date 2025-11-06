#ifndef STRUCTS_AND_CONSTS_H
#define STRUCTS_AND_CONSTS_H

typedef int treeElem_t;

struct node_t {
    treeElem_t data;
    node_t* left;
    node_t* right;
};

struct tree {
    node_t* rootNode;
    size_t size;
};




#endif

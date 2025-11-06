#ifndef STRUCTS_AND_CONSTS_H
#define STRUCTS_AND_CONSTS_H

typedef int treeElem_t;

struct node_t {
    int canary;
    treeElem_t data;
    node_t* left;
    node_t* right;
};

struct tree_t {
    node_t* rootNode;
    size_t size;
};

struct dump {
    const char* nameOfFile;
    const char* nameOfFunc;
    unsigned int numOfLine;

    const char* nameOfDumpFile;
    const char* nameOfGraphFile;
    int dumpFileWasOpened;
};

const size_t STR_SIZE = 64;
const int SIGNATURE = 0xBADBABE;

#endif

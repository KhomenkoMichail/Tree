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

    int errorCode;
};

struct dump {
    const char* nameOfFile;
    const char* nameOfFunc;
    unsigned int numOfLine;

    const char* nameOfDumpFile;
    const char* nameOfGraphFile;
    int dumpFileWasOpened;
};

enum treeErr_t {
    noErrors = 0x00,
    deadCanary = 0x01,
    badLeft = 0x02,
    badRight = 0x04,
    tooManyRecursiveCalls = 0x08,
};

const size_t STR_SIZE = 64;
const int SIGNATURE = 0xBADBABE;

#endif

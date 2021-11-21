#ifndef _HUFFMANCODING_H
#define _HUFFMANCODING_H
#include "Heap.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

#define _weigth 0
#define _left 1
#define _right 2
#define _parent 3
//#define _value 4

struct Node{
    int val;
    long long weight;
    int parent;
    Node(int val,long long weight,int parent){
        this->val=val;
        this->weight=weight;
        this->parent=parent;
    }
    friend bool operator < (Node a,Node b){
        return a.weight < b.weight;
    }
};


class Document{
private:
    long long BytecodeArray[256];
    long long HuffmanTree[512][4];
    string Words[258];
    const char* path;
    Heap<Node> Nodes;
    int mode;
    int top;
    ///
    bool Readin(int mode);
    bool HTreeInit();
    bool Select(int & node1,int & node2);
    bool HTreeCreate();
    bool WordsCreate();
public:
    Document(const char *Address,int mode_chose);
    //~Document();
    bool Encode();
    bool Decode();
    bool watch();

};

#endif

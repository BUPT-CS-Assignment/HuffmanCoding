#ifndef _HUFFMANCODING_H
#define _HUFFMANCODING_H
#include "Heap.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <windows.h>
#include<math.h>
using namespace std;

#define _weigth 0
#define _left 1
#define _right 2
#define _parent 3

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
    const char* fileName;
    Heap<Node> Nodes;
    long long fileSize;
    int mode;
    int top;
    ///
    bool Readin(int mode);
    bool HTreeInit();
    bool Select(int & node1,int & node2);
    bool HTreeCreate();
    bool WordsCreate();
public:
    Document(const char *Address,int mode_chose,const char * fileName);
    //~Document();
    bool Encode();
    bool Decode();
    bool watch();
    int toInt(char bit[]);
    bool toBinary(char* binary,int num);

};
#endif

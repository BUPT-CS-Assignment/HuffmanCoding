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
    int BytecodeArray[256];
    int HuffmanTree[512][4];
    string Words[258];
    const char* FILEpath;
    const char* FILEname;
    Heap<Node> Nodes;
    unsigned long long fileSize;
    int top;
    ///
    bool Readin(int mode);
    bool HTreeInit();
    bool Select(int & node1,int & node2);
    bool HTreeCreate();
    bool WordsCreate();
public:
    Document(string filePath,string fileName);
    //~Document();
    bool Init(int mode);
    bool Encode();
    bool Decode();
    bool checkTree();
    int toInt(char* bit);
    bool toBinary(char* binary,int num);

};
#endif

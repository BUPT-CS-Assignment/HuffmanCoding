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
#define TOP_NUM 256

struct Node{
    int val ,parent;
    long long weight;
    Node(int val,long long weight,int parent){
        this->val=val;
        this->weight=weight;
        this->parent=parent;
    }
    friend bool operator < (Node a,Node b){
        return a.weight < b.weight;
    }
};

class reCodingMethod {
    unsigned char buff[64] , buff_p , buff_t;
    unsigned char bitSeq[256] , bitSeq_p;
public:
    void searchTree(long long HuffmanTree[][4] , int now);
    bool enCodingTree(FILE **fp_h , long long HuffmanTree[][4] , const int top );
    bool buildTree(FILE **fp ,long long HuffmanTree[][4] , int &now);
    int deCodingTree(FILE **fp_h , long long HuffmanTree[][4]);
};

class Document:public reCodingMethod{
private:
    int BytecodeArray[256];
    long long HuffmanTree[512][4];
    string Words[258];
    const char* FILEpath;
    const char* FILEname; 
    FILE* reader;
    FILE* writer;
    Heap<Node> Nodes;
    int top;
    bool Readin(int mode);
    bool HTreeInit();
    bool Select(int & node1,int & node2);
    bool HTreeCreate();
    bool WordsCreate();
public:
    Document(string filePath,string fileName);
    ~Document();
    bool Init(int mode);
    bool Encode();
    bool Decode();
    bool checkTree();
    int toInt(char* bit);
    bool toBinary(char* binary,int num);
};
#endif

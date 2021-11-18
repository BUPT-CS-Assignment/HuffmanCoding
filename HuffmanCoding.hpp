#ifndef HUFFMANCODING_H
#define HUFFMANCODING_H
#include "Heap.hpp"
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

#define _weigth 0
#define _left 1
#define _right 2
#define _parent 3
#define _value 4

struct Node{
    int val;
    int weight;
    int parent;
    Node(int val,int weight,int parent){
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
    int BytecodeArray[258];
    int HuffmanTree[512][5];
    string Words[258];
    FILE *fp;
    int top;
    Heap<Node> Nodes;
    //
    bool Readin();
    bool HTreeInit();
    bool Select(int & node1,int & node2);
    bool HTreeCreate();
    bool WordsCreate();
public:
    Document(const char *Address);
    //~Document();
    int getTop();

};
/*
class Code{
private:
    int HuffmanTree[512][4];
    FILE* fp;
public:
    bool coding();

};
*/
#endif
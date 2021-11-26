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

class reCodingMethod {
    unsigned char buff[64] , buff_p , buff_t;
    unsigned char bitSeq[256] , bitSeq_p;

public:
    void searchTree(long long HuffmanTree[][4] , int now);
    bool enCodingTree(FILE **fp_h , long long HuffmanTree[][4] , const int top );
    bool buildTree(FILE **fp ,long long HuffmanTree[][4] , int &now);
    int deCodingTree(FILE **fp_h , long long HuffmanTree[][4]);
};

void reCodingMethod::searchTree(long long HuffmanTree[][4] , int now) {
    bool Cflag = (HuffmanTree[now][_left] == -1);
    buff[buff_t] |= ((!Cflag) << buff_p++);
    //printf("T: %d : %.2x : %d -- %d\n" ,buff_t , buff[buff_t], now , Cflag);
    if(buff_p == 8) buff_t++ , buff_p = 0;
    if(Cflag) bitSeq[bitSeq_p++] = now;
    else    searchTree( HuffmanTree , HuffmanTree[now][_left]),
            searchTree( HuffmanTree , HuffmanTree[now][_right]);
}


bool reCodingMethod::enCodingTree(FILE **fp_h , long long HuffmanTree[][4] , const int top ) {
    FILE *fp = *fp_h;
    searchTree(HuffmanTree , top);buff_t++;
    fwrite(&buff_t , 1 , 1 ,fp);
    fwrite(buff , buff_t , 1 ,fp);
    fwrite(bitSeq , bitSeq_p , 1 ,fp);

    return true;
};

bool reCodingMethod::buildTree(FILE **fp ,long long HuffmanTree[][4] , int &now){
    if(buff_p == 8) {buff_t++,buff_p = 0;}
    unsigned char t;    int _now = now;
    bool Cflag = (buff[buff_t] & (1 << buff_p++));
    
    if(!Cflag) {now--; return true;}
    else {
        HuffmanTree[_now][_left] = ++now;
        if(buildTree(fp , HuffmanTree , now )) {
            fread(&t , 1 , 1 , *fp);
            HuffmanTree[_now][_left] = t;            
        }
        HuffmanTree[_now][_right] = ++now;
        if( buildTree(fp , HuffmanTree , now )) {
            fread(&t , 1 , 1 , *fp);
            HuffmanTree[_now][_right] = t;
        }
    } 
    return false;
};
int reCodingMethod::deCodingTree(FILE **fp_h , long long HuffmanTree[][4] ) {
    FILE *fp = *fp_h;
    unsigned char head_t = 0;
    fread(&head_t, 1 , 1 ,fp);
    fread(buff, 1 , head_t , fp);

    int top = 256;  buff_p = 0;
    buildTree(&fp , HuffmanTree , top);

 
    return 256;
}

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

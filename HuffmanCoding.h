#ifndef _HUFFMANCODING_H
#define _HUFFMANCODING_H
#include "Heap.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <windows.h>
#include<math.h>
using namespace std;

#define _weigth 0   //权值
#define _left 1     //左子树
#define _right 2    //右子树
#define _parent 3   //双亲
#define TOP_NUM 257 //树根编号

//为小根堆定义节点结构
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

//定义Document类，包含编解码方法
class Document{
private:
    int BytecodeArray[256];  //权值记录数组
    long long HuffmanTree[512][4];  //哈夫曼树
    string Words[258];  //字节编码数组
    //
    unsigned char buff[64], bitSeq[256];
    int bitSeq_p, buff_p , buff_t;
    //
    const char* FILEpath,* FILEname;  //读写文件名
    FILE* reader,* writer;  //读写文件指针
    long long FILEsize;  //文件大小（字节数）
    Heap<Node> Nodes;  //小根堆
    int top;   //树根编号
    //编码函数
    bool ReadinSource();
    bool HTreeInit();
    bool Select(int & node1,int & node2);
    bool HTreeCreate();
    bool WordsCreate();
    void searchTree(int now);
    bool enCodingTree(const int top);
    //解码函数
    bool ReadinCode();
    bool RebuildTree(int &now);
    //
public:
    Document(string filePath,string fileName);
    ~Document();
    bool Init(int mode);
    bool Encode();
    bool Decode();
    void checkTree();
    int toInt(char* bit);
    void toBinary(char* binary,int num);
};
#endif

#ifndef _HUFFMANCODING_H
#define _HUFFMANCODING_H
#include "Heap.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <windows.h>
#include<math.h>
using namespace std;

#define _weigth 0   //Ȩֵ
#define _left 1     //������
#define _right 2    //������
#define _parent 3   //˫��
#define TOP_NUM 257 //�������

//ΪС���Ѷ���ڵ�ṹ
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

//����Document�࣬��������뷽��
class Document{
private:
    int BytecodeArray[256];  //Ȩֵ��¼����
    long long HuffmanTree[512][4];  //��������
    string Words[258];  //�ֽڱ�������
    //
    unsigned char buff[64], bitSeq[256];
    int bitSeq_p, buff_p , buff_t;
    //
    const char* FILEpath,* FILEname;  //��д�ļ���
    FILE* reader,* writer;  //��д�ļ�ָ��
    long long FILEsize;  //�ļ���С���ֽ�����
    Heap<Node> Nodes;  //С����
    int top;   //�������
    //���뺯��
    bool ReadinSource();
    bool HTreeInit();
    bool Select(int & node1,int & node2);
    bool HTreeCreate();
    bool WordsCreate();
    void searchTree(int now);
    bool enCodingTree(const int top);
    //���뺯��
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

#include"HuffmanCoding.hpp"
#include"Heap.hpp"
#include <stdio.h>

using namespace std;


Document::Document(const char *Address){
    fp=fopen(Address,"rb");
    if(fp==NULL){
        cout<<"No such file or failed to open."<<endl;
    }else{
        Readin();
        HTreeInit();
        HTreeCreate();
        //WordsCreate();
    }
}

bool Document::Readin(){
    FILE *reader=fp;
    char *buffer;
    while(!feof(reader)){
        int count=fread(buffer,1,1,reader);
        if(count>0)
            BytecodeArray[(int)*buffer]++;
    }
}

bool Document::HTreeInit(){
    top=0;
    HuffmanTree[0][_parent]=-1;
    int flag=1;
    for(int i=0;i<=258;i++){
        if(BytecodeArray[i]!=0){
            Nodes.push(Node(i,BytecodeArray[i],0));
            HuffmanTree[i][_weigth]=BytecodeArray[i];
        }
    }
};

bool Document::Select(int & node1,int & node2){
    node1=node2=0;
    if(!Nodes.empty()){
        node1=Nodes.top().val;    Nodes.pop();
    }
    if(!Nodes.empty()){
        node2=Nodes.top().val;    Nodes.pop();
    }
}

bool Document::HTreeCreate(){
    int flag=257;
    while(!Nodes.empty()){
        int node1,node2;
        Select(node1,node2);
        int new_weight=HuffmanTree[node1][_weigth]+HuffmanTree[node2][_weigth];
        HuffmanTree[flag++][_weigth]=new_weight;
        HuffmanTree[node1][_parent]=HuffmanTree[node2][_parent]=flag-1;
        if(!Nodes.empty())
            Nodes.push(Node(flag-1,new_weight,0));
            top=flag-1;
            //cout<<new_weight<<endl;
    }
}

int Document::getTop(){
    return top;
}



#include"HuffmanCoding.hpp"
#include"Heap.hpp"
#include <stdio.h>
#include<string>
using namespace std;

Document::Document(const char *Address){
    path=Address;
    if(!Readin()){
        cout<<"No such file or failed to open."<<endl;
    }else{
        HTreeInit();
        HTreeCreate();
        WordsCreate();
    }
}

bool Document::Readin(){
    FILE* reader=fopen(path,"rb");
    if(reader==NULL)  return false;
    char buffer[3];
    if(!reader)  return false;
    while(!feof(reader)){
        int count=fread(buffer,1,1,reader);
        if(count>0)
            BytecodeArray[(int)*buffer]++;
    }
    fclose(reader);
    return true;
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
    return true;
}

bool Document::Select(int & node1,int & node2){
    node1=node2=0;
    if(!Nodes.empty()){
        node1=Nodes.top().val;    Nodes.pop();
    }
    if(!Nodes.empty()){
        node2=Nodes.top().val;    Nodes.pop();
    }
    return true;
}

bool Document::HTreeCreate(){
    int flag=257;
    if(Nodes.empty())  return false;
    while(!Nodes.empty()){
        int node1,node2;
        Select(node1,node2);
        int new_weight = HuffmanTree[node1][_weigth] + HuffmanTree[node2][_weigth];
        HuffmanTree[flag++][_weigth] = new_weight;
        HuffmanTree[node1][_parent] = HuffmanTree[node2][_parent] = flag-1;
        HuffmanTree[flag-1][_left] = node1;
        HuffmanTree[flag-1][_right] = node2;
        if(!Nodes.empty())
            Nodes.push(Node(flag-1,new_weight,0));
            top=flag-1;
    }
    return true;
}

bool Document::WordsCreate(){
    for(int i=0;i<=256;i++){
        if(BytecodeArray[i]>0){
            int cur=i;
            int pre=HuffmanTree[cur][_parent];
            string code="";
            while(pre!=-1){
                code = HuffmanTree[pre][_left]==cur ? ('0'+code):('1'+code);
                cur=pre;
                pre=HuffmanTree[pre][_parent];
            }
            Words[i]=code;
        }
    }
}

bool Document::Encode(){
    FILE *reader=fopen(path,"rb");
    FILE *writer=fopen("out.txt","wb");
    if(!reader||!writer){
        printf("Failed to encode. File Error.\n");
        return false;
    }
    for(int i=0;i<=256;i++){
        if(BytecodeArray[i]>0){
            fprintf(writer,"%d %d ",i,BytecodeArray[i]);
        }
    }
    fprintf(writer,"-1\n");
    char buffer[3];
    while(!feof(reader)){
        int count=fread(buffer,1,1,reader);
        if(count>0)
            fprintf(writer,"%s",Words[(int)*buffer].c_str());
    }
    fclose(reader);
    fclose(writer);
    return true;
}




#include"HuffmanCoding.h"
#include"Heap.hpp"
using namespace std;

Document::Document(string filePath,string fileName){
    FILEpath=filePath.c_str();
    FILEname=fileName.c_str();
    fileSize=0;
}

bool Document::Init(int mode){
    if(!Readin(mode)){
        cout<<"Oops! Read-in failed.\nNo such file or failed to open."<<endl;
    }else{
        Sleep(500);
        cout<<"Read-in success.\nCreating CodeTree..."<<endl;
        Sleep(500);
        if(HTreeInit()&&HTreeCreate()&&WordsCreate())
            return true;
        cout<<"Oops! Something went wrong. Try again later."<<endl;
        return false;
    }
}

bool Document::HTreeInit(){
    HuffmanTree[256][_parent]=-1;
    top=256;
    int flag=1;
    for(int i=0;i<512;i++){
        HuffmanTree[i][_weigth]=0;
        HuffmanTree[i][_left]=-1;
        HuffmanTree[i][_right]=-1;
        HuffmanTree[i][_parent]=256;
        if(i<256&&BytecodeArray[i]!=0){
            Nodes.push(Node(i,BytecodeArray[i],256));
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
        long long new_weight = HuffmanTree[node1][_weigth] + HuffmanTree[node2][_weigth];
        HuffmanTree[flag++][_weigth] = new_weight;
        HuffmanTree[node1][_parent] = HuffmanTree[node2][_parent] = flag-1;
        HuffmanTree[flag-1][_left] = node1;
        HuffmanTree[flag-1][_right] = node2;
        if(!Nodes.empty())
            Nodes.push(Node(flag-1,new_weight,256));
            top=flag-1;
    }
    return true;
}

bool Document::WordsCreate(){
    for(int i=0;i<256;i++){
        if(BytecodeArray[i]>0){
            int cur=i;
            int pre=HuffmanTree[cur][_parent];
            string code="";
            while(pre!=256){
                code = HuffmanTree[pre][_left]==cur ? ('0'+code):('1'+code);
                cur=pre;
                pre=HuffmanTree[pre][_parent];
            }
            Words[i]=code;
            
        }
    }
    return true;
}

bool Document::checkTree(){
    cout<<endl;
    for(int i=0;i<512;i++){
        cout<<i<<" "//<<(char)i<<" "
            <<HuffmanTree[i][_weigth]<<" "
            <<HuffmanTree[i][_left]<<" "
            <<HuffmanTree[i][_right]<<" "
            <<HuffmanTree[i][_parent]<<" "
            <<(i<=256?Words[i]:" ")<<endl;
    }
}

int Document::toInt(char bit[]){
    int out=0;
    for(int i=0;i<8;i++){
        out+=(bit[i]-0x30)*pow(2,7-i);
    }
    return out;
}

bool Document::toBinary(char* binary,int num){
    int dir=0;
    while(num!=0){
        if(num%2==1)
            binary[dir++]='1';
        else
            binary[dir++]='0';
        num=num/2;
    }
    for(int i=0;i<4;i++){
        char temp=binary[i];
        binary[i]=binary[7-i];
        binary[7-i]=temp;
    }
    return true;
}




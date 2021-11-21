#include"HuffmanCoding.h"
#include"Heap.hpp"
using namespace std;

Document::Document(const char *Address,int mode_chose){
    path=Address;
    mode=mode_chose;
    if(!Readin(mode)){
        cout<<"Oops!\nNo such file or failed to open."<<endl;
    }else{
        Sleep(500);
        cout<<"Read-in success.\nCreating codeTree..."<<endl;
        //HTreeInit();
        //HTreeCreate();
        //watch();
        ///*
        Sleep(500);
        if(HTreeInit()&&HTreeCreate()&&WordsCreate()){
            cout<<"Going to "<<(mode==0?"encoding":"decoding")<<"..."<<endl;
            Sleep(500);
            if(mode==0){  Encode();  }
            else{  Decode();  }    
        }else{
            cout<<"Oops! Something went wrong. Try again later."<<endl;
        }
        //*/
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
                //cout<<pre<<endl;
                code = HuffmanTree[pre][_left]==cur ? ('0'+code):('1'+code);
                cur=pre;
                pre=HuffmanTree[pre][_parent];
            }
            Words[i]=code;
            
        }
    }
    //cout<<"in2"<<endl;
    return true;
}

bool Document::watch(){
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





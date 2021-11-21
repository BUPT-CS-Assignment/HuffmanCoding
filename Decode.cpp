#include"HuffmanCoding.h"

bool Document::Decode(){
    FILE* reader=fopen(path,"r");
    FILE *writer=fopen("results","wb");
    if(!reader||!writer){
        cout<<"Oops! Something went wrong. Try again later."<<endl;
        return false;
    }
    int num=-1;
    while(!feof(reader)){
        if(fscanf(reader,"%d",&num)<=0||num==-1)
            break;
    }
    int flag=top;
    while(!feof(reader)){
        char c;
        if(fscanf(reader,"%c",&c)<=0)  break;
        if(c=='0'){
            flag=HuffmanTree[flag][_left];
        }else if(c=='1'){
            flag=HuffmanTree[flag][_right];
        }else if(c=='\n'){
        }else{
            cout<<"Oops!\nDecoding failed! Invalid code exists."<<endl;
            return false;
        }
        if(HuffmanTree[flag][_left]==-1 && HuffmanTree[flag][_right]==-1){
            unsigned char ch=(unsigned char)flag;
            fwrite(&ch,1,1,writer);
            flag=top;
        }
    }
    cout<<"Finish. Check 'results'."<<endl;
    fclose(reader);
    fclose(writer);
    return true;
}


#include"HuffmanCoding.h"

bool Document::Decode(){
    FILE* reader=fopen(path,"rb");
    FILE *writer=fopen(fileName,"wb");
    if(!reader||!writer){
        cout<<"Oops! Something went wrong. Try again later."<<endl;
        return false;
    }
    int num=-1;
    while(!feof(reader)){
        for(int i=0;i<256;i++){
            if(fscanf(reader,"%d",&num)<=0){
                return false;
            } 
        }
        break;
    }
    int data=0;
    int flag=top;
    unsigned char buffer[3]="00";
    while(!feof(reader)){
        if(fread(buffer,1,1,reader)<=0)
            return false;
        if((int)*buffer==10)
            break;
    }
    while(!feof(reader)){
        if(fread(buffer,1,1,reader)<=0)
            return false;
        char bits[9]="00000000";
        if(toBinary(bits,(int)*buffer)==0)
            return false;
        for(int i=0;i<8;i++){
            if(data>=fileSize){
                cout<<"Finish. Check '"<<fileName<<"'."<<endl;
                fclose(reader);
                fclose(writer);
                return true;
            }
            if(bits[i]=='0'){
                flag=HuffmanTree[flag][_left];
            }else{
                flag=HuffmanTree[flag][_right];
            }
            if(HuffmanTree[flag][_left]==-1 && HuffmanTree[flag][_right]==-1){
                unsigned char ch=(unsigned char)flag;
                fwrite(&ch,1,1,writer);
                data++;
                flag=top;
            }
        }
    }
    
}


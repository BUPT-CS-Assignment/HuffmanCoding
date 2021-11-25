#include"HuffmanCoding.h"

bool Document::Decode(){
    FILE* reader=fopen(FILEpath,"rb");
    FILE *writer=fopen(FILEname,"wb");
    if(!reader||!writer){
        cout<<"Oops! Something went wrong. Try again later."<<endl;
        return false;
    }
    int buffers=0;
    while(!feof(reader)){
        for(int i=0;i<256;i++){
            if(fread(&buffers,4,1,reader)<=0) return false;
        }
        break;
    }
    unsigned long long data=0;
    int flag=top;
    int buffer=0;
    //Decode process.
    while(!feof(reader)){
        if(fread(&buffer,1,1,reader)<=0)
            return false;
        char bits[9]="00000000";
        if(toBinary(bits,buffer)==0)  return false;
        for(int i=0;i<8;i++){
            if(data>=fileSize){
                cout<<"Finish. Check '"<<FILEname<<"'."<<endl;
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
                //unsigned char ch=(unsigned char)flag;
                if(fwrite(&flag,1,1,writer)<=0)  return false;
                data++;
                flag=top;
            }
        }
    }
    
}


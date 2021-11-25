#include"HuffmanCoding.h"

bool Document::Readin(int mode){
    if(mode==0){
        //read in source file while encoding.
        fseek(reader,0,0);
        if(reader==NULL)  return false;
        int buffer=0;
        while(!feof(reader)){
            if(fread(&buffer,1,1,reader)>0)
                BytecodeArray[buffer]++;      
            
        }
        return true;
    }else if(mode==1){
        //read in cipher file while decoding.
        fseek(reader,0,0);
        int num,wt;
        int flag=0;
        int number;
        while(!feof(reader)){
            for(int i=0;i<256;i++){
                if(fread(&number,4,1,reader)<=0) 
                    return false;
                BytecodeArray[i]=number;
            }
            break;
        }
        return true;
    }
    return false;
}

#include"HuffmanCoding.h"

bool Document::Readin(int mode){
    if(mode==0){
        //read in source file while encoding.
        FILE* reader=fopen(FILEpath,"rb");
        if(reader==NULL)  return false;
        unsigned char buffer[3];
        while(!feof(reader)){
            if(fread(buffer,1,1,reader)>0)
                BytecodeArray[(int)*buffer]++;
                fileSize++;
        }
        fclose(reader);
    }else if(mode==1){
        //read in cipher file while decoding.
        FILE* reader=fopen(FILEpath,"r");
        int num,wt;
        int flag=0;
        while(!feof(reader)){
            for(int i=0;i<256;i++){
                if(fscanf(reader,"%d",&num)<=0){
                    return false;
                }
                BytecodeArray[i]=num;
                fileSize+=num;
            }
            break;
        }
        fclose(reader);
    }else{
        return false;
    }
    return true;
}

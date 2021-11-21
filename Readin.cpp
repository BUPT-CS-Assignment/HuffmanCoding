#include"HuffmanCoding.h"

bool Document::Readin(int mode){
    if(mode==0){
        //read in source file while encoding.
        FILE* reader=fopen(path,"rb");
        if(reader==NULL)  return false;
        unsigned char buffer[3];
        while(!feof(reader)){
            //cout<<(int)*buffer<<endl;
            if(fread(buffer,1,1,reader)>0)
                BytecodeArray[(int)*buffer]++;
        }
        fclose(reader);


    }else if(mode==1){
        //read in cipher file while decoding.

        FILE* reader=fopen(path,"r");
        int num,wt;
        int flag=0;
        while(!feof(reader)){
            int count=fscanf(reader,"%d",&num);
            if(count<=0||num==-1)  break;
            count=fscanf(reader,"%d",&wt);
            if(count<=0||num==-1)  break;
            BytecodeArray[num]=wt;
        }
        fclose(reader);
    }
    return true;
}

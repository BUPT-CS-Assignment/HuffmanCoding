#include"HuffmanCoding.h"

bool Document::Encode(){
    FILE *reader=fopen(FILEpath,"rb");
    FILE *writer=fopen(FILEname,"wb");
    if(!reader||!writer){
        cout<<"Oops! Something went wrong. Try again later."<<endl;
        return false;
    }
    for(int i=0;i<256;i++){
        int num=BytecodeArray[i];
        if(fwrite(&num,4,1,writer)<=0) return false;        
    }
    //output by 8 bits
    int buffer=0;
    char bitStr[9]="00000000";
    int indic=0;
    while(!feof(reader)){
        if(fread(&buffer,1,1,reader)>0){
            const char *str= Words[buffer].c_str();
            for(int i=0;i<strlen(str);i++){
                bitStr[indic++]=str[i];
                if(indic==8){
                    int byte=toInt(bitStr);
                    fwrite(&byte,1,1,writer);
                    strcpy(bitStr,"00000000");
                    indic=0;
                }
            }
        }
    }
    if(indic!=0){
        int byte=toInt(bitStr);
        if(fwrite(&byte,1,1,writer)<=0) return false;
    }
    cout<<"Finish. Check '"<<FILEname<<"'."<<endl;
    fclose(reader);
    fclose(writer);
    return true;
}





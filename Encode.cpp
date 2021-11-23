#include"HuffmanCoding.h"

int toBinary(char bit[]);
bool Document::Encode(){
    FILE *reader=fopen(path,"rb");
    FILE *writer=fopen(fileName,"wb");
    if(!reader||!writer){
        cout<<"Oops! Something went wrong. Try again later."<<endl;
        return false;
    }
    for(int i=0;i<256;i++){
        fprintf(writer,"%d\t",BytecodeArray[i]);          
    }
    fprintf(writer,"\n");
    //output by 8 bits
    unsigned char buffer[3];
    char bitStr[9]="00000000";
    int indic=0;
    while(!feof(reader)){
        if(fread(buffer,1,1,reader)>0){
            const char *str= Words[(int)*buffer].c_str();
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
        fwrite(&byte,1,1,writer);
    }
    cout<<"Finish. Check '"<<fileName<<"'."<<endl;
    fclose(reader);
    fclose(writer);
    return true;
}





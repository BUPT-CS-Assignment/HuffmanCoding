#include"HuffmanCoding.h"

bool Document::Encode(){
    FILE *reader=fopen(path,"rb");
    FILE *writer=fopen("out.txt","wb");
    if(!reader||!writer){
        cout<<"Oops! Something went wrong. Try again later."<<endl;
        return false;
    }
    for(int i=0;i<256;i++){
        if(BytecodeArray[i]>0)
            fprintf(writer,"%d %d ",i,BytecodeArray[i]);
    }
    fprintf(writer,"-1\n");
    unsigned char buffer[3];
    int flag=0;
    while(!feof(reader)){
        if(fread(buffer,1,1,reader)>0){
            const char *str= Words[(int)*buffer].c_str();
            for(int i=0;i<strlen(str);i++){
                flag++;
                fwrite(&str[i],1,1,writer);
                if(flag==8){
                    //fprintf(writer," ");
                    flag=0;
                }
            }
            
        }
        
        //fprintf(writer,"%s",Words[(int)*buffer].c_str());
    }
    cout<<"Finish. Check 'out.txt'."<<endl;
    fclose(reader);
    fclose(writer);
    return true;
}






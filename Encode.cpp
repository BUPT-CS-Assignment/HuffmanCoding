#include"HuffmanCoding.h"

bool Document::Encode(){
    FILE *reader=fopen(path,"rb");
    FILE *writer=fopen("out.txt","wb");
    if(!reader||!writer){
        cout<<"Oops! Something went wrong. Try again later."<<endl;
        return false;
    }
    for(int i=0;i<=256;i++){
        if(BytecodeArray[i]>0)
            fprintf(writer,"%d %d ",i,BytecodeArray[i]);
    }
    fprintf(writer,"-1\n");
    char buffer[3];
    while(!feof(reader)){
        int count=fread(buffer,1,1,reader);
        if(count>0)
            fprintf(writer,"%s",Words[(int)*buffer].c_str());
    }
    cout<<"Finish. Check 'out.txt'."<<endl;
    fclose(reader);
    fclose(writer);
    return true;
}






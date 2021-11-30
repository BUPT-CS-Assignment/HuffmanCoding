#include"HuffmanCoding.h"

bool Document::Decode(){
    fseek(reader,0,0);
    fseek(writer,0,0);
    if(!reader||!writer){
        cout<<"Oops! Something went wrong. Try again later."<<endl;
        return false;
    }
    top = reCodingMethod::deCodingTree(&reader , HuffmanTree);
    // for(int i = 256 ; i < 512 ; i++) {
    //     printf("%d -- %d -- %d\n" ,i , HuffmanTree[i][_left] ,HuffmanTree[i][_right] );
    // }
    // int buffers=0;
    // while(!feof(reader)){
    //     for(int i=0;i<256;i++){
    //         if(fread(&buffers,4,1,reader)<=0) return false;
    //     }
    //     break;
    // }
    unsigned long long data=0;
    int flag=top;
    int buffer=0;
    //Decode process.
    while(!feof(reader)){
        if(fread(&buffer,1,1,reader)<=0)
            return false;
        char bits[9]="00000000";
        if(toBinary(bits,buffer)==0)
            return false;
        for(int i=0;i<8;i++){
            // if(flag==-1||flag==256)
            //     return false;
            // if(data>=HuffmanTree[top][_weigth]){
            //     cout<<"Finish. Check '"<<FILEname<<"'."<<endl;
            //     return true;
            // }
            if(bits[i]=='0'){
                flag=HuffmanTree[flag][_left];
            }else{
                flag=HuffmanTree[flag][_right];
            }
            printf("Now : %d\n" ,flag);
            if(HuffmanTree[flag][_left]==-1 && HuffmanTree[flag][_right]==-1){
                //unsigned char ch=(unsigned char)flag;
                //printf("Leaf : %d\n" ,flag);
                if(fwrite(&flag,1,1,writer)<=0)
                    return false;
                data++;
                flag=top;
            }
        }
    }
    return false;
    
}


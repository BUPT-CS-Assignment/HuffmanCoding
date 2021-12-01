#include "HuffmanCoding.h"

int main(int argc,char* argv[]){
    int mode = 0 ,  mode_2 = 0; 
    mode=(argv[1][0]-'0');
        string filePath="in.txt",fileName="out.txt";
        /////////////////////////////////////////////////////////////////  
        Document File(filePath,fileName);      //Construct FILE.
        switch(mode){
            case 0:
                if(File.Init(0)){
                    if(!File.Encode())
                        cout<<"Encode failed. Check your file."<<endl;
                }break;
            case 1:
                if(File.Init(1)){
                    if(!File.Decode())
                        cout<<"Invalid CodeTree. Check your file."<<endl;
                }break;
        }
    return 0;
}
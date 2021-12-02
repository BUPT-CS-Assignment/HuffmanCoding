#include "HuffmanCoding.h"

int main(){
    int mode = 0 ,  mode_2 = 0; 
    cout<<"Enter 0 to encode,1 to decode and -1 to exit.\nMode:";
    scanf("%d",&mode);
    while(mode!=-1){
        // Readin process.
        string filePath,fileName;
        cout<<"Enter name or path of source file: ";
        cin>>filePath;    
        if(mode!=2){
            cout<<"Enter export file name: ";
            cin>>fileName;
        }else{
            fileName="__out";
        }
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
            case 2:
                cout<<"Enter check_Mode:";
                cin>>mode_2;
                if(File.Init(mode_2)){
                    cout<<"HuffmanTree check for mode:"<<mode_2<<endl;
                    File.checkTree();
                }break;
            default:
                cout<<"Invalid mode number. Check your input."<<endl;
        }
        Sleep(300);
        cout<<"Enter 0 to encode,1 to decode and -1 to exit.\nMode:";
        scanf("%d",&mode);
    }
    cout<<"\nSee you next time."<<endl;
    cout<<"\n--Made by @NoUITeam.\n--Website: https://github.com/NoUITeam"<<endl;
    Sleep(2000);
    return 0;
}
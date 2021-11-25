#include"HuffmanCoding.h"
#include"Document.cpp"
#include"Readin.cpp"
#include"Encode.cpp"
#include"Decode.cpp"
using namespace std;
int main(){
    int mode=0; int mode_2=0; 
    string filePath,fileName="out";
    cout<<"Enter 0 to encode,1 to decode and -1 to exit.\nMode:";
    cin>>mode;
    while(mode!=-1){
        // Readin process.
        cout<<"Enter name or path of a file: ";
        cin>>filePath;    
        if(mode!=2){
            cout<<"Enter export file name: ";
            cin>>fileName;
        }
        /////////////////////////////////////////////////////////////////  
        Document File(filePath,fileName);      //Construct FILE.
        switch(mode){
            case 0:
                if(File.Init(0)){
                    cout<<"Initial success. Going to encode."<<endl;
                    File.Encode();
                }else{
                    cout<<"Initial failed. Try again later."<<endl;
                }
                break;
            case 1:
                if(File.Init(1)){
                    cout<<"Initial success. Going to decode."<<endl;
                    if(!File.Decode())
                        cout<<"Invalid CodeTree! Check your file."<<endl;
                }else{
                    cout<<"Initial failed. Try again later."<<endl;
                }
                break;
            case 2:
                cout<<"Enter check_Mode:";
                cin>>mode_2;
                if(File.Init(mode_2)){
                    cout<<"HuffmanTree check for mode:"<<mode_2<<endl;
                    if(!File.checkTree())
                         cout<<"Error. Try again later."<<endl;
                    break;
                }
            default:
                cout<<"Invalid mode number! Check your input."<<endl;
                break;
        }
        Sleep(500);
        cout<<"Enter 0 to encode,1 to decode and -1 to exit.\nMode:";
        cin>>mode;
    }
    return 0;
}

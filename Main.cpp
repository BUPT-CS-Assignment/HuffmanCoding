#include"HuffmanCoding.h"
#include"Document.cpp"
#include"Readin.cpp"
#include"Encode.cpp"
#include"Decode.cpp"
using namespace std;
int main(){
    int mode=0; int mode_2=0; 
    string filePath,fileName;
    int flag=1;
    while(flag==1){
        // Readin process.
        cout<<"Enter 0 for encode,1 for decode and 2 for HuffmanTree check.\nMode:";
        cin>>mode;
        cout<<"Enter name or path of a file:";
        cin>>filePath;    
        cout<<"Enter export file name:";
        if(mode!=2)
            cin>>fileName;
        else
            fileName="out";
        /////////////////////////////////////////////////////////////////  
        Document File(filePath,fileName);      //Construct FILE.
        switch(mode){
            case 0:
                if(File.Init(0))
                    cout<<"Initial success. Going to encode."<<endl;
                    File.Encode();
                break;
            case 1:
                if(File.Init(1))
                    cout<<"Initial success. Going to decode."<<endl;
                    File.Decode();
                break;
            case 2:
                cout<<"Enter check_Mode:";
                cin>>mode_2;
                if(File.Init(mode_2))
                    cout<<"HuffmanTree check for mode:"<<mode_2<<endl;
                    if(!File.checkTree())
                         cout<<"Error. Try again later."<<endl;
                break;
            default:
                cout<<"Invalid mode number! Check your input."<<endl;
                break;
        }
        cout<<"Enter 1 for continuing:";
        cin>>flag;
    }
    system("pause");
    return 0;
}

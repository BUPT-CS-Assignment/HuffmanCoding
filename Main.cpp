#include"HuffmanCoding.h"
#include"Document.cpp"
#include"Readin.cpp"
#include"Encode.cpp"
#include"Decode.cpp"
using namespace std;
int main(){
    int mode=0; string filePath,fileName;
    int flag=1; char ch;
    while(flag==1){
        cout<<"Enter name or path of a file:"<<endl;
        cin>>filePath;
        cout<<"Enter mode,0 for encode and 1 for decode:"<<endl;
        cin>>mode;
        cout<<"Enter export file name:"<<endl;
        cin>>fileName;
        const char* path=filePath.c_str();
        const char* name=fileName.c_str();
        Document test(path,mode,name);
        cout<<"Enter 1 for continuing:";
        cin>>flag;
    }
    system("pause");
    return 0;
}

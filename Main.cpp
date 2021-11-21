#include"HuffmanCoding.h"
#include"Document.cpp"
#include"Readin.cpp"
#include"Encode.cpp"
#include"Decode.cpp"
using namespace std;
int main(){
    int mode; string filePath;
    cout<<"Enter name or path of a file:";
    cin>>filePath;
    cout<<"Enter mode,0 for encode and 1 for decode:";
    cin>>mode;
    const char* path=filePath.c_str();
    Document test(path,mode);
    return 0;
}

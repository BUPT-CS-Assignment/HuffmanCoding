#include"HuffmanCoding.h"
#include"Document.cpp"
#include"Readin.cpp"
#include"Encode.cpp"
#include"Decode.cpp"
using namespace std;
int main(){
    string address1="in.txt",address2="out.txt";
    int mode0=0,mode1=1;
    /*
    cout<<"Enter name or path of a file:";
    cin>>filePath;
    cout<<"Enter mode:";
    cin>>mode;
    */
    const char* path1=address1.c_str();
    const char* path2=address2.c_str();
    Document test(path1,mode0);
    Document test2(path2,mode1);
    //test.watch();
    return 0;
}

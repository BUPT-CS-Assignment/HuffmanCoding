#include"HuffmanCoding.hpp"
#include"Document.cpp"
using namespace std;

int main(){
    string filePath;
    cout<<"Enter name or path of a file:";
    cin>>filePath;
    const char* path=filePath.c_str();
    Document test(path);
    test.Encode();
    cout<<"...\nEncode finish. Check 'out.txt'.";
    return 0;
}

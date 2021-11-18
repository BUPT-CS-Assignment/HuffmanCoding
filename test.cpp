#include"HuffmanCoding.hpp"
#include"Document.cpp"
using namespace std;
int main(){
    string filePath;
    cin>>filePath;
    const char* path=filePath.c_str();
    Document test(path);
    cout<<test.getTop()<<endl;
    return 0;
}
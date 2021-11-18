#include"HuffmanCoding.hpp"
#include"Document.cpp"
using namespace std;

int main(){
    string filePath;
    cout<<"输入文件路径或当前路径下文件名:";
    cin>>filePath;
    const char* path=filePath.c_str();
    Document test(path);
    cout<<test.getTop()<<endl;
    return 0;
}
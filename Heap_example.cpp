#include "Heap.hpp"
/*
该模块实现了小根堆这一数据结构，保证：
    1.创建一个自定义节点集合
    2.每次从集合中取出的元素为集合中的规定最小值
    3.不定长。
下面给出使用样例
*/

//自定义类
struct Node
{
    int data;
    double tag;
    Node *L ,*R;
    //自定义构造函数
    Node(int _data, Node *_l =NULL,Node *_r=NULL):data(_data) , L(_l) ,R(_r){};

    //必须定义排序的方法——即重载小于号。如下为按照Node类型中data元素从小到大排序
    friend bool operator < (Node a , Node b) {
        return a.data < b.data;
    }
    //也可以这么做
    // bool operator <(Node &another) {
    //     return (*this).data < another.data;
    // }
};

int main(int argc, char* argv[]) {
    for(int i = 0 ; i < argc ; i++) {
        puts(argv[i]);
    }
    
    //声明一个小根堆
    Heap<Node> h;

    h.push( Node(3) ); //插入元素3
    h.push( Node(2) ); //插入元素2
    h.push( Node(1) ); //插入元素1
    
    if(!h.empty())  //判断堆顶非空
        printf("Top data is: %d\n" ,h.top().data); //输出堆顶实例的元素
    h.pop();        //删除堆顶元素
    printf("Top data is: %d\n" ,h.top().data); //输出堆顶实例的元素

    h.print();
    return 0;
}
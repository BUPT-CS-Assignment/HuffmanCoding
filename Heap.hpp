#ifndef HEAP_H
#define HEAP_H

#include <cstdio>
#include <cstdlib>
#include <iostream>
//С����ʵ��
template <class T>
class Heap {
private:
    size_t heapLength , lastPos; 
    T *heapNode ;

public:
    Heap():heapLength(1) , lastPos(1){
        heapNode = (T*)malloc(sizeof(T));
    }
    ~Heap() {
        free(heapNode);
    }
    //���������
    void print() ;
    //�ж϶��Ƿ�Ϊ��
    bool empty();
    //����Ѷ���Ԫ��
    T top() ;
    //��һ���ڵ�������
    void push(T node);
    //ɾ���Ѷ�Ԫ��
    void pop() ;
};

template<class T>
void Heap<T>::print() {
    printf("lastPos : %d \n" ,lastPos);
    for(int i = 1 ; i < lastPos ; i++) {
        printf("%d " ,heapNode[i]);
    }printf("\n");
}

template<class T>
bool Heap<T>::empty() {
    return (lastPos == 1);
}

template<class T>
T Heap<T>::top() {
    return heapNode[1];
}

template<class T>
void Heap<T>:: push(T node) {
    if(heapLength == lastPos) {
        try {
            heapLength <<= 1;
            heapNode = (T*)realloc(heapNode , sizeof(T) *heapLength);
        }
        catch(const std::bad_alloc& e) {
            std::cerr << e.what() << '\n';
        }
    }
    heapNode[lastPos++] = node;
    for(int nowPos = lastPos-1; nowPos > 1 ;){
        if(heapNode[nowPos] < heapNode[nowPos >> 1]) 
            std::swap(heapNode[nowPos] , heapNode[nowPos >> 1]) , nowPos >>= 1;
        else break;
    }
}

template<class T>
void Heap<T>::pop() {
    std::swap(heapNode[--lastPos] , heapNode[1]);
    for(int nowPos = 1 ; nowPos <<= 1 ; ) {
        if( nowPos+1 < lastPos && heapNode[nowPos+1] < heapNode[nowPos] )  nowPos++;
        if( nowPos < lastPos && heapNode[nowPos] < heapNode[nowPos >> 1]) 
            std::swap(heapNode[nowPos >> 1] , heapNode[nowPos]);
        else break;
    }
}

#endif
#include "HuffmanCoding.h"

//递归的DFS哈夫曼树,进行编码
void reCodingMethod::searchTree(long long HuffmanTree[][4] , int now) {
    bool Cflag = (HuffmanTree[now][_left] == -1);   //判断是否有孩子
    
    buff[buff_t] |= ((!Cflag) << buff_p++);         
    /*
        1.小端法，从右向左依次记录
        2.如果当前节点now有孩子，则Cflag为0 取反后将当前位置位1
        
        e.g:若buff_p为 4 , Cflag为0 首先1 << 4 得到b(0001 0000)
            若当前buff[buff_t] 为 0000 0011 ,进行|操作后为 0001 0011.
            完成记录操作;
    */
    
    if(buff_p == 8) buff_t++ , buff_p = 0;   //当写满一个字节后,buff_t+1,存储到下一个buff
    if(Cflag){ bitSeq[bitSeq_p++] = now; return ;} //如果是字节叶子,则存储当前节点的字节并返回
    
    searchTree( HuffmanTree , HuffmanTree[now][_left]);
    searchTree( HuffmanTree , HuffmanTree[now][_right]);
}

//对哈夫曼树进行编码
bool reCodingMethod::enCodingTree(FILE **fp_h , long long HuffmanTree[][4] , const int top ) {
    FILE *fp = *fp_h;
    searchTree(HuffmanTree , top);
    fwrite(&(++buff_t) , 1 , 1 ,fp); //写入首字节:树结构数组的大小
    fwrite(buff , buff_t , 1 ,fp);    //写入buff数组:存储树结构的
    fwrite(bitSeq , bitSeq_p , 1 ,fp);//写入bitseq数组:按照DFS序,依次存储权值从大到小的字节叶子

    return true;
};

//DFS遍历,建立哈夫曼树.返回当前节点是否为字节叶子
bool reCodingMethod::buildTree(FILE **fp ,long long HuffmanTree[][4] , int &now){
    unsigned char t;    int _now = now;
    bool Cflag = (buff[buff_t] & (1 << buff_p++)); //判断是否有孩子
    
    if(buff_p == 8) {buff_t++,buff_p = 0;}
    if(!Cflag) {now--; return true;}     //当前是字节叶子节点.
    
    HuffmanTree[_now][_left] = ++now;
    if( buildTree(fp , HuffmanTree , now )) { //如果是字节叶子节点,则顺序读入一个字节叶子数据
        fread(&t , 1 , 1 , *fp);
        HuffmanTree[_now][_left] = t;            
    }
    HuffmanTree[_now][_right] = ++now;
    if( buildTree(fp , HuffmanTree , now )) {
        fread(&t , 1 , 1 , *fp);
        HuffmanTree[_now][_right] = t;
    }
    return false;
};

//从文件中读入头部分,进行解码并建树.返回树根的编号(默认为256)
int reCodingMethod::deCodingTree(FILE **fp_h , long long HuffmanTree[][4] ) {
    FILE *fp = *fp_h;
    unsigned char head_t = 0;
    fread(&head_t, 1 , 1 ,fp); //读入首字节:树结构数组的大小
    fread(buff, 1 , head_t , fp); //读入树结构数组.此后fp位于首个字节叶子

    int top = TOP_NUM;  buff_p = 0;
    buildTree(&fp , HuffmanTree , top);

    return TOP_NUM;
}

#include"HuffmanCoding.h"

//读取源文件.
bool Document::ReadinSource() {
    fseek(reader, 0, 0);
    if (reader == NULL) return false;
    int buffer = 0;
    while (!feof(reader)) {
        if (fread( & buffer, 1, 1, reader) <= 0 && !feof(reader))
            return false;
        if(feof(reader)) return true;
        BytecodeArray[buffer]++;
    }
    return true;
}

//读取已解码文件
//从文件中读入头部分,进行解码并还原树
bool Document::ReadinCode() {
    int head_t = 0;
    int _top = TOP_NUM;
    memset(buff, 0, sizeof(buff));
    if (fread( & FILEsize, 8, 1, reader) <= 0) return false; //读取文件大小（字节数）
    if (fread( & head_t, 1, 1, reader) <= 0) return false; //读入首字节:树结构数组的大小
    if (fread( & buff, 1, head_t, reader) <= 0) return false; //读入树结构数组.此后fp位于首个字节叶子
    RebuildTree(_top); //构建树
    return true;
}

//DFS遍历,建立哈夫曼树.返回当前节点是否为字节叶子
bool Document::RebuildTree(int & now) {
    unsigned char t = 0;
    int _now = now;
    bool Cflag = (buff[buff_t] & (1 << buff_p--)); //判断是否有孩子
    if (buff_p == -1)
        buff_t++, buff_p = 7;
    if (!Cflag) {
        now--;
        return true;
    } //当前是字节叶子节点.
    HuffmanTree[_now][_left] = ++now;
    if (RebuildTree(now)) { //如果是字节叶子节点,则顺序读入一个字节叶子数据
        if (fread( & t, 1, 1, reader) <= 0) return false;
        HuffmanTree[_now][_left] = t;
    }
    HuffmanTree[_now][_right] = ++now;
    if (RebuildTree(now)) {
        if (fread( & t, 1, 1, reader) <= 0) return false;
        HuffmanTree[_now][_right] = t;
    }
    return false;
}
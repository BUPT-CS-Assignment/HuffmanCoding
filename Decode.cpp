#include"HuffmanCoding.h"

//解码过程
bool Document::Decode() {
    long long data = 0;
    int flag = TOP_NUM;
    int buffer = 0;
    while (!feof(reader)) {
        if (fread( & buffer, 1, 1, reader) <= 0 && !feof(reader)) //如果读取失败，则返回错误
            return false;
        if(feof(reader)){
            cout << "Finish. Check '" << FILEname << "'." << endl;
            return true;
        }
        char bits[9] = "00000000";
        toBinary(bits, buffer);
        ///8bit合并输出
        for (int i = 0; i < 8; i++) {
            flag = HuffmanTree[flag][bits[i] == '0' ? _left : _right]; //按bit读取到0，向左子树找；否则向右子树找
            if (HuffmanTree[flag][_left] == -1 && HuffmanTree[flag][_right] == -1) {   //判断是否是叶子节点，若是则写入叶子节点编号
                if (fwrite( & flag, 1, 1, writer) <= 0)
                    return false;
                data++;     //字节计数器+1
                flag = top;   //更新flag
            }
            if (data >= FILEsize) {   //判断是否到达文件尾
                cout << "Finish. Check '" << FILEname << "'." << endl;
                return true;
            }
        }
    }
    return false;
}


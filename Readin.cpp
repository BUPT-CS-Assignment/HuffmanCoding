#include"HuffmanCoding.h"

//��ȡԴ�ļ�.
bool Document::ReadinSource() {
    fseek(reader, 0, 0);
    if (reader == NULL) return false;
    int buffer = 0;
    while (!feof(reader)) {
        if (fread( & buffer, 1, 1, reader) <= 0 && !feof(reader))
            return false;
        BytecodeArray[buffer]++;
    }
    return true;
}

//��ȡ�ѽ����ļ�
//���ļ��ж���ͷ����,���н��벢��ԭ��
bool Document::ReadinCode() {
    int head_t = 0;
    int _top = TOP_NUM;
    memset(buff, 0, sizeof(buff));
    if (fread( & FILEsize, 8, 1, reader) <= 0) return false; //��ȡ�ļ���С���ֽ�����
    if (fread( & head_t, 1, 1, reader) <= 0) return false; //�������ֽ�:���ṹ����Ĵ�С
    if (fread( & buff, 1, head_t, reader) <= 0) return false; //�������ṹ����.�˺�fpλ���׸��ֽ�Ҷ��
    RebuildTree(_top); //������
    return true;
}

//DFS����,������������.���ص�ǰ�ڵ��Ƿ�Ϊ�ֽ�Ҷ��
bool Document::RebuildTree(int & now) {
    unsigned char t = 0;
    int _now = now;
    bool Cflag = (buff[buff_t] & (1 << buff_p++)); //�ж��Ƿ��к���
    if (buff_p == 8)
        buff_t++, buff_p = 0;
    if (!Cflag) {
        now--;
        return true;
    } //��ǰ���ֽ�Ҷ�ӽڵ�.
    HuffmanTree[_now][_left] = ++now;
    if (RebuildTree(now)) { //������ֽ�Ҷ�ӽڵ�,��˳�����һ���ֽ�Ҷ������
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
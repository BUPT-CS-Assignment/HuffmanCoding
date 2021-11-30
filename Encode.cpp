#include"HuffmanCoding.h"

//�������
bool Document::Encode() {
    fseek(reader, 0, 0);
    fseek(writer, 0, 0);
    if (!reader || !writer)
        return false;
    fwrite( & FILEsize, 8, 1, writer);
    enCodingTree(top);  //д�����ṹ����
    ///
    int buffer = 0;
    char bitStr[9] = "00000000";
    int indic = 0;
    while (!feof(reader)) {
        if (fread( & buffer, 1, 1, reader) > 0) {
            const char * str = Words[buffer].c_str();
            for (int i = 0; i < strlen(str); i++) {
                bitStr[indic++] = str[i];
                if (indic == 8) { //��8bitΪһ��λ���
                    int byte = toInt(bitStr);
                    fwrite( & byte, 1, 1, writer);
                    strcpy(bitStr, "00000000");
                    indic = 0;
                }
            }
        }
    }
    if (indic != 0) {  //���һ���ֽڲ���8λ����0����
        int byte = toInt(bitStr);
        if (fwrite( & byte, 1, 1, writer) <= 0) return false;
    }
    cout << "Finish. Check '" << FILEname << "'." << endl;
    return true;
}

//�Թ����������б���
bool Document::enCodingTree(int top) {
    searchTree(top);
    //
    fwrite( & (++buff_t), 1, 1, writer); //д�����ֽ�:���ṹ����Ĵ�С
    fwrite(buff, buff_t, 1, writer); //д��buff����:�洢���ṹ��
    fwrite(bitSeq, bitSeq_p, 1, writer); //д��bitseq����:����DFS��,���δ洢Ȩֵ�Ӵ�С���ֽ�Ҷ��
    return true;
};

//�ݹ��DFS��������,���б���
void Document::searchTree(int now) {
    bool Cflag = (HuffmanTree[now][_left] == -1); //�ж��Ƿ��к���
    buff[buff_t] |= ((!Cflag) << buff_p++);
    /*
        1.С�˷��������������μ�¼
        2.�����ǰ�ڵ�now�к��ӣ���CflagΪ0 ȡ���󽫵�ǰλ��λ1
        
        e.g:��buff_pΪ 4 , CflagΪ0 ����1 << 4 �õ�b(0001 0000)
            ����ǰbuff[buff_t] Ϊ 0000 0011 ,����|������Ϊ 0001 0011.
            ��ɼ�¼����;
    */
    if (buff_p == 8) buff_t++, buff_p = 0; //��д��һ���ֽں�,buff_t+1,�洢����һ��buff
    if (Cflag) {
        bitSeq[bitSeq_p++] = now;
        return;
    } //������ֽ�Ҷ��,��洢��ǰ�ڵ���ֽڲ�����

    searchTree(HuffmanTree[now][_left]);
    searchTree(HuffmanTree[now][_right]);
}


#include"HuffmanCoding.h"

//�������
bool Document::Decode() {
    long long data = 0;
    int flag = TOP_NUM;
    int buffer = 0;
    while (!feof(reader)) {
        if (fread( & buffer, 1, 1, reader) <= 0 && !feof(reader)) //�����ȡʧ�ܣ��򷵻ش���
            return false;
        if(feof(reader)){
            cout << "Finish. Check '" << FILEname << "'." << endl;
            return true;
        }
        char bits[9] = "00000000";
        toBinary(bits, buffer);
        ///8bit�ϲ����
        for (int i = 0; i < 8; i++) {
            flag = HuffmanTree[flag][bits[i] == '0' ? _left : _right]; //��bit��ȡ��0�����������ң���������������
            if (HuffmanTree[flag][_left] == -1 && HuffmanTree[flag][_right] == -1) {   //�ж��Ƿ���Ҷ�ӽڵ㣬������д��Ҷ�ӽڵ���
                if (fwrite( & flag, 1, 1, writer) <= 0)
                    return false;
                data++;     //�ֽڼ�����+1
                flag = top;   //����flag
            }
            if (data >= FILEsize) {   //�ж��Ƿ񵽴��ļ�β
                cout << "Finish. Check '" << FILEname << "'." << endl;
                return true;
            }
        }
    }
    return false;
}



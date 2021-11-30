#include"HuffmanCoding.h"

using namespace std;

Document::Document(string filePath, string fileName) {
    FILEpath = filePath.c_str();
    FILEname = fileName.c_str();
    reader = writer = NULL;
    reader = fopen(FILEpath, "rb");
    writer = fopen(FILEname, "wb");
    //
    top = TOP_NUM;
    FILEsize = buff_p = buff_t = bitSeq_p = 0;
    memset(buff, 0, sizeof(buff));
    memset(bitSeq, 0, sizeof(bitSeq));
    //
    for (int i = 0; i < 512; i++) {
        //�����������ʼ��
        HuffmanTree[i][_weigth] = 0;
        HuffmanTree[i][_left] = HuffmanTree[i][_right] = -1;
        HuffmanTree[i][_parent] = 256;
        if (i < 256)
            BytecodeArray[i] = 0;
    }
}

Document::~Document() {
    if (reader != NULL) fclose(reader);
    if (writer != NULL) fclose(writer);
}

bool Document::Init(int mode) {
    ///��ʼ��
    //�����ģʽ�ж�
    if (!(mode == 0 || mode == 1)) return false;
    int _flag=1;
    if (mode == 0) {
        //����׼��
        if (ReadinSource() && HTreeInit() && HTreeCreate() && WordsCreate())
            _flag=0;
    } else if (mode == 1) {
        //����׼��
        if(ReadinCode())
            _flag=0;
    }
    ///���ؽ��
    if(_flag==0){
        cout<<"Initial success. Going to encode."<<endl;
        return true;
    }else{
        cout<<"Initial failed. Check your file."<<endl;
        return false;
    }
    
}

bool Document::HTreeInit() {
    ///����������ʼ��
    HuffmanTree[256][_parent] = -1;
    int flag = 1;
    for (int i = 0; i < 256; i++) {
        if (BytecodeArray[i] != 0) {
            //���г�ʼ�ڵ����
            Nodes.push(Node(i, BytecodeArray[i], 256));
            HuffmanTree[i][_weigth] = BytecodeArray[i];
        }
    }
    return true;
}

bool Document::Select(int & node1, int & node2) {
    ///ѡ��Ȩֵ��С�������ڵ�
    node1 = node2 = 0;
    if (!Nodes.empty()) {
        node1 = Nodes.top().val;
        Nodes.pop();
    }
    if (!Nodes.empty()) {
        node2 = Nodes.top().val;
        Nodes.pop();
    }
    return true;
}

bool Document::HTreeCreate() {
    ///������������
    int flag = TOP_NUM;
    if (Nodes.empty()) return false;
    while (!Nodes.empty()) {
        int node1, node2;
        //ѡ��Ȩֵ��С�������ڵ�
        Select(node1, node2);
        //�����½ڵ�
        long long new_weight = HuffmanTree[node1][_weigth] + HuffmanTree[node2][_weigth];
        HuffmanTree[flag][_weigth] = new_weight;
        HuffmanTree[node1][_parent] = HuffmanTree[node2][_parent] = flag;
        HuffmanTree[flag][_left] = node1;
        HuffmanTree[flag][_right] = node2;
        if (!Nodes.empty()) {
            //�½ڵ����
            Nodes.push(Node(flag, new_weight, 256));
            top = flag;
            flag++;
        }
    }
    //��¼�ļ���С��/�ֽڣ�
    FILEsize = HuffmanTree[++top][_weigth];
    return true;
}

bool Document::WordsCreate() {
    ///��¼�ַ��Ĺ���������
    for (int i = 0; i < 256; i++) {
        if (BytecodeArray[i] > 0) {
            int cur = i;
            //��Ҷ�ӽڵ���������
            int pre = HuffmanTree[cur][_parent];
            string code = "";
            while (pre != 256) {
                code = HuffmanTree[pre][_left] == cur ? ('0' + code) : ('1' + code);
                cur = pre;
                pre = HuffmanTree[pre][_parent];
            }
            Words[i] = code;
        }
    }
    return true;
}

void Document::checkTree() {
    ///����������������Ҷ�ӽڵ��Ӧ�ַ�����
    for (int i = 0; i < 512; i++) {
        cout << i << " " <<
            HuffmanTree[i][_weigth] << " " <<
            HuffmanTree[i][_left] << " " <<
            HuffmanTree[i][_right] << " " <<
            HuffmanTree[i][_parent] << " " <<
            (i < 256 ? Words[i] : "") << endl;
    }
    cout << "top: " << top << endl;
    cout << "File Size: " << FILEsize << endl;
    cout << "Done." << endl;
}

int Document::toInt(char * bit) {
    //������תʮ����
    int out = 0;
    int len = strlen(bit);
    for (int i = 0; i < len; i++) {
        out += (bit[i] - 0x30) * pow(2, len - 1 - i);
    }
    return out;
}

void Document::toBinary(char * binary, int num) {
    //ʮ����ת������
    int dir = 0;
    int len = strlen(binary);
    while (num != 0) {
        binary[dir++] = (num % 2 == 1) ? '1' : '0';
        num /= 2;
    }
    for (int i = 0; i < len / 2; i++) {
        char temp = binary[i];
        binary[i] = binary[len - 1 - i];
        binary[len - 1 - i] = temp;
    }
}
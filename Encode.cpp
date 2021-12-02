#include"HuffmanCoding.h"

//编码过程
bool Document::Encode() {
    fseek(reader, 0, 0);
    fseek(writer, 0, 0);
    if (!reader || !writer)
        return false;
    char FileSizeBit[65];
    memset(FileSizeBit,'0',sizeof(FileSizeBit));
    FileSizeBit[64]='\0';
    toBinary(FileSizeBit,FILEsize);
    for(int j=56;j>=0;j-=8){
        for(int i=0;i<8;i++){
            fprintf(writer,"%c",FileSizeBit[i+j]);
        }
        fprintf(writer," ");
    }
    //fprintf(writer,"%s ",FileSizeBit);
    //fwrite( & FILEsize, 8, 1, writer);
    enCodingTree(top);  //写入树结构编码
    ///
    int buffer = 0;
    char bitStr[9] = "00000000";
    int indic = 0;
    while (!feof(reader)) {
        if (fread( & buffer, 1, 1, reader) > 0) {
            const char * str = Words[buffer].c_str();
            for (int i = 0; i < strlen(str); i++) {
                bitStr[indic++] = str[i];
                if (indic == 8) { //按8bit为一单位输出
                    //int byte = toInt(bitStr);
                    fwrite( & bitStr, 8, 1, writer);
                    strcpy(bitStr, "00000000");
                    indic = 0;
                    fprintf(writer," ");
                }
            }
        }
    }
    if (indic != 0) {  //最后一个字节不满8位则以0补足
        //int byte = toInt(bitStr);
        if (fwrite( & bitStr, 8, 1, writer) <= 0) return false;
    }
    cout << "Finish. Check '" << FILEname << "'." << endl;
    cout<<FILEsize<<endl;
    return true;
}

//对哈夫曼树进行编码
bool Document::enCodingTree(int top) {
    searchTree(top);
    //
    char _buff_t[9]="00000000";
    toBinary(_buff_t,(++buff_t));
    fprintf(writer,"%s ",_buff_t);
    //fwrite( & (++buff_t), 1, 1, writer); //写入首字节:树结构数组的大小
    //fprintf(writer,"%s",buff);
    for(int i=0;i<buff_t;i++){
        char s[9]="00000000";
        toBinary(s,(int)buff[i]);
        fprintf(writer,"%s ",s);
    }
    //fwrite(buff, buff_t, 1, writer); //写入buff数组:存储树结构的
    for(int i=0;i<bitSeq_p;i++){
        char numBit[9]="00000000";
        toBinary(numBit,(int)bitSeq[i]);
        fwrite( & numBit, 8, 1, writer);
        fprintf(writer," ");
    }
    //fwrite(bitSeq, bitSeq_p, 1, writer); //写入bitseq数组:按照DFS序,依次存储权值从大到小的字节叶子
    return true;
};

//递归的DFS哈夫曼树,进行编码
void Document::searchTree(int now) {
    bool Cflag = (HuffmanTree[now][_left] == -1); //判断是否有孩子
    buff[buff_t] |= ((!Cflag) << buff_p--);
    //buff[buff_t]+='0';
    /*
        1.大端法，从左向右依次记录
        2.如果当前节点now有孩子，则Cflag为0 取反后将当前位置位1
        
        e.g:若buff_p为 4 , Cflag为0 首先1 << 4 得到b(0001 0000)
            若当前buff[buff_t] 为 0000 0011 ,进行|操作后为 0001 0011.
            完成记录操作;
    */
    if (buff_p == -1) buff_t++, buff_p = 7; //当写满一个字节后,buff_t+1,存储到下一个buff
    if (Cflag) {
        bitSeq[bitSeq_p++] = now;
        return;
    } //如果是字节叶子,则存储当前节点的字节并返回

    searchTree(HuffmanTree[now][_left]);
    searchTree(HuffmanTree[now][_right]);
}


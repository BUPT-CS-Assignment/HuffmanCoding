#include "HuffmanCoding.h"


void reCodingMethod::searchTree(long long HuffmanTree[][4] , int now) {
    bool Cflag = (HuffmanTree[now][_left] == -1);
    buff[buff_t] |= ((!Cflag) << buff_p++);
    //printf("T: %d : %.2x : %d -- %d\n" ,buff_t , buff[buff_t], now , Cflag);
    if(buff_p == 8) buff_t++ , buff_p = 0;
    if(Cflag) bitSeq[bitSeq_p++] = now;
    else    searchTree( HuffmanTree , HuffmanTree[now][_left]),
            searchTree( HuffmanTree , HuffmanTree[now][_right]);
}

bool reCodingMethod::enCodingTree(FILE **fp_h , long long HuffmanTree[][4] , const int top ) {
    FILE *fp = *fp_h;
    searchTree(HuffmanTree , top);buff_t++;
    fwrite(&buff_t , 1 , 1 ,fp);
    fwrite(buff , buff_t , 1 ,fp);
    fwrite(bitSeq , bitSeq_p , 1 ,fp);

    return true;
};

bool reCodingMethod::buildTree(FILE **fp ,long long HuffmanTree[][4] , int &now){
    if(buff_p == 8) {buff_t++,buff_p = 0;}
    unsigned char t;    int _now = now;
    bool Cflag = (buff[buff_t] & (1 << buff_p++));
    
    if(!Cflag) {now--; return true;}
    else {
        HuffmanTree[_now][_left] = ++now;
        if(buildTree(fp , HuffmanTree , now )) {
            fread(&t , 1 , 1 , *fp);
            HuffmanTree[_now][_left] = t;            
        }
        HuffmanTree[_now][_right] = ++now;
        if( buildTree(fp , HuffmanTree , now )) {
            fread(&t , 1 , 1 , *fp);
            HuffmanTree[_now][_right] = t;
        }
    } 
    return false;
};
int reCodingMethod::deCodingTree(FILE **fp_h , long long HuffmanTree[][4] ) {
    FILE *fp = *fp_h;
    unsigned char head_t = 0;
    fread(&head_t, 1 , 1 ,fp);
    fread(buff, 1 , head_t , fp);

    int top = 256;  buff_p = 0;
    buildTree(&fp , HuffmanTree , top);

 
    return 256;
}

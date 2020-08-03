#include "graphelement.h"
//#include "diagramitem.h"
#include <QPainter>
#include <QPen>
#include <QtMath>
#include<QMouseEvent>
#include"idpool.h"

//int GraphElement::maxid = 0;



GraphElement::GraphElement()
{
//    Id = ++maxid;
     this->setId();
}
void GraphElement::setId(){
    for(int i=0;i<200;i++){
        if(k1[i]==0){
            this->Id=i+1;
            k1[i]=1;
            break;
            //为0的时候表示ID未被占用，为1的时候表示已经被占用
        }
    }
}


int GraphElement::GetID(){
    return this->Id;

}

QString GraphElement::getIdNum(int num)
{
    if(num == 0)
        return "0x0";

    QString res;
    QString hex[16] = {"0", "1", "2", "3", "4", "5", "6", "7",
                      "8", "9", "a", "b", "c", "d", "e", "f"};

    unsigned int num2 = num;//无论正负，全部转换成无符号整型
    while(num2)
    {
        res = hex[num2 % 16] + res;//取余即是最低位
        num2 /= 16;
    }
    return "0x"+res;
}//得到ID的16进制表示的字符串
void GraphElement::deleteID()
{
   k1[this->Id-1]=0;
   return ;
}

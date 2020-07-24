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

#include "graphelement.h"
//#include "diagramitem.h"
#include <QPainter>
#include <QPen>
#include <QtMath>
#include<QMouseEvent>
#include"idpool.h"
extern int k1[100][2];
extern int k2[100][2];
//extern int k1=0;
//int GraphElement::xy[50][50]={0};


GraphElement::GraphElement()
{
    for(int i=0;i<100;i++){
        k1[i][0]=i+1;
        k1[i][1]=0;
    }
}
void GraphElement::setId(){
    for(int i=0;i<100;i++){
        if(k1[i][1]==0){
            this->Id=i+1;
            k1[i][1]=0;
        }
    }
}


int GraphElement::GetID(){
    return this->Id;

}

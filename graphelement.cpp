#include "graphelement.h"
#include "diagramitem.h"

#include <QPainter>
#include <QPen>
#include <QtMath>
#include<QMouseEvent>
GraphElement::GraphElement()
{

}
void GraphElement::setId(){
    this->Id=k++;
}

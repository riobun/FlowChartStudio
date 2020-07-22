#include<textitem.h>
#include<textevent.h>
    /*TextItem ::TextItem(){}
    void  TextItem ::keyPressEvent(QKeyEvent* event) override{}
    void  TextItem ::mousePressEvent(QGraphicsSceneMouseEvent* event)override{}
    void  TextItem ::mouseMoveEvent(QGraphicsSceneMouseEvent* event)override{}
    void  TextItem ::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)override{}
    void  TextItem ::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)override{}
    void  TextItem ::keyReleaseEvent(QKeyEvent* event)override{}
    void  TextItem ::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)override{}*/
void TextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    NodeEvents::mousePressEvent(text, event);
}

void TextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    NodeEvents::mouseReleaseEvent(text, event);
}

void TextItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    NodeEvents::contextMenuEvent(text, event);
}

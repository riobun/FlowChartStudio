#ifndef TEXTITEM_H
#define TEXTITEM_H
#include"QGraphicsItem"
#include<QFont>
class Text;

/*
 鼠标左键按住拖动
 shift+鼠标左键按住调整大小
 */
class TextItem:public QObject,public QGraphicsPolygonItem
{
Q_OBJECT
public:
    explicit TextItem(QObject *parent = nullptr):QObject(parent) {};
    TextItem(Text* text):text(text){};
    Text* GetText() {return text;}
    void SetSelected(bool b)
    {
        isSelected=b;

        setSelected(b);
    }


signals:
    void Selected(Text*t,bool b);
    void NewLocation(Text*t,QPointF oldlocation);
    void NewFont(Text*t,QFont oldfont);
    void NewColor(Text* t,QColor oldcolor);
    void NewContent(Text* t,QString oldcontent);
protected:

    void mousePressEvent(QGraphicsSceneMouseEvent* event)override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event)override;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event)override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    bool isSelected=false;
    bool isFocus=false;
    bool isMoved=false;
    QPointF lastlocation;
    QFont lastfont;
    QColor lastcolor;
    QString lastcontent;
    Text* text=nullptr;

    void dialog();
};
#endif // TEXTITEM_H

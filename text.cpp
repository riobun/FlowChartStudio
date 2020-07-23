

#include"text.h"

#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <math.h>
#include <QMenu>
#include<QInputDialog>
#include<QLineEdit>
#include "changeelementaction.h"
#include "mainwindow.h"

Text::Text(QPointF primary_location,QGraphicsItem* parent ): QGraphicsTextItem(parent) {
    location = primary_location;
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
}
/*Text::Text(QPointF position1, QPointF position2,QGraphicsItem* parent ): QGraphicsRectItem(parent)  {//两个鼠标位置表示对角线两个顶点
    location = (position1 + position2) / 2;
    if ((position1.x() - position2.x()) > 0) {
        width = position1.x() - position2.x();
    }
    else {
        width = position2.x() - position1.x();
    }
    if ((position1.y() - position2.y()) > 0) {
        height = position1.y() - position2.y();
    }
    else {
        height = position2.y() - position1.y();
    }
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
}*/

void Text::build_text(QColor c, QFont f) {//创建文本框
   /* setRect(location.x()-width/2,location.y()-height/2,width,height);
    QBrush brush = this->brush();
    brush.setColor(QColor(0x00, 0xff, 0x00, 0x00));//透明
    setBrush(brush);
    setVisible(true);

     QPen pen = this->pen();
    pen.setColor(QColor(0x00, 0xff, 0x00, 0x00));
    setPen(pen);*/


    font = f;
    color = c;
    setFont(font);
    setDefaultTextColor(c);
    QPointF p=location;
    setPos(p);

}
void Text::putup_text(QGraphicsScene* scene) {
    scene->addItem(this);
}

Text::~Text() {


}


void Text::delete_text(QGraphicsScene* scene) {
    scene->removeItem(this);
    //在存储文件中删除

}

void Text::delete_char(int begin, int end) {

    int n = end - begin + 1;
    content.remove(begin, n);
    setPlainText(content);
}

void Text::add_char(int position, QString c) {

    content.insert(position, c);
    setPlainText(content);
}


void Text::reset_font(QFont new_font) {
    font = new_font;
    setFont(font);
}

/*Text::Text(Text old_t, QPointF primary_location, double primary_width, double primary_height,QGraphicsItem* parent ): QGraphicsRectItem(parent)  {
    location = primary_location;
    width = primary_width;
    height = primary_height;
    content = old_t.get_text_content();
    font = old_t.get_text_fond();
    color = old_t.get_text_color();
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
}*/

void Text::move_text(QPointF new_location) {
    location = new_location;
    setPos(location);
}

void Text::reset_color(QColor new_color) {
    color = new_color;
    setDefaultTextColor(color);
}

/*void Text::resize_text(double d_width, double d_height) {
    width += d_width;
    height += d_height;
    setRect(location.x() - width / 2, location.y() - height / 2, width, height);
}*/

QFont Text::get_text_fond() {
    return font;
}

QString Text::get_text_content() {
    return content;
}

QPointF Text::get_text_location() {
    return location;
}

QColor Text::get_text_color() {
    return color;
}
Text* Text::get_item() {
    return this;
}






void Text::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        setSelected(true);
        if (event->modifiers() == Qt::ShiftModifier) {
            qDebug() << "Custom item left clicked with shift key.";
            // 选中 item
            setSelected(true);
        }
        else if (event->modifiers() == Qt::AltModifier) {
           qDebug() << "Custom item left clicked with alt key.";
            // 重置 item 大小
            /*double radius = boundingRect().width() / 2.0;
            QPointF topLeft = boundingRect().topLeft();
            location = QPointF(topLeft.x() + pos().x() + radius, topLeft.y() + pos().y() + radius);
            QPointF pos = event->scenePos();
            qDebug() << boundingRect() << radius << this->pos() << pos << event->pos();
            double dist = sqrt(pow(m_centerPointF.x() - pos.x(), 2) + pow(m_centerPointF.y() - pos.y(), 2));
                        if (dist / radius > 0.8) {
                            qDebug() << dist << radius << dist / radius;
                            m_bResizing = true;
                        }
                        else {
                            m_bResizing = false;
                        }*/
             }
        else {
            qDebug() << "Custom item left clicked.";
            QGraphicsItem::mousePressEvent(event);
            event->accept();
        }
    }
    else if (event->button() == Qt::RightButton) {
        qDebug() << "Custom item right clicked.";
        event->ignore();

        QMenu menu;
        auto deleteAction = menu.addAction("删除");
        auto editAction = menu.addAction("编辑");
        deleteAction->setShortcut(QKeySequence::Delete);
        auto selectedAction = menu.exec(event->screenPos());
        if (selectedAction == deleteAction)
        {
            auto action = new ChangeElementAction(this, ElementShape::Text, false);
            action->Do();
        }else if(selectedAction == editAction){
            QString dlgTitle="文本框对话框";
            QString txtLable="请输入文本框中的文字";
            QString defaultInput =content;
            QLineEdit ::EchoMode echoMode=QLineEdit::Normal;
            bool ok=false;
            QString t=QInputDialog::getText(NULL,dlgTitle,txtLable,echoMode,defaultInput,&ok);
            if(ok&&!t.isEmpty()){
                change_content(t);
            }
        }



    }
}

void Text::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if ((event->modifiers() == Qt::AltModifier) && m_bResizing) {
       /* QPointF pos = event->scenePos();
        if ((location.x() - pos.x()) > 0) {
            width = (location.x() - pos.x())*2;
        }
        else {
            width = (pos.x() - location.x())*2;
        }
        if ((location.y() - pos.y()) > 0) {
            height = (location.y() - pos.y())*2;
        }
        else {
            height = (pos.y() - location.y())*2;
        }
        setRect(location.x() - width / 2, location.y() - height / 2, width, height);
        QPointF p=location;
        p.setX(p.x() - width/ 2);
        p.setY(p.y()-height/2);
        text->setPos(p);*/
    }
    else if (event->modifiers() != Qt::AltModifier) {
        qDebug() << "Custom item moved.";
        QGraphicsItem::mouseMoveEvent(event);
        location=pos();

        setPos(location);
        qDebug() << "moved" << pos();
    }
}

void Text::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if ((event->modifiers() == Qt::AltModifier) && m_bResizing) {
        m_bResizing = false;
    }
    else {
        QGraphicsItem::mouseReleaseEvent(event);
    }
}

int Text::type() const
{
    return UserType + 1;
}
 void Text::change_content(QString new_c){
     content=new_c;
     setPlainText(content);
 }
void Text::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event){
    if(textInteractionFlags()==Qt::NoTextInteraction)
        setTextInteractionFlags(Qt::TextEditorInteraction);
    QGraphicsTextItem::mouseDoubleClickEvent(event);

}

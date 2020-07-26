

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
#include<QFontDialog>
#include<QColorDialog>

Text::Text(QPointF primary_location,QGraphicsItem* parent ): QGraphicsTextItem(parent) {
    location = primary_location;
    setZValue(120);
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    content.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
    //setTextInteractionFlags(Qt::TextEditable);
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

void Text::build_text(QColor c, QFont f) {

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
    delete shape;

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
    emit shape->NewFont(this,font);
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
    emit shape->NewColor(this,color);
    color = new_color;
    setDefaultTextColor(color);

}

/*void Text::resize_text(double d_width, double d_height) {
    width += d_width;
    height += d_height;
    setRect(location.x() - width / 2, location.y() - height / 2, width, height);
}*/
void Text::change_content(QString new_c){
    emit shape->NewContent(this,content);
    content=new_c;
    setPlainText(content);

}
QFont Text::get_text_font() {
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
TextItem* Text::get_item() {
    return shape;
}



void Text::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
        qDebug() << "Custom item moved.";
        QGraphicsItem::mouseMoveEvent(event);
        move_text(pos());
        qDebug() << "moved" << pos();

}

void Text::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event){
    if(textInteractionFlags()==Qt::NoTextInteraction){
       // setTextInteractionFlags(Qt::TextEditorInteraction);
        QString dlgTitle="文本框对话框";
        QString txtLable="请输入文本框中的文字";
        QString defaultInput =content;
        bool ok=false;
        QString t=QInputDialog::getMultiLineText(NULL,dlgTitle,txtLable,defaultInput,&ok);
        if(ok&&!t.isEmpty()){
            change_content(t);
        }


    }
    QGraphicsTextItem::mouseDoubleClickEvent(event);

}

void Text::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
    QMenu menu;
    auto deleteAction = menu.addAction("删除");
    auto editAction = menu.addAction("编辑");
    auto fontAction = menu.addAction("修改字体");
    auto colorAction = menu.addAction("修改颜色");

    deleteAction->setShortcut(QKeySequence::Delete);
    auto selectedAction = menu.exec(event->screenPos());

    if (selectedAction == deleteAction)
    {
        auto action = new ChangeElementAction(this, ElementShape::Text, false);
        action->Do();
    }
    else if(selectedAction == editAction){
        QString dlgTitle="文本框对话框";
        QString txtLable="请输入文本框中的文字";
        QString defaultInput =content;
        bool ok=false;
         QString t=QInputDialog::getMultiLineText(NULL,dlgTitle,txtLable,defaultInput,&ok);
        if(ok&&!t.isEmpty()){
            change_content(t);
        }
    }
    else if(selectedAction == fontAction){
       //QFont iniFont=ui->plainTextEdit->font();

       bool ok=false;
       QFont f=QFontDialog::getFont(&ok,font);
       if(ok){
           reset_font(f);
       }

    }
    else if(selectedAction == colorAction){

        QColor c=QColorDialog::getColor(color,nullptr,"选择颜色");
        if(c.isValid()){
            reset_color(c);
        }

    }
}


void Text::mousePressEvent(QGraphicsSceneMouseEvent* event){
    QGraphicsTextItem::mousePressEvent(event);
    shape->Selected(this,true);
}



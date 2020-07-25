#include"textitem.h"
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

void TextItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

        isFocus=true;
        lastlocation=text->get_text_location();
        QGraphicsItem::mousePressEvent(event);

}

void TextItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
        qDebug() << "Custom item moved.";
        QGraphicsItem::mouseMoveEvent(event);
        text->move_text(pos());
        qDebug() << "moved" << pos();
        isMoved=true;

}

void TextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
        QGraphicsItem::mouseReleaseEvent(event);
        if(isFocus){
            if(isMoved){
                emit NewLocation(text,lastlocation);
            }
        }


}


void TextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event){
    qDebug() << "Custom Double Click.";
       dialog();


}

void TextItem::dialog(){
    QString dlgTitle="文本框对话框";
    QString txtLable="请输入文本框中的文字";
    QString defaultInput =text->get_text_content();
    bool ok=false;
     QString t=QInputDialog::getMultiLineText(NULL,dlgTitle,txtLable,defaultInput,&ok);
    if(ok&&!t.isEmpty()){

        lastcontent=text->get_text_content();
        text->change_content(t);
        emit NewContent(text,lastcontent);
    }
}
void TextItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
    QMenu menu;
    auto deleteAction = menu.addAction("删除");
    auto editAction = menu.addAction("编辑");
    auto fontAction = menu.addAction("修改字体");
    auto colorAction = menu.addAction("修改颜色");

    deleteAction->setShortcut(QKeySequence::Delete);
    auto selectedAction = menu.exec(event->screenPos());

    if (selectedAction == deleteAction)
    {
        auto action = new ChangeElementAction(text, ElementShape::Text, false);
        action->Do();
    }
    else if(selectedAction == editAction){
            dialog();

    }
    else if(selectedAction == fontAction){
       //QFont iniFont=ui->plainTextEdit->font();

       bool ok=false;
       QFont f=QFontDialog::getFont(&ok,text->get_text_font());
       if(ok){
           lastfont=text->get_text_font();
           emit NewFont(text,lastfont);
           text->reset_font(f);
       }

    }
    else if(selectedAction == colorAction){

        QColor c=QColorDialog::getColor(text->get_text_color(),nullptr,"选择颜色");
        if(c.isValid()){
            lastcolor=text->get_text_color();
            emit NewColor(text,lastcolor);
            text->reset_color(c);
        }

    }
}


QVariant TextItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
    {
        SetSelected(QGraphicsItem::isSelected());
        emit Selected(text, QGraphicsItem::isSelected());
    }
    return value;
}

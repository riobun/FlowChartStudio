#ifndef TEXT_H
#define TEXT_H


#include <QMainWindow>
#include<QString>
#include<QFont>
#include<QGraphicsRectItem>
#include<QGraphicsScene>
#include <QGraphicsTextItem>
#include<QColor>

class Text {
public:
    Text(QPointF primary_location, double primary_width, double primary_height);//由节点生成
    Text(QPointF position1, QPointF position2);//由图生成（鼠标位置决定大小）
    ~Text();
    void build_text(QGraphicsScene* scene,QColor c=Qt::black, QFont f=QFont());//初始化并在界面中显示，注：创建文本框时一定要调用
    void delete_text(QGraphicsScene* scene);
    void delete_char(int begin, int end);//参数：待删除字符位置
    void add_char(int position, QString str);//增加字符位置，增加的字符
    void reset_font(QFont new_font);//新字体
    void reset_color(QColor new_color);
    Text(Text old_t, QPointF primary_location, double primary_width, double primary_height);//附着于新的节点
    void move_text(QPointF new_location);//参数：新的坐标位置
    void resize_text(double d_width, double d_height);//参数：表示宽和高的位移
    QFont get_text_fond();
    QString get_text_content();
    QPointF get_text_location();
    QColor get_text_color();

private:
    QPointF location;
    QString content;
    QFont font;
    double width, height;
    QColor color;
    QGraphicsRectItem* item = new QGraphicsRectItem();
    QGraphicsTextItem* text = new QGraphicsTextItem(item);
};



#endif 

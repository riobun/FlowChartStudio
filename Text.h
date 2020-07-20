#ifndef TEXT_H
#define TEXT_H

#include <QMainWindow>
#include<QString>


class Text{
public:

    Text(QPoint primary_location,double primary_width,double primary_hight);//参数：节点或鼠标位置，节点大小
    void delete_text();
    void delete_char(int position);//参数：待删除字符位置
    void change_char(int position,char c);//待替换字符位置，新字符
    void add_char(int position,char c);//增加字符位置，增加的字符
    void revise_font(QFont new_font);//新字体
    Text& reset_text(QPoint primary_location,double primary_width,double primary_hight);//附着于新的节点
    void move_text(QPoint new_location);//参数：新的坐标位置

    QFont get_text_fond();
    QString get_test_content();
    QPoint get_text_location();

private:
    QPoint location;
    QString content;
    QFont font;
    double width,hight;
};



#endif 

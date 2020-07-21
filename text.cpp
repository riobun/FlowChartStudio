#include"text.h"



Text::Text(QPoint primary_location,double primary_width,double primary_height) {
    location = primary_location;
    width = primary_width;
    height = primary_height;
    
}
Text::Text(QPointF position1, QPointF position2) {//两个鼠标位置表示对角线两个顶点
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
}

void Text::build_text(QGraphicsScene* scene, QColor c, QFont f) {//创建文本框
    item->setRect(location.x()-width/2,location.y()-height/2,width,height);
    QBrush brush = item->brush();
    brush.setColor(QColor(0x00, 0xff, 0x00, 0x00));//透明
    item->setBrush(brush);
    item->setVisible(true);
    scene->addItem(item);

    QRectF rect = text->boundingRect();
    font = f;
    color = c;
    text->setFont(font);
    text->setDefaultTextColor(c);
    QPointF p=location;
    p.setX(p.x() - rect.width() / 2);
    text->setPos(p);

}

Text::~Text() {
    delete text;
    delete item;
}


void Text::delete_text() {
    item->setVisible(false);
    //在存储文件中删除
    
}

void Text::delete_char(int begin, int end) {
    
    int n = end - begin + 1;
    content.remove(begin, n);
    text->setPlainText(content);
}

void Text::add_char(int position, QString c) {
   
    content.insert(position, c);
    text->setPlainText(content);
}


void Text::reset_font(QFont new_font) {
    font = new_font;
    text->setFont(font);
}

Text::Text(Text old_t, QPointF primary_location, double primary_width, double primary_height) {
    location = primary_location;
    width = primary_width;
    height = primary_height;
    content = old_t.get_text_content();
    font = old_t.get_text_fond();
    color = old_t.get_text_color();
}

void Text::move_text(QPointF new_location) {
    location = new_location;
    item->setX(location.x() - width / 2);
    item->setY(location.y() - height / 2);
}

void Text::reset_color(QColor new_color) {
    color = new_color;
    text->setDefaultTextColor(color);
}


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


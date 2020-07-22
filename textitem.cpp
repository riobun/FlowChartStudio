#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include"textitem.h"

// 自定义 Item
TextItem::TextItem(QGraphicsItem* parent)
    : QGraphicsRectItem(parent)
{

    // 可选择、可移动
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
}

void TextItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        if (event->modifiers() == Qt::ShiftModifier) {
            qDebug() << "Custom item left clicked with shift key.";
            // 选中 item
            setSelected(true);
        }
        else if (event->modifiers() == Qt::AltModifier) {
            qDebug() << "Custom item left clicked with alt key.";
            // 重置 item 大小
            double radius = boundingRect().width() / 2.0;
            QPointF topLeft = boundingRect().topLeft();
            m_centerPointF = QPointF(topLeft.x() + pos().x() + radius, topLeft.y() + pos().y() + radius);
            QPointF pos = event->scenePos();
            qDebug() << boundingRect() << radius << this->pos() << pos << event->pos();
            double dist = sqrt(pow(m_centerPointF.x() - pos.x(), 2) + pow(m_centerPointF.y() - pos.y(), 2));
            if (dist / radius > 0.8) {
                qDebug() << dist << radius << dist / radius;
                m_bResizing = true;
            }
            else {
                m_bResizing = false;
            }
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
    }
}

void TextItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if ((event->modifiers() == Qt::AltModifier) && m_bResizing) {
        QPointF pos = event->scenePos();
        double dist = sqrt(pow(m_centerPointF.x() - pos.x(), 2) + pow(m_centerPointF.y() - pos.y(), 2));
        setRect(m_centerPointF.x() - this->pos().x() - dist, m_centerPointF.y() - this->pos().y() - dist, dist * 2, dist * 2);
    }
    else if (event->modifiers() != Qt::AltModifier) {
        qDebug() << "Custom item moved.";
        QGraphicsItem::mouseMoveEvent(event);
        qDebug() << "moved" << pos();
    }
}

void TextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if ((event->modifiers() == Qt::AltModifier) && m_bResizing) {
        m_bResizing = false;
    }
    else {
        QGraphicsItem::mouseReleaseEvent(event);
    }
}

int TextItem::type() const
{
    return UserType + 1;
}


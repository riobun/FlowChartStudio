#include "navigationbutton.h"

#include <QPropertyAnimation>

NavigationButton::NavigationButton(QWidget *parent) :
    QPushButton(parent)
{
    animation = new QPropertyAnimation(this, "");
    animation->setDuration(100);
    connect(animation, &QPropertyAnimation::valueChanged, this, &NavigationButton::valueChanged);
}

void NavigationButton::enterEvent(QEvent* event)
{
    if (startPoint.x() == -1) startPoint = pos() + QPoint(150, 100);
    animation->stop();
    animation->setStartValue(height());
    animation->setEndValue(220);
    animation->start();
}

void NavigationButton::leaveEvent(QEvent* event)
{
    animation->stop();
    animation->setStartValue(height());
    animation->setEndValue(200);
    animation->start();
}

void NavigationButton::valueChanged(QVariant variant)
{
    auto height = variant.toInt();
    auto width = height * 3 / 2;
    setGeometry(QRect(startPoint - QPoint(width / 2, height / 2), QSize(width, height)));
    update();
}

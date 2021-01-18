#ifndef NAVIGATIONBUTTON_H
#define NAVIGATIONBUTTON_H

#include <QPushButton>
#include <QVariant>

class QPropertyAnimation;

class NavigationButton : public QPushButton
{
    Q_OBJECT
public:
    explicit NavigationButton(QWidget *parent = nullptr);

protected:
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;

private slots:
    void valueChanged(QVariant variant);

private:
    QPoint startPoint = QPoint(-1, -1);
    QPropertyAnimation* animation;
};

#endif // NAVIGATIONBUTTON_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QToolButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QGraphicsScene* scene() { return _scene; }
private slots:
    void on_addRectangleButton_clicked();

    void on_addDiamondButton_clicked();

    void on_addArrowButton_clicked();

    void textColorChanged();
    void textButtonTriggered();


private:
    Ui::MainWindow *ui;

    QGraphicsScene* _scene;

    QMenu *createColorMenu(const char *slot, QColor defaultColor);
    QIcon createColorToolButtonIcon(const QString &image, QColor color);
    QIcon createColorIcon(QColor color);

    QAction *textAction;
    QToolButton* fontColorToolBtn;
};
#endif // MAINWINDOW_H

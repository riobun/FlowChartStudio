#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

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

private:
    Ui::MainWindow *ui;

    QGraphicsScene* _scene;
};
#endif // MAINWINDOW_H

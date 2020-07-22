#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QToolButton>
#include <QVector>
#include "elementshape.h"
#include "action.h"
#include "node.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static MainWindow* instance() { return _instance; }
    QGraphicsScene* scene() { return _scene; }
    ElementShape nextAddedShape() const {return _nextAddedShape; }
    void setNextAddedShape(ElementShape shape) { _nextAddedShape = shape; }
    void Doing(Action* action) { undoStack.append(action); }
    void Discard(Action* action) { if (undoStack.last() == action) undoStack.removeLast(); }

    QVector<Node*> selectedNodes;

public slots:
    void Undo();
    void Redo();

private slots:
    void textColorChanged();
    void textButtonTriggered();

    void itemColorChanged();
    void fillButtonTriggered();

    void bdColorChanged();
    void bdButtonTriggered();

    void arrowColorChanged();
    void arrowColorButtonTriggered();

    void on_addRectangleButton_clicked();
    void on_addDiamondButton_clicked();
    void on_addArrowButton_clicked();
    void on_addTextButton_clicked();

private:
    Ui::MainWindow *ui;

    static MainWindow* _instance;

    QGraphicsScene* _scene;

    QMenu *createColorMenu(const char *slot, QColor defaultColor);
    QIcon createColorToolButtonIcon(const QString &image, QColor color);
    QIcon createColorIcon(QColor color);

    QAction *textAction;
    QAction *fillAction;
    QAction *bdAction;
    QAction *arrowColorAction;
    QToolButton* arrowColorToolBtn;
    QToolButton* bdColorToolBtn;
    QToolButton* fontColorToolBtn;
    QToolButton* fillColorToolBtn;

    ElementShape _nextAddedShape;
    int _selectedId;
    QVector<Action*> undoStack;
    QVector<Action*> redoStack;
};
#endif // MAINWINDOW_H

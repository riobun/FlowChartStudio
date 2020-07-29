#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QToolButton>
#include <QVector>
#include <QStandardItemModel>
#include "elementshape.h"
#include "action.h"
#include "node.h"
#include "graph.h"
#include "flowchartscene.h"


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
    QMap<int, Node*>* selectedNodes() { return &_selectedNodes; }
    QVector<Text*>* selectedTexts() { return &_selectedTexts; }
    QMap<int, Arrow*>* selectedArrows() { return &_selectedArrows; }

    QColor bdColor = Qt::black;
    QColor fillColor = Qt::white;
    QColor lineColor = Qt::black;
    Graph* graph = new Graph;
    Graph* cutGraph = new Graph;

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

    void removeSubTab(int index);

private:
    void clickbdBtn();
    void clickFillBtn();
    void clickLineBtn();
    void addNewTab(QStandardItem* currentItem);
    void addNewTab();

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
    QList<Action*> undoStack;
    QList<Action*> redoStack;
    QMap<int, Node*> _selectedNodes;
    QMap<int, Arrow*> _selectedArrows;
    QVector<Text*> _selectedTexts;
    QMap<QModelIndex,FlowChartScene* > scenes;

};
#endif // MAINWINDOW_H

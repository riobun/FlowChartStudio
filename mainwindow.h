#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QToolButton>
#include <QVector>
#include <QStandardItemModel>
#include <QFontComboBox>
#include "elementshape.h"
#include "action.h"
#include "node.h"
#include "graph.h"
#include "scene.h"
#include <QMap>
//*************************************************
#include <QMenu>
#include <QAction>
#include <QTextEdit>
//*********************************************

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ElementOperator;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static MainWindow* instance() { return _instance; }
    Scene* scene() { return _scene; }
    QList<QGraphicsScene*> open_scene(){return open_scenes;}
    ElementShape nextAddedShape() const {return _nextAddedShape; }
    void setNextAddedShape(ElementShape shape) { _nextAddedShape = shape; }
    void Doing(Action* action) { undoStack.append(action); }
    void Discard(Action* action) { if (undoStack.last() == action) undoStack.removeLast(); }
    QMap<int, Node*>* selectedNodes() { return &_selectedNodes; }
    QVector<Text*>* selectedTexts() { return &_selectedTexts; }
    QMap<int, Arrow*>* selectedArrows() { return &_selectedArrows; }
    void addNewTab();
    void addNewTab(QString name);
    int index_tab();
    Graph* graph();

    QColor bdColor = Qt::black;
    QColor fillColor = Qt::white;
    QColor lineColor = Qt::black;
    QColor textColor = Qt::black;
    int lineType = 1;
    QString fontFamily = "宋体";
    int fontSize = 12;
    Graph* cutGraph = new Graph;

public slots:
    void Undo();
    void Redo();
    void Cut();
    void Copy();
    void Paste();
    void SelectAll();
    void deleteElement();

    void lineTypeChanged(int index);
    void changeFontFamily(QFont font);
    void changeFontSize(QString sizeString);

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
    void modifyTabText(QStandardItem* item);

    void on_addSubgraghButton_clicked();

    void on_addFatherPortButton_clicked();

    void on_addSonPortButton_clicked();


//*****************************************************
    void on_action1_triggered();

    void on_action1_2_triggered();

    void on_action1_3_triggered();

    void on_action1_4_triggered();
    //*****************************************************
    void on_addInnerInputButton_clicked();

    void on_addInnerOutputButton_clicked();

private:
    void changeFrameColor(QColor color);
    void changeFillColor(QColor color);
    void changeLineColor(QColor color);
    void changeTextColor(QColor color);
    void changeFont(QFont font);
    void clickbdBtn();
    void clickFillBtn();
    void clickLineBtn();
    void clickTextColorButton();
    void addNewTab(QStandardItem* currentItem);


private:
    Ui::MainWindow *ui;
    int rename_index;

    static MainWindow* _instance;

    Scene* _scene;

    QList<QGraphicsScene*> open_scenes;
    QMenu *createColorMenu(const char *slot, QColor defaultColor);
    QIcon createColorToolButtonIcon(const QString &image, QColor color);
    QIcon createColorIcon(QColor color);
    //**********************************
    QTextEdit *textEdit;
      //***********************
    QAction *textAction;
    QAction *fillAction;
    QAction *bdAction;
    QAction *arrowColorAction;
    QFontComboBox* fontBtn;
    QComboBox* fontSizeCombo;
    QComboBox* bdSizeCombo;
    QComboBox* arrowSizeCombo;

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
    QMap<QModelIndex,Scene* > scenes;
    QMap<QGraphicsScene*, Graph*> graphs;

    QVector<QPair<int,QString>> index_name_subgraph;

private:
    ElementOperator* _elementOperator;
};
#endif // MAINWINDOW_H

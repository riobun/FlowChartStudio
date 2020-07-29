#include <QToolBar>
#include <QPushButton>
#include <QComboBox>
#include <QColorDialog>
#include <QFontComboBox>
#include <QFontDialog>
#include <QToolButton>
#include <QStandardItemModel>
#include <QIcon>
#include <QString>
#include <QTreeView>
#include <QVBoxLayout>
#include <QDebug>
#include <QList>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flowchartscene.h"
#include "editelementaction.h"
#include "groupaction.h"


MainWindow* MainWindow::_instance;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //侧边栏
    ui->addSubgraghButton->setIcon(QIcon(":/images/subGraph_new.png"));
    ui->addFatherPortButton->setIcon(QIcon(":/images/Right_new.png"));
    ui->addSonPortButton->setIcon(QIcon(":/images/Left_new.png"));

    //工具栏
    ui->toolBar->addWidget(ui->backBtn);
    ui->toolBar->addWidget(ui->copyBtn);
    ui->toolBar->addWidget(ui->pasteBtn);

    ui->toolBar->addSeparator();

    QFontComboBox* fontBtn = new QFontComboBox(this);
    ui->toolBar->addWidget(fontBtn);

    ui->toolBar->addSeparator();

    //字号
    QComboBox* fontSizeCombo = new QComboBox(this);
    fontSizeCombo->setEditable(true);
    for (int i = 6; i < 52; i = i + 2)
        fontSizeCombo->addItem(QString().setNum(i));
    QIntValidator *validator = new QIntValidator(2, 64, this);
    fontSizeCombo->setValidator(validator);
    ui->toolBar->addWidget(fontSizeCombo);

    ui->toolBar->addSeparator();

    ui->toolBar->addWidget(ui->boldBtn);
    ui->toolBar->addWidget(ui->italicBtn);
    ui->toolBar->addWidget(ui->underlineBtn);

    ui->toolBar->addSeparator();

    //字体颜色
    fontColorToolBtn = new QToolButton(this);
    fontColorToolBtn->setPopupMode(QToolButton::MenuButtonPopup);
    fontColorToolBtn->setMenu(createColorMenu(SLOT(textColorChanged()), Qt::black));
    textAction = fontColorToolBtn->menu()->defaultAction();
    fontColorToolBtn->setIcon(createColorToolButtonIcon(":/images/textpointer.png", Qt::black));
    fontColorToolBtn->setAutoFillBackground(true);
    ui->toolBar->addWidget(fontColorToolBtn);

    ui->toolBar->addSeparator();

    //填充颜色
    fillColorToolBtn = new QToolButton(this);
    fillColorToolBtn->setPopupMode(QToolButton::MenuButtonPopup);
    fillColorToolBtn->setMenu(createColorMenu(SLOT(itemColorChanged()), Qt::white));
    fillAction = fillColorToolBtn->menu()->defaultAction();
    fillColorToolBtn->setIcon(createColorToolButtonIcon(
                                     ":/images/floodfill.png", Qt::white));
    connect(fillColorToolBtn, &QAbstractButton::clicked, this, &MainWindow::clickFillBtn);

    ui->toolBar->addWidget(fillColorToolBtn);

    //边框颜色
    bdColorToolBtn = new QToolButton(this);
    bdColorToolBtn->setPopupMode(QToolButton::MenuButtonPopup);
    bdColorToolBtn->setMenu(createColorMenu(SLOT(bdColorChanged()), Qt::black));
    bdAction = bdColorToolBtn->menu()->defaultAction();
    bdColorToolBtn->setIcon(createColorToolButtonIcon(
                                     ":/images/bdcolor.png", Qt::black));
    connect(bdColorToolBtn, &QAbstractButton::clicked, this, &MainWindow::clickbdBtn);
    ui->toolBar->addWidget(bdColorToolBtn);

    //箭头颜色
    arrowColorToolBtn = new QToolButton(this);
    arrowColorToolBtn->setPopupMode(QToolButton::MenuButtonPopup);
    arrowColorToolBtn->setMenu(createColorMenu(SLOT(arrowColorChanged()), Qt::black));
    arrowColorAction = arrowColorToolBtn->menu()->defaultAction();
    arrowColorToolBtn->setIcon(createColorToolButtonIcon(
                                     ":/images/arrowcolor.png", Qt::black));
    connect(arrowColorToolBtn, &QAbstractButton::clicked, this, &MainWindow::clickLineBtn);
    ui->toolBar->addWidget(arrowColorToolBtn);

    ui->toolBar->addSeparator();

    ui->toolBar->addWidget(ui->arrowComboBox);
    ui->arrowComboBox->addItem("实线箭头");
    ui->arrowComboBox->addItem("虚线箭头");
    ui->arrowComboBox->addItem("点线箭头");

    //菜单栏信号
    //文本框
    connect(ui->action_fontColor,&QAction::triggered,[](){
        QColorDialog::getColor(QColor(Qt::black));
    });
    connect(ui->action_font,&QAction::triggered,[](){
        bool flag;
        QFontDialog::getFont(&flag,QFont("宋体",20));
    });
    //箭头
    connect(ui->action_arrowColor,&QAction::triggered,[](){
        QColorDialog::getColor(QColor(Qt::black));
    });
    //节点
    connect(ui->action_bgColor,&QAction::triggered,[](){
        QColorDialog::getColor(QColor(Qt::black));
    });
    connect(ui->action_bdColor,&QAction::triggered,[](){
        QColorDialog::getColor(QColor(Qt::black));
    });

    //项目树形结构
    QStandardItemModel* model = new QStandardItemModel(ui->treeView);
    ui->treeView->setModel(model);
    model->setHorizontalHeaderLabels(QStringList()<<"项目管理");
    QStandardItem* itemProject1 = new QStandardItem(QIcon(":/images/project.png"),"项目1");
    model->appendRow(itemProject1);
    QStandardItem* itemFileFolder1 = new QStandardItem(QIcon(":/images/filefolder.png"),tr("Folder1"));
    itemProject1->appendRow(itemFileFolder1);
    QStandardItem* itemFile1 = new QStandardItem(QIcon(":/images/file.png"),"文件1");
    itemFileFolder1->appendRow(itemFile1);
/*
    _scene = new FlowChartScene();
    ui->graphicsView->setScene(scene());
    _scene->setSceneRect(QRectF(QPointF(0.0f, 0.0f), ui->graphicsView->size()));
*/
    //页面选项卡设计
    ui->tabWidget->clear();
    ui->tabWidget->setTabsClosable(true);
    ui->tabWidget->usesScrollButtons();

    connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(removeSubTab(int)));
    QWidget *tabFile0 = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(ui->graphicsView);
    tabFile0->setLayout(layout);
    ui->tabWidget->addTab(tabFile0,QIcon(":/images/file.png"),"0");

    _instance = this;

    connect(ui->undoAction, SIGNAL(triggered()), this, SLOT(Undo()));
    connect(ui->redoAction, SIGNAL(triggered()), this, SLOT(Redo()));


    //项目树结构和页面选项卡的连接
    connect(ui->treeView,&QTreeView::clicked,[=](){

        QModelIndex currentIndex = ui->treeView->currentIndex();
        QStandardItem* currentItem = model->itemFromIndex(currentIndex);

        if(!currentItem->hasChildren())
        {
            int i;
            for(i=0;i<ui->tabWidget->count();i++){
                if(ui->tabWidget->tabText(i)==currentItem->text())
                    break;
            }
            if(i>=ui->tabWidget->count()){

               addNewTab(currentItem);
            }
        }
    });

//    connect(ui->treeView,&QTreeView::clicked,[=](){
//       qDebug()<<ui->treeView->currentIndex();
//    });

    //切换选项卡时scene的切换
    connect(ui->tabWidget,&QTabWidget::currentChanged,[=](){

        if(ui->tabWidget->count() != 0){
            QLayoutItem* item = ui->tabWidget->currentWidget()->layout()->itemAt(0);
            QGraphicsView* graphicView = qobject_cast<QGraphicsView*>(item->widget());

            _scene = graphicView->scene();
        }

    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

QMenu *MainWindow::createColorMenu(const char *slot, QColor defaultColor)
{
    QList<QColor> colors;
    colors << Qt::black << Qt::white << Qt::red << Qt::blue << Qt::yellow << Qt::green << Qt::cyan << Qt::gray;
    QStringList names;
    names << tr("黑色") << tr("白色") << tr("红色") << tr("蓝色")
          << tr("黄色") << tr("绿色") << tr("青色") << tr("灰色");

    QMenu *colorMenu = new QMenu(this);
    for (int i = 0; i < colors.count(); ++i) {
        QAction *action = new QAction(names.at(i), this);
        action->setData(colors.at(i));
        action->setIcon(createColorIcon(colors.at(i)));
        connect(action, SIGNAL(triggered()), this, slot);
        colorMenu->addAction(action);
        if (colors.at(i) == defaultColor)
            colorMenu->setDefaultAction(action);
    }
    return colorMenu;
}

QIcon MainWindow::createColorToolButtonIcon(const QString &imageFile, QColor color)
{
    QPixmap pixmap(50, 80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image(imageFile);
    // Draw icon centred horizontally on button.
    QRect target(4, 0, 42, 43);
    QRect source(0, 0, 42, 43);
    painter.fillRect(QRect(0, 60, 50, 80), color);
    painter.drawPixmap(target, image, source);

    return QIcon(pixmap);
}

QIcon MainWindow::createColorIcon(QColor color)
{
    QPixmap pixmap(20, 20);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 20, 20), color);

    return QIcon(pixmap);
}

void MainWindow::textColorChanged()
{
    textAction = qobject_cast<QAction *>(sender());
    fontColorToolBtn->setIcon(createColorToolButtonIcon(
                                     ":/images/textpointer.png",
                                     qvariant_cast<QColor>(textAction->data())));
    textButtonTriggered();
}

void MainWindow::textButtonTriggered()
{
//    scene->setTextColor(qvariant_cast<QColor>(textAction->data()));
}

void MainWindow::itemColorChanged()
{
    fillAction = qobject_cast<QAction *>(sender());
    fillColorToolBtn->setIcon(createColorToolButtonIcon(
                                     ":/images/floodfill.png",
                                     qvariant_cast<QColor>(fillAction->data())));
    fillButtonTriggered();
    auto color = qvariant_cast<QColor>(fillAction->data());
    fillColor = color;
    if (selectedNodes()->size() > 0)
    {
        clickFillBtn();
    }
}

void MainWindow::fillButtonTriggered()
{
    //scene->setItemColor(qvariant_cast<QColor>(fillAction->data()));
}

void MainWindow::bdColorChanged()
{
    bdAction = qobject_cast<QAction *>(sender());
    bdColorToolBtn->setIcon(createColorToolButtonIcon(
                                     ":/images/bdcolor.png",
                                     qvariant_cast<QColor>(bdAction->data())));
    bdButtonTriggered();
    auto color = qvariant_cast<QColor>(bdAction->data());
    bdColor = color;
    if (selectedNodes()->size() > 0)
    {
        clickbdBtn();
    }
}

void MainWindow::bdButtonTriggered()
{
    //scene->setBdColor(qvariant_cast<QColor>(bdAction->data()));
}

void MainWindow::arrowColorChanged()
{
    arrowColorAction = qobject_cast<QAction *>(sender());
    arrowColorToolBtn->setIcon(createColorToolButtonIcon(
                                     ":/images/arrowcolor.png",
                                     qvariant_cast<QColor>(arrowColorAction->data())));
    arrowColorButtonTriggered();
    lineColor = qvariant_cast<QColor>(arrowColorAction->data());
}

void MainWindow::arrowColorButtonTriggered()
{
    //scene->setBdColor(qvariant_cast<QColor>(bdAction->data()));
}


void MainWindow::on_addRectangleButton_clicked()
{
    _nextAddedShape = ElementShape::Rectangle;
}

void MainWindow::on_addDiamondButton_clicked()
{
    _nextAddedShape = ElementShape::Diamond;
}

void MainWindow::on_addArrowButton_clicked()
{
    _nextAddedShape = ElementShape::Arrow;
}

void MainWindow::on_addTextButton_clicked()
{
    _nextAddedShape = ElementShape::Text;
}

void MainWindow::Undo()
{
    if (undoStack.size() > 0)
    {
        auto action = undoStack.last();
        undoStack.removeLast();
        action->Undo();
        redoStack.append(action);
    }
}

void MainWindow::Redo()
{
    if (redoStack.size() > 0)
    {
        auto action = redoStack.last();
        redoStack.removeLast();
        action->Do();
        undoStack.append(action);
    }
}

void MainWindow::clickbdBtn()
{
    auto action = new GroupAction;
    foreach (auto node, *selectedNodes())
    {
        *action << new EditElementAction(node, ElementShape::Rectangle,
                                         ElementProperty::FrameColor,
                                         new QColor(node->GetFrameColor()),
                                         new QColor(bdColor));
    }
    action->Do();
}

void MainWindow::clickFillBtn()
{
    auto action = new GroupAction;
    foreach (auto node, *selectedNodes())
    {
        *action << new EditElementAction(node, ElementShape::Rectangle,
                                         ElementProperty::BackgroundColor,
                                         new QColor(node->GetBackgroundColor()),
                                         new QColor(fillColor));
    }
    action->Do();
}

void MainWindow::clickLineBtn()
{

}

void MainWindow::removeSubTab(int index){
    if(ui->tabWidget->count() == 1) {
        ui->tabWidget->removeTab(index);

        addNewTab();
    }
    else {
        ui->tabWidget->removeTab(index);
    }

}

void MainWindow::addNewTab(QStandardItem* currentItem){
    //创建新的VIEW和SCENE，并绑定
    FlowChartScene* scene = new FlowChartScene();
    QGraphicsView* graphicsView = new QGraphicsView();

    graphicsView->setScene(scene);

    //在tabWidget中加入 包含VIEW的布局的widget 并 切换tab
    QWidget *tabFile = new QWidget(this);
    QVBoxLayout *layout1 = new QVBoxLayout;
    layout1->addWidget(graphicsView);
    tabFile->setLayout(layout1);
    ui->tabWidget->addTab(tabFile,QIcon(":/images/file.png"),currentItem->text());
    ui->tabWidget->setCurrentWidget(tabFile);


    scene->setSceneRect(QRectF(QPointF(0.0f, 0.0f), graphicsView->size()));
}

void MainWindow::addNewTab(){
    //创建新的VIEW和SCENE，并绑定
    FlowChartScene* scene = new FlowChartScene();
    QGraphicsView* graphicsView = new QGraphicsView();

    graphicsView->setScene(scene);

    //在tabWidget中加入 包含VIEW的布局的widget 并 切换tab
    QWidget *tabFile = new QWidget(this);
    QVBoxLayout *layout1 = new QVBoxLayout;
    layout1->addWidget(graphicsView);
    tabFile->setLayout(layout1);
    ui->tabWidget->addTab(tabFile,QIcon(":/images/file.png"),"0");
    ui->tabWidget->setCurrentWidget(tabFile);


    scene->setSceneRect(QRectF(QPointF(0.0f, 0.0f), graphicsView->size()));
}

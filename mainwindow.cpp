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
#include <QTableWidget>
#include <QTableWidgetItem>
//**********************************************************
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QFileDevice>
#include <QTextStream>
#include <QtEvents> //************************************

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flowchartscene.h"
#include "editelementaction.h"
#include "groupaction.h"
#include "nodeevents.h"
#include "arrow.h"


MainWindow* MainWindow::_instance;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //*****************************************************
        textEdit = new QTextEdit(this);

        textEdit->setGeometry(QRect(150,120,700,600));
        textEdit->setHidden(true); //隐藏文本编辑
    //*****************************************************


    //状态栏
        ui->listWidget->addItem("提示信息1");
        ui->listWidget->addItem("提示信息2");
        ui->listWidget->addItem("提示信息3");
        ui->listWidget->addItem("提示信息4");
        ui->listWidget->addItem("提示信息5");




    //工具栏
    ui->toolBar->addWidget(ui->backBtn);
    ui->toolBar->addWidget(ui->copyBtn);
    ui->toolBar->addWidget(ui->pasteBtn);

    ui->toolBar->addSeparator();

    fontBtn = new QFontComboBox(this);
    connect(fontBtn, &QFontComboBox::currentFontChanged, this, &MainWindow::changeFontFamily);
    ui->toolBar->addWidget(fontBtn);

    ui->toolBar->addSeparator();

    //字号
    fontSizeCombo = new QComboBox(this);
    fontSizeCombo->setEditable(true);
    for (int i = 6; i < 52; i = i + 2)
        fontSizeCombo->addItem(QString().setNum(i));
    fontSizeCombo->setCurrentText("12");
    QIntValidator *validator = new QIntValidator(2, 64, this);
    fontSizeCombo->setValidator(validator);
    connect(fontSizeCombo, SIGNAL(activated(const QString&)), this, SLOT(changeFontSize(QString)));
    ui->toolBar->addWidget(fontSizeCombo);

    ui->toolBar->addSeparator();

    ui->toolBar->addWidget(ui->boldBtn);
    ui->toolBar->addWidget(ui->italicBtn);
    ui->toolBar->addWidget(ui->underlineBtn);

    //字体颜色
    fontColorToolBtn = new QToolButton(this);
    fontColorToolBtn->setPopupMode(QToolButton::MenuButtonPopup);
    fontColorToolBtn->setMenu(createColorMenu(SLOT(textColorChanged()), Qt::black));
    textAction = fontColorToolBtn->menu()->defaultAction();
    fontColorToolBtn->setIcon(createColorToolButtonIcon(":/images/textpointer.png", Qt::black));
    fontColorToolBtn->setAutoFillBackground(true);
    connect(fontColorToolBtn, &QAbstractButton::clicked, this, &MainWindow::clickTextColorButton);
    ui->toolBar->addWidget(fontColorToolBtn);

    //边框颜色
    bdColorToolBtn = new QToolButton(this);
    bdColorToolBtn->setPopupMode(QToolButton::MenuButtonPopup);
    bdColorToolBtn->setMenu(createColorMenu(SLOT(bdColorChanged()), Qt::black));
    bdAction = bdColorToolBtn->menu()->defaultAction();
    bdColorToolBtn->setIcon(createColorToolButtonIcon(
                                     ":/images/bdcolor.png", Qt::black));
    connect(bdColorToolBtn, &QAbstractButton::clicked, this, &MainWindow::clickbdBtn);
    ui->toolBar->addWidget(bdColorToolBtn);

    //填充颜色
    fillColorToolBtn = new QToolButton(this);
    fillColorToolBtn->setPopupMode(QToolButton::MenuButtonPopup);
    fillColorToolBtn->setMenu(createColorMenu(SLOT(itemColorChanged()), Qt::white));
    fillAction = fillColorToolBtn->menu()->defaultAction();
    fillColorToolBtn->setIcon(createColorToolButtonIcon(
                                     ":/images/floodfill.png", Qt::white));
    connect(fillColorToolBtn, &QAbstractButton::clicked, this, &MainWindow::clickFillBtn);
    ui->toolBar->addWidget(fillColorToolBtn);


    //箭头颜色
    arrowColorToolBtn = new QToolButton(this);
    arrowColorToolBtn->setPopupMode(QToolButton::MenuButtonPopup);
    arrowColorToolBtn->setMenu(createColorMenu(SLOT(arrowColorChanged()), Qt::black));
    arrowColorAction = arrowColorToolBtn->menu()->defaultAction();
    arrowColorToolBtn->setIcon(createColorToolButtonIcon(
                                     ":/images/arrowcolor.png", Qt::black));
    connect(arrowColorToolBtn, &QAbstractButton::clicked, this, &MainWindow::clickLineBtn);
    ui->toolBar->addWidget(arrowColorToolBtn);


    ui->toolBar->addWidget(ui->arrowComboBox);
    ui->arrowComboBox->addItem("实线箭头");
    ui->arrowComboBox->addItem("虚线箭头");
    ui->arrowComboBox->addItem("点线箭头");
    connect(ui->arrowComboBox, SIGNAL(activated(int)), this, SLOT(lineTypeChanged(int)));

        ui->toolBar->addSeparator();

    //边框粗细
     ui->bdSizeButton->setEnabled(false);
     ui->toolBar->addWidget(ui->bdSizeButton);

    bdSizeCombo = new QComboBox(this);
    bdSizeCombo->setEditable(true);
    for (int i = 2; i < 16; i = i + 1)
        bdSizeCombo->addItem(QString().setNum(i));
    bdSizeCombo->setCurrentText("6");
    QIntValidator *bd_validator = new QIntValidator(2, 15, this);
    bdSizeCombo->setValidator(validator);
    //connect(fontSizeCombo, &QComboBox::currentTextChanged, this, &MainWindow::changeFontSize);
    ui->toolBar->addWidget(bdSizeCombo);

    //箭头粗细
    ui->arrowSizeButton->setEnabled(false);
    ui->toolBar->addWidget(ui->arrowSizeButton);

    arrowSizeCombo = new QComboBox(this);
    arrowSizeCombo->setEditable(true);
    for (int i = 2; i < 16; i = i + 1)
        arrowSizeCombo->addItem(QString().setNum(i));
    arrowSizeCombo->setCurrentText("6");
    QIntValidator *arrow_validator = new QIntValidator(2, 15, this);
    arrowSizeCombo->setValidator(validator);
    //connect(fontSizeCombo, &QComboBox::currentTextChanged, this, &MainWindow::changeFontSize);
    ui->toolBar->addWidget(arrowSizeCombo);




    //菜单栏信号
    //文本框
    connect(ui->action_fontColor,&QAction::triggered,[=](){
        auto color = QColorDialog::getColor(QColor(Qt::black));
        changeTextColor(color);
    });
    connect(ui->action_font,&QAction::triggered,[this](){
        bool flag;
        auto font = QFontDialog::getFont(&flag, QFont("宋体",20));
        if (flag) changeFont(font);
    });
    //箭头
    connect(ui->action_arrowColor,&QAction::triggered,[=](){
        auto color = QColorDialog::getColor(QColor(Qt::black));
        changeLineColor(color);
    });
    // 箭头样式
    connect(ui->action_arrow1, &QAction::triggered, [this](){
        lineTypeChanged(0);
    });
    connect(ui->action_arrow2, &QAction::triggered, [this](){
        lineTypeChanged(1);
    });
    connect(ui->actiondain, &QAction::triggered, [this](){
        lineTypeChanged(2);
    });
    //节点
    connect(ui->action_bgColor,&QAction::triggered,[=](){
        auto color = QColorDialog::getColor(QColor(Qt::black));
        changeFillColor(color);
    });
    connect(ui->action_bdColor,&QAction::triggered,[this](){
        auto color = QColorDialog::getColor(QColor(Qt::black));
        changeFrameColor(color);
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

    _scene = new FlowChartScene();
    ui->graphicsView->setScene(scene());
    //_scene->setSceneRect(QRectF(QPointF(0.0f, 0.0f), ui->graphicsView->size()));
    _scene->setSceneRect(QRectF(0,0,5000,5000));

    //页面选项卡设计
    ui->tabWidget->clear();
    ui->tabWidget->setTabsClosable(true);
    ui->tabWidget->usesScrollButtons();

    connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(removeSubTab(int)));

//    FlowChartScene* scene = new FlowChartScene();
//    ui->graphicsView->setScene(scene);
    QWidget *tabFile0 = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(ui->graphicsView);
    tabFile0->setLayout(layout);
    ui->tabWidget->addTab(tabFile0,QIcon(":/images/file.png"),"0");
//    scene->setSceneRect(QRectF(QPointF(0.0f, 0.0f), ui->graphicsView->size()));
    open_scenes.append(_scene);
    qDebug()<<open_scenes.count();

//     _scene = ui->graphicsView->scene();

    _instance = this;

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

    connect(ui->treeView,&QTreeView::doubleClicked,[=](){

        QModelIndex currentIndex = ui->treeView->currentIndex();
        QStandardItem* currentItem = model->itemFromIndex(currentIndex);

//        qDebug()<<ui->tabWidget->count();
        if(!currentItem->hasChildren())
        {

            for(rename_index=0;rename_index<ui->tabWidget->count();rename_index++){
                if(ui->tabWidget->tabText(rename_index)==currentItem->text())
                    break;
            }

            connect(model,&QStandardItemModel::itemChanged,this,&MainWindow::modifyTabText);
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

            _scene->clearSelect();
            _scene = static_cast<FlowChartScene*>(graphicView->scene());
        }

    });

    // 将编辑菜单栏中的动作绑定到槽
    connect(ui->undoAction, SIGNAL(triggered()), this, SLOT(Undo()));
    connect(ui->redoAction, SIGNAL(triggered()), this, SLOT(Redo()));
    connect(ui->cutAction, SIGNAL(triggered()), this, SLOT(Cut()));
    connect(ui->copyAction, SIGNAL(triggered()), this, SLOT(Copy()));
    connect(ui->pasteAction, SIGNAL(triggered()), this, SLOT(Paste()));
    connect(ui->selectAllAction, SIGNAL(triggered()), this, SLOT(SelectAll()));
    connect(ui->deleteAction, SIGNAL(triggered()), this, SLOT(deleteElement()));
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

void MainWindow::removeSubTab(int index){

    open_scenes.removeAt(index);

    if(ui->tabWidget->count() == 1) {
        ui->tabWidget->removeTab(index);

        addNewTab();
    }
    else {
        ui->tabWidget->removeTab(index);
    }
    qDebug()<<open_scenes.count();
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


    scene->setSceneRect(QRectF(0,0,5000,5000));
    open_scenes.append(scene);
    qDebug()<<open_scenes.count();
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


    scene->setSceneRect(QRectF(0,0,5000,5000));
    open_scenes.append(scene);
    qDebug()<<open_scenes.count();
}

void MainWindow::addNewTab(QString name){
    foreach(auto n, index_name_subgraph){
        if(n.second==name){
            ui->tabWidget->setCurrentIndex(n.first);
            return;
        }
    }

    //创建新的VIEW和SCENE，并绑定
    FlowChartScene* scene = new FlowChartScene();
    QGraphicsView* graphicsView = new QGraphicsView();

    graphicsView->setScene(scene);

    //在tabWidget中加入 包含VIEW的布局的widget 并 切换tab
    QWidget *tabFile = new QWidget(this);
    QVBoxLayout *layout1 = new QVBoxLayout;
    layout1->addWidget(graphicsView);
    tabFile->setLayout(layout1);
    int index = ui->tabWidget->addTab(tabFile,QIcon(":/images/file.png"),name);
    ui->tabWidget->setCurrentWidget(tabFile);

    scene->setSceneRect(QRectF(0,0,5000,5000));
    open_scenes.append(scene);
    qDebug()<<open_scenes.count();

    index_name_subgraph.push_back({index,name});

}

int MainWindow::index_tab(){
    return ui->tabWidget->currentIndex();
}

void MainWindow::modifyTabText(QStandardItem* item){

    ui->tabWidget->tabBar()->setTabText(rename_index,item->text());
}

//****************************************************************
int Flag_isOpen = 0;       //标记：判断是否打开或创建了一个文件
int Flag_IsNew = 0;        //标记：如果新建了文件就为1，初始值为0
QString Last_FileName;     //最后一次保存的文件的名字
QString Last_FileContent;  //最后一次保存文件的内容
void MainWindow::on_action1_triggered()//新建
{

    textEdit->clear();              //清除原先文件内容
    textEdit->setHidden(false);     //显示文本框
    Flag_IsNew = 1;                 //新文件标记位设为1
    Flag_isOpen = 1;                //新文件创建 标记位设为1
}

void MainWindow::on_action1_2_triggered()//打开
{
    QString fileName;
        fileName = QFileDialog::getOpenFileName(this,tr("Open File"),tr(""),tr("Text File (*.txt)"));
        if(fileName == "")
        {
            return;
        }
        else
        {
           QFile file(fileName);
           if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
           {
               QMessageBox::warning(this,tr("错误"),tr("打开文件失败"));
               return;
           }
           else
           {
               if(!file.isReadable())
               {
                   QMessageBox::warning(this,tr("错误"),tr("该文件不可读"));
               }
               else
               {
                   QTextStream textStream(&file);       //读取文件，使用QTextStream
                   while(!textStream.atEnd())
                   {
                       textEdit->setPlainText(textStream.readAll());
                   }
                   textEdit->show();
                   file.close();
                   Flag_isOpen = 1;
                   Last_FileName = fileName;
               }
           }
        }
}

void MainWindow::on_action1_3_triggered()//保存
{
    if(Flag_IsNew)                  //如果新文件标记位为1，则弹出保存文件对话框
       {
           if(textEdit->toPlainText() == "")
           {
               QMessageBox::warning(this,tr("警告"),tr("内容不能为空!"),QMessageBox::Ok);
           }
           else
           {
               QFileDialog fileDialog;
               QString str = fileDialog.getSaveFileName(this,tr("Open File"),"/home",tr("Text File(*.txt)"));
               if(str == "")
               {
                   return;
               }
               QFile filename(str);
               if(!filename.open(QIODevice::WriteOnly | QIODevice::Text))
               {
                   QMessageBox::warning(this,tr("错误"),tr("打开文件失败"),QMessageBox::Ok);
                   return;
               }
               else
               {
                   QTextStream textStream(&filename);
                   QString str = textEdit->toPlainText();
                   textStream<<str;
                   Last_FileContent = str;
               }
               QMessageBox::information(this,"保存文件","保存文件成功",QMessageBox::Ok);
               filename.close();
               Flag_IsNew = 0;     //新文件标记位记为0
               Last_FileName = str;//保存文件内容
           }
       }
       else                        //否则，新文件标记位是0，代表是旧文件，默认直接保存覆盖源文件
       {
           if(Flag_isOpen)         //判断是否创建或打开了一个文件
           {
               QFile file(Last_FileName);
               if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
               {
                   QMessageBox::warning(this,tr("警告"),tr("打开文件失败"));
                   return;
               }
               else
               {
                   QTextStream textStream(&file);
                   QString str = textEdit->toPlainText();
                   textStream<<str;
                   Last_FileContent = str;
                   file.close();
               }
           }
           else
           {
               QMessageBox::warning(this,tr("警告"),tr("请先创建或者打开文件"));
               return;
           }
       }
}

void MainWindow::on_action1_4_triggered()//另存为
{
    QFileDialog fileDialog;
       QString fileName = fileDialog.getSaveFileName(this,tr("Open File"),"/home",tr("Text File(*.txt)"));
       if(fileName == "")
       {
           return;
       }
       QFile file(fileName);
       if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
       {
           QMessageBox::warning(this,tr("错误"),tr("打开文件失败"));
           return;
       }
       else
       {
           QTextStream textStream(&file);
           QString str = textEdit->toPlainText();
           textStream<<str;
           QMessageBox::warning(this,tr("提示"),tr("保存文件成功"));
           Last_FileContent = str;
           Last_FileName = fileName;
           Flag_IsNew = 0;
           file.close();
       }
}

Graph* MainWindow::graph()
{
    return static_cast<FlowChartScene*>(scene())->graph;
}


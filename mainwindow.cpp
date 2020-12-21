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
#include <QScrollBar>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene.h"
#include "editelementaction.h"
#include "groupaction.h"
#include "nodeevents.h"
#include "arrow.h"
#include "item.h"
#include "saver.h"
#include "filemanager.h"
#include "subgraphnode.h"
#include "checker.h"
#include "autosavethread.h"

//**************************
#include "graph.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>
#include <QByteArray>
#include <QDebug>
#include <QVariant>
//**************************
MainWindow* MainWindow::_instance;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowState(Qt::WindowMaximized);

    //状态栏
/*        ui->listWidget->addItem("提示信息1");
        ui->listWidget->addItem("提示信息2");
        ui->listWidget->addItem("提示信息3");
        ui->listWidget->addItem("提示信息4");
        ui->listWidget->addItem("提示信息5");*/




    //工具栏
    //ui->toolBar->addWidget(ui->backBtn);
    //ui->toolBar->addWidget(ui->copyBtn);
    //ui->toolBar->addWidget(ui->pasteBtn);

    ui->toolBar->addSeparator();

    fontBtn = new QFontComboBox(this);
    fontBtn->setEditable(false);
    fontBtn->setCurrentFont(QFont("微软雅黑"));
    connect(fontBtn, &QFontComboBox::currentFontChanged, this, &MainWindow::changeFontFamily);
    ui->toolBar->addWidget(fontBtn);

    ui->toolBar->addSeparator();

    //字号
    fontSizeCombo = new QComboBox(this);
    //fontSizeCombo->setEditable(true);
    for (int i = 6; i < 52; i = i + 2)
        fontSizeCombo->addItem(QString().setNum(i));
    fontSizeCombo->setCurrentText("10");
    QIntValidator *validator = new QIntValidator(2, 64, this);
    fontSizeCombo->setValidator(validator);
    connect(fontSizeCombo, SIGNAL(activated(const QString&)), this, SLOT(changeFontSize(QString)));
    ui->toolBar->addWidget(fontSizeCombo);

    ui->toolBar->addSeparator();

    //ui->toolBar->addWidget(ui->boldBtn);
    //ui->toolBar->addWidget(ui->italicBtn);
    //ui->toolBar->addWidget(ui->underlineBtn);

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
    //bdSizeCombo->setEditable(true);
    for (int i = 2; i < 16; i = i + 1)
        bdSizeCombo->addItem(QString().setNum(i));
    bdSizeCombo->setCurrentText("2");
    QIntValidator *bd_validator = new QIntValidator(2, 15, this);
    bdSizeCombo->setValidator(bd_validator);
    connect(bdSizeCombo, SIGNAL(activated(const QString&)), this, SLOT(changeFrameWidth(QString)));
    ui->toolBar->addWidget(bdSizeCombo);

    //箭头粗细
    ui->arrowSizeButton->setEnabled(false);
    ui->toolBar->addWidget(ui->arrowSizeButton);

    arrowSizeCombo = new QComboBox(this);
    //arrowSizeCombo->setEditable(true);
    for (int i = 2; i < 16; i = i + 1)
        arrowSizeCombo->addItem(QString().setNum(i));
    arrowSizeCombo->setCurrentText("2");
    QIntValidator *arrow_validator = new QIntValidator(2, 15, this);
    arrowSizeCombo->setValidator(arrow_validator);
    connect(arrowSizeCombo, SIGNAL(activated(const QString&)), this, SLOT(changeLineWidth(QString)));
    ui->toolBar->addWidget(arrowSizeCombo);




    //菜单栏信号
    //文本框
    connect(ui->action_fontColor,&QAction::triggered,[=](){
        auto color = QColorDialog::getColor(QColor(Qt::black));
        changeTextColor(color);
    });
    connect(ui->action_font,&QAction::triggered,[this](){
        bool flag;
        auto font = QFontDialog::getFont(&flag, QFont("微软雅黑",10));
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
    //箭头和节点粗细

    connect(ui->action_nodeSize,&QAction::triggered,[=](){
        sizeDialog();
    });
    connect(ui->action_arrowSize,&QAction::triggered,[=](){
        sizeDialog();
    });


    fileManager = new FileManager(this);
    model = fileManager->model;

    //treeview右键菜单
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeView,&QTreeView::customContextMenuRequested,this,&MainWindow::onTreeViewMenuRequested);
/*
    _scene = new Scene(defaultGraph);
    ui->graphicsView->setScene(scene());
    //_scene->setSceneRect(QRectF(QPointF(0.0f, 0.0f), ui->graphicsView->size()));
    _scene->setSceneRect(QRectF(0,0,5000,5000));
*/
    //页面选项卡设计
    ui->tabWidget->clear();
    ui->tabWidget->setTabsClosable(true);
    ui->tabWidget->usesScrollButtons();

    connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(removeSubTab(int)));
/*
//    FlowChartScene* scene = new FlowChartScene();
//    ui->graphicsView->setScene(scene);
    QWidget *tabFile0 = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(ui->graphicsView);
    tabFile0->setLayout(layout);
    ui->tabWidget->addTab(tabFile0,QIcon(":/images/file.png"),"0");
//    scene->setSceneRect(QRectF(QPointF(0.0f, 0.0f), ui->graphicsView->size()));
    open_scenes.append(_scene);
    //在tab里保存路径
    tab_data Data0;
    Data0.path = "NULL";
    QVariant tabVariData;
    tabVariData.setValue<tab_data>(Data0);
    ui->tabWidget->tabBar()->setTabData(0,tabVariData);
*/
//     _scene = ui->graphicsView->scene();

    _instance = this;

    //项目树结构和页面选项卡的连接
    connect(ui->treeView,&QTreeView::clicked,[=](){

        QModelIndex currentIndex = ui->treeView->currentIndex();
        QStandardItem* currentItem = model->itemFromIndex(currentIndex);
        auto item = static_cast<Item*>(currentItem);

        if(item->itemType() == ::ItemType::File)
        {
            if (item->tab())
            {
                ui->tabWidget->setCurrentWidget(item->tab());
            }
            else
            {
                addNewTab(currentItem);
            }
        }
    });

    //找到tab中要改名的那个tab的index
    connect(ui->treeView,&QTreeView::doubleClicked,[=](){

        QModelIndex currentIndex = ui->treeView->currentIndex();
        QStandardItem* currentItem = model->itemFromIndex(currentIndex);
        auto item = static_cast<Item*>(currentItem);

        if(item->itemType() == ItemType::File)
        {

            for(rename_index=0;rename_index<ui->tabWidget->count();rename_index++){
                if(ui->tabWidget->tabBar()->tabData(rename_index).value<tab_data>().path==item->path())
                    break;
            }
        }
    });

    //改tab名字和路径
    connect(model,&QStandardItemModel::itemChanged,this,&MainWindow::modifyTabText);
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::on_tabWidget_tabCloseRequested);


    //切换选项卡时scene的切换
    connect(ui->tabWidget,&QTabWidget::currentChanged,[=](){

        if(ui->tabWidget->count() != 0){
            QLayoutItem* item = ui->tabWidget->currentWidget()->layout()->itemAt(0);
            QGraphicsView* graphicView = qobject_cast<QGraphicsView*>(item->widget());

            if (_scene) _scene->clearSelect();
            _scene = static_cast<Scene*>(graphicView->scene());
        }

    });

    auto closeProject = [this]()
    {
        startWait();
        auto root = model->invisibleRootItem();
        auto item = static_cast<Item*>(root->child(0));
        if (item) removeItem(item);
        _scene = nullptr;
        ui->tabWidget->setStyleSheet("border-image: url(:/images/one_plane.png);");
        endWait();
    };

    connect(ui->newProjectAction, &QAction::triggered, [this, closeProject]()
    {
        auto path = QFileDialog::getSaveFileName(window(), "新建项目文件", QString(), "项目文件(*.pr)");
        if (path != QString())
        {
            closeProject();
            startWait();
            auto item = new Item(ItemType::Project, path);
            model->appendRow(item);
            Saver::AddNewProject(path);
            endWait();
        }
    });

    connect(ui->openProjectAction, &QAction::triggered, [this, closeProject]()
    {
        auto path = QFileDialog::getOpenFileName(window(), "打开项目", QString(), "项目文件(*.pr)");
        if (path != QString())
        {
            closeProject();
            startWait();
            Saver::ClearRelation();
            auto item = Saver::Open(path);
            Saver::AddRelation();
            model->appendRow(item);
            endWait();
        }
    });

    connect(ui->actionsave, &QAction::triggered, [this]()
    {
        startWait();
        auto root = model->invisibleRootItem();
        auto item = static_cast<Item*>(root->child(0));
        if (item) saveItem(item);
        endWait();
    });

    connect(ui->actionclose_pro, &QAction::triggered, [this, closeProject]()
    {
        startWait();
        closeProject();
        endWait();
    });

    connect(ui->actioncheck_pro, &QAction::triggered, [this]()
    {
        startWait();
        Checker::check();
        endWait();
    });

    // 将编辑菜单栏中的动作绑定到槽
    connect(ui->undoAction, SIGNAL(triggered()), this, SLOT(Undo()));
    connect(ui->redoAction, SIGNAL(triggered()), this, SLOT(Redo()));
    connect(ui->cutAction, SIGNAL(triggered()), this, SLOT(Cut()));
    connect(ui->copyAction, SIGNAL(triggered()), this, SLOT(Copy()));
    connect(ui->pasteAction, SIGNAL(triggered()), this, SLOT(Paste()));
    connect(ui->selectAllAction, SIGNAL(triggered()), this, SLOT(SelectAll()));
    connect(ui->deleteAction, SIGNAL(triggered()), this, SLOT(deleteElement()));

    //ui->tabWidget->setStyleSheet("border-image: url(:/images/one_plane.png);");

    connect(AutoSaveThread::instance(), &AutoSaveThread::autoSave, this, &MainWindow::autoSave, Qt::BlockingQueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
    _instance = nullptr;
}

void MainWindow::autoSave()
{
    startWait();
    auto root = model->invisibleRootItem();
    auto item = static_cast<Item*>(root->child(0));
    if (item) saveItem(item);
    endWait();
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

        _scene = nullptr;
        //addNewTab();
    }
    else {
        ui->tabWidget->removeTab(index);
    }
    ui->tabWidget->setStyleSheet("border-image: url(:/images/one_plane.png);");
}

void MainWindow::addNewTab(QStandardItem* currentItem){
    auto item = static_cast<Item*>(currentItem);

    //创建新的VIEW和SCENE，并绑定
    QGraphicsView* graphicsView = new QGraphicsView();
    graphicsView->setContentsMargins(0, 0, 0, 0);

    graphicsView->setScene(item->scene());

    //在tabWidget中加入 包含VIEW的布局的widget 并 切换tab
    QWidget *tabFile = new QWidget(this);
    tabFile->setStyleSheet("border: 0px solid #ffffff");
    QVBoxLayout *layout1 = new QVBoxLayout;
    //layout1->setSpacing(0);
    layout1->addWidget(graphicsView);
    tabFile->setLayout(layout1);
    ui->tabWidget->addTab(tabFile,QIcon(":/images/file.png"),currentItem->text());
    ui->tabWidget->setCurrentWidget(tabFile);
    item->setTab(tabFile);

    int tabCount = ui->tabWidget->count();

    //在tab里保存路径
    tab_data Data0;
    Data0.path = item->path();
    Data0.item = item;
    QVariant tabVariData;
    tabVariData.setValue<tab_data>(Data0);
    ui->tabWidget->tabBar()->setTabData(tabCount-1,tabVariData);

    graphicsView->horizontalScrollBar()->setSliderPosition(0);
    graphicsView->verticalScrollBar()->setSliderPosition(0);
    open_scenes.append(item->scene());

    auto a = layout1->spacing();
    ui->tabWidget->setStyleSheet("border: 10px solid #215E21");
}

void MainWindow::addNewTab(){
    //创建新的VIEW和SCENE，并绑定
/*    defaultGraph->clear();
    Scene* scene = new Scene(defaultGraph);
    QGraphicsView* graphicsView = new QGraphicsView();

    graphicsView->setScene(scene);

    //在tabWidget中加入 包含VIEW的布局的widget 并 切换tab
    QWidget *tabFile = new QWidget(this);
    QVBoxLayout *layout1 = new QVBoxLayout;
    layout1->addWidget(graphicsView);
    tabFile->setLayout(layout1);
    ui->tabWidget->addTab(tabFile,QIcon(":/images/file.png"),"0");
    ui->tabWidget->setCurrentWidget(tabFile);

    //在tab里保存路径
    tab_data Data0;
    Data0.path = "NULL";
    QVariant tabVariData;
    tabVariData.setValue<tab_data>(Data0);
    ui->tabWidget->tabBar()->setTabData(0,tabVariData);


    scene->setSceneRect(QRectF(0,0,5000,5000));
    open_scenes.append(scene);
    qDebug()<<open_scenes.count();*/
}

bool MainWindow::addNewTab(Node* node, QString name){
    auto subGraph = static_cast<SubgraphNode*>(node);
    if (subGraph->relatedGraph)
    {
        auto item = subGraph->relatedGraph->scene->item;
        if (item->tab()) ui->tabWidget->setCurrentWidget(item->tab());
        else addNewTab(item);
        return true;
    }
    auto root = model->invisibleRootItem();
    auto projectItem = static_cast<Item*>(root->child(0));
    //auto path =  + "/" + name + ".gr";
    Item* item;
    auto path = QFileDialog::getSaveFileName(this, "添加新文件", QString(), "图文件(*.gr)");
    if (path != QString())
    {
        if (scene()->item->path() == path)
        {
            QMessageBox::warning(this, "警告", "不能把这张图替换为子图");
            return false;
        }
        item = new Item(::ItemType::File, path);
        projectItem->appendRow(item);
        Saver::AddNewFile(path, item);
        saveItem(projectItem);
        node->BindToText(scene());
        node->content->change_content(item->name());
    }
    else return false;
    name = item->name();

    //创建新的VIEW和SCENE，并绑定
    QGraphicsView* graphicsView = new QGraphicsView();

    graphicsView->setScene(item->scene());

    //在tabWidget中加入 包含VIEW的布局的widget 并 切换tab
    QWidget *tabFile = new QWidget(this);
    QVBoxLayout *layout1 = new QVBoxLayout;
    layout1->addWidget(graphicsView);
    tabFile->setLayout(layout1);
    int index = ui->tabWidget->addTab(tabFile,QIcon(":/images/file.png"),name);
    ui->tabWidget->setCurrentWidget(tabFile);
    item->setTab(tabFile);

    int tabCount = ui->tabWidget->count();
    tab_data Data0;
    Data0.path = item->path();
    Data0.item = item;
    QVariant tabVariData;
    tabVariData.setValue<tab_data>(Data0);
    ui->tabWidget->tabBar()->setTabData(tabCount-1,tabVariData);

    graphicsView->horizontalScrollBar()->setSliderPosition(0);
    graphicsView->verticalScrollBar()->setSliderPosition(0);
    open_scenes.append(item->scene());

    index_name_subgraph.push_back({index,name});

    return true;
}

int MainWindow::index_tab(){
    return ui->tabWidget->currentIndex();
}

QVector<QString> MainWindow::getChildrenPaths(QStandardItem* item)
{
    QVector<QString> children;
    for (auto i = 0; i < item->rowCount(); i++)
    {
        auto child = item->child(i);
        children.append(child->data(Qt::UserRole).value<item_data>().path);
        children.append(getChildrenPaths(child));
    }
    return children;
}

void MainWindow::modifyChildPath(QStandardItem* item){
    for (auto i = 0; i < item->rowCount(); i++){
        auto child = item->child(i);
        QString parentPath=static_cast<Item*>(child->parent())->path();
        QString curPath = parentPath+"/"+child->text();
        static_cast<Item*>(child)->setPath(curPath);
        if(child->rowCount()!=0){
            modifyChildPath(child);
        }
    }
}

void MainWindow::checkName(QStandardItem *item, bool showMessage){
    auto row = item->row();
    auto parent = item->parent();
    auto text = item->text();
    auto path = item->data(Qt::UserRole).value<item_data>().path;
    auto hasSame = true;
    auto hasShown = false;
    QVector<QString> paths;
    for (auto i = 0; i < model->rowCount(); i++)
    {
        paths.append(model->item(i)->data(Qt::UserRole).value<item_data>().path);
        paths.append(getChildrenPaths(model->item(i)));
    }
    for(auto i =0;i<paths.count();i++){
        qDebug()<<"paths:"<<paths[i];
    }

    paths.removeOne(path);
    while (hasSame)
    {
        hasSame = false;
        if (paths.contains(path))
        {
            if (!hasShown && showMessage)
            {
                QMessageBox::information(this, "提示", "出现同名", QMessageBox::Yes);
            }
            hasShown = true;
            item->setText(item->text() + "1");
            path=path+"1";

            qDebug()<<"curItem:"<<item->data(Qt::UserRole).value<item_data>().path;
            qDebug()<<"path:"<<path;

            hasSame = true;
        }
    }
    item_data data0;
    if(item->data(Qt::UserRole).value<item_data>().type == 2){
        data0.type=2;
        data0.path=path;
        QVariant itemVariData;
        itemVariData.setValue<item_data>(data0);
        item->setData(itemVariData,Qt::UserRole);
    }
    else if(item->data(Qt::UserRole).value<item_data>().type == 3){
        data0.type=3;
        data0.path=path;
        QVariant itemVariData;
        itemVariData.setValue<item_data>(data0);
        item->setData(itemVariData,Qt::UserRole);
    }
    else if(item->data(Qt::UserRole).value<item_data>().type == 1){
        data0.type=3;
        data0.path=path;
        QVariant itemVariData;
        itemVariData.setValue<item_data>(data0);
        item->setData(itemVariData,Qt::UserRole);
    }
}

void MainWindow::modifyTabText(QStandardItem* standardItem){

    auto item = static_cast<Item*>(standardItem);

    if (item->text() == item->name()) return;

    if (item->itemType() == ItemType::Folder)
    {
        auto parent = item->parent();
        for (auto i = 0; i < parent->rowCount(); i++)
        {
            auto sibling = static_cast<Item*>(parent->child(i));
            if (sibling != item && sibling->name() == item->text())
            {
                QMessageBox::warning(this, "警告", "父目录下已有同名筛选器！");
                item->setText(item->name());
                return;
            }
        }
    }
    if (!item->rename(item->text()))
    {
        QMessageBox::warning(this, "警告", "重命名文件失败！");
        item->setText(item->name());
    }
    saveItem(static_cast<Item*>(model->invisibleRootItem()->child(0)));
    auto tabWidget = ui->tabWidget;
    auto index = tabWidget->indexOf(item->tab());
    tabWidget->setTabText(index, item->text());
/*    if(item->itemType() == ItemType::File) {
        ui->tabWidget->tabBar()->setTabText(rename_index,standardItem->text());

        auto newName = item->text();
        if (item->itemType() == ::ItemType::File)
        {
            Saver::Rename(item->path(), newName);
        }
        //item->rename(newName);

        //修改tab里存储的路径
        tab_data Data0;
        Data0.path = static_cast<Item*>(item->parent())->path()+"/"+item->text();
        if (item->itemType() == ::ItemType::File) Data0.path += ".gr";
        qDebug()<<Data0.path;
        QVariant tabVariData;
        tabVariData.setValue<tab_data>(Data0);
        ui->tabWidget->tabBar()->setTabData(rename_index,tabVariData);

        //修改item里存储的路径
        item->setPath(Data0.path);
    }
    else if(item->itemType() == ItemType::Folder){
        QString parentPath=static_cast<Item*>(item->parent())->path();
        QString curPath = parentPath+"/"+item->text();
        item->setPath(curPath);
        modifyChildPath(item);

    }
    else if (item->itemType() == ItemType::Project) {
        QString prePath=static_cast<Item*>(item)->path();
        QString curPath;
        auto prePathParts = prePath.split('/');
        auto length = prePathParts.length();
        for (auto i = 1; i < length - 2; i++)
        {
            auto pathPart = prePathParts[i];
            curPath += "/" + pathPart;
        }
        curPath+=item->text();
        item->setPath(curPath);
        modifyChildPath(item);
    }*/
}

void MainWindow::sizeDialog(){
//    QDialog dlg(this);
    dlg = new QDialog(this);
    dlg->resize(400,300);
    dlg->setWindowTitle("设置粗细");
    QLabel *label_nodeSize = new QLabel();
    label_nodeSize->setText("边框粗细：");
    nodeSizeCombo_menu = new QComboBox(this);
    nodeSizeCombo_menu->setEditable(true);
    for (int i = 2; i < 16; i = i + 1)
        nodeSizeCombo_menu->addItem(QString().setNum(i));
    nodeSizeCombo_menu->setCurrentText("2");
    QIntValidator *node_validator = new QIntValidator(2, 15, this);
    nodeSizeCombo_menu->setValidator(node_validator);
    QHBoxLayout* up =new QHBoxLayout();
    up->addWidget(label_nodeSize);
    up->addWidget(nodeSizeCombo_menu);
    up->setContentsMargins(30,5,30,5);
    up->setSpacing(10);

    QLabel *label_arrowSize = new QLabel();
    label_arrowSize->setText("箭头粗细：");
    arrowSizeCombo_menu = new QComboBox(this);
    arrowSizeCombo_menu->setEditable(true);
    for (int i = 2; i < 16; i = i + 1)
        arrowSizeCombo_menu->addItem(QString().setNum(i));
    arrowSizeCombo_menu->setCurrentText("2");
    QIntValidator *arrow_validator = new QIntValidator(2, 15, this);
    arrowSizeCombo_menu->setValidator(arrow_validator);
    QHBoxLayout* down =new QHBoxLayout();
    down->addWidget(label_arrowSize);
    down->addWidget(arrowSizeCombo_menu);
    down->setContentsMargins(30,5,30,5);
    down->setSpacing(10);

    ok_sizeBtn = new QPushButton();
    ok_sizeBtn->setText("确定");
    cancel_sizeBtn = new QPushButton();
    cancel_sizeBtn->setText("取消");
    QHBoxLayout* tail =new QHBoxLayout();
    tail->addWidget(ok_sizeBtn);
    tail->addWidget(cancel_sizeBtn);
    tail->setContentsMargins(50,20,50,20);
    tail->setSpacing(20);

    QVBoxLayout*sizeDialog = new QVBoxLayout();
    sizeDialog->addLayout(up);
    sizeDialog->addLayout(down);
    sizeDialog->addLayout(tail);


    dlg->setLayout(sizeDialog);

    connect(cancel_sizeBtn,&QPushButton::clicked,this,&MainWindow::cancel_sizeBtn_clicked);
    connect(ok_sizeBtn,&QPushButton::clicked,this,&MainWindow::ok_sizeBtn_clicked);
    auto result = dlg->exec();
    if (result == QDialog::Accepted)
    {
        auto frameWidthString = nodeSizeCombo_menu->currentText();
        if (frameWidthString.toInt() != frameWidth)
        {
            bdSizeCombo->setCurrentText(frameWidthString);
            changeFrameWidth(frameWidthString);
        }
        auto arrowWidthString = arrowSizeCombo_menu->currentText();
        if (arrowWidthString.toInt() != lineWidth)
        {
            arrowSizeCombo->setCurrentText(arrowWidthString);
            changeLineWidth(arrowWidthString);
        }
    }
}

void MainWindow::ok_sizeBtn_clicked(){
    dlg->done(1);
}
void MainWindow::cancel_sizeBtn_clicked(){
    dlg->done(0);
}

void MainWindow::onTreeViewMenuRequested(const QPoint &pos){
    QModelIndex curIndex = ui->treeView->indexAt(pos);
    QStandardItem* curItem = model->itemFromIndex(curIndex);
    auto root = static_cast<Item*>(model->item(0));
    if(curIndex.isValid()){
        auto item = static_cast<Item*>(curItem);
        auto type = item->itemType();
        QMenu menu;
        int item_type=curItem->data(Qt::UserRole).value<item_data>().type;
        QAction* addFolderAction = nullptr, *addExistingFileAction = nullptr,
                *SaveProjectAction = nullptr, *importBranchesAction = nullptr,
                *CloseProjectAction = nullptr, *exportCsvAction = nullptr,
                *CloseFileAction = nullptr, *RemoveAction = nullptr,
                *SaveFileAction = nullptr, *SaveAsFileAction = nullptr,
                *ShowBrachesAction = nullptr, *importNodeDictionaryPathAction = nullptr,
                *importBranchDictionaryPathAction = nullptr,
                *addNewFileAction = nullptr, *showPathAction = nullptr;
        switch (type) {
        case ItemType::Project:
            addNewFileAction = menu.addAction("添加新文件");
            addExistingFileAction = menu.addAction("添加现有文件");
            addFolderAction = menu.addAction("添加筛选器");
            SaveProjectAction = menu.addAction("保存项目");
            //SaveProjectAsAction = menu.addAction("Save Project As");
            CloseProjectAction = menu.addAction("关闭项目");
            showPathAction = menu.addAction("显示详细信息");
            break;
        case ItemType::Folder:
            addNewFileAction = menu.addAction("添加新文件");
            addExistingFileAction = menu.addAction("添加现有文件");
            addFolderAction = menu.addAction("添加筛选器");
            RemoveAction = menu.addAction("移除筛选器");
            showPathAction = menu.addAction("显示详细信息");
            break;
        case ItemType::File:
            RemoveAction = menu.addAction("移除文件");
            CloseFileAction = menu.addAction("关闭文件");
            SaveFileAction = menu.addAction("保存文件");
            importBranchesAction = menu.addAction("导入Branches文件");
            exportCsvAction = menu.addAction("导出csv文件");
            importNodeDictionaryPathAction = menu.addAction("导入节点字典文件");
            importBranchDictionaryPathAction = menu.addAction("导入分支字典文件");
            showPathAction = menu.addAction("显示详细信息");
        }
        auto selectedAction = menu.exec(QCursor::pos());
        if (selectedAction == nullptr) return;
        auto addFolder = [item, root, this]()
        {
            auto newPath = item->path() + "/新筛选器";
            auto newItem = new Item(::ItemType::Folder, newPath);
            item->appendRow(newItem);
            startWait();
            Saver::Save(root);
            endWait();
        };
        if (selectedAction == addFolderAction) addFolder();
        else if (selectedAction == addExistingFileAction)
        {
            auto path = QFileDialog::getOpenFileName(this, "添加现有文件", QString(), "图文件(*.gr)");
            if (path != QString())
            {
                startWait();
                auto newItem = Saver::Open(path);
                item->appendRow(newItem);
                Saver::Save(root);
                endWait();
            }
        }
        else if (selectedAction == SaveProjectAction) saveItem(item);
/*        else if (selectedAction == SaveProjectAsAction)
        {
            auto path = QFileDialog::getSaveFileName(this, "另存为项目", "",
                                                     "项目文件(*.pr)");
            Saver::SaveAs(item, path);
        }*/
        else if (selectedAction == CloseProjectAction) removeItem(item);
        else if (selectedAction == addNewFileAction)
        {
            auto path = QFileDialog::getSaveFileName(this, "添加新文件", QString(), "图文件(*.gr)");
            if (path != QString())
            {
                auto newItem = new Item(::ItemType::File, path);
                item->appendRow(newItem);
                startWait();
                Saver::AddNewFile(path, newItem);
                saveItem(root);
                endWait();
            }
        }
        else if (selectedAction == CloseFileAction) closeItem(item);
        else if (selectedAction == RemoveAction)
        {
            removeItem(item);
            startWait();
            Saver::Save(root);
            endWait();
        }
        else if (selectedAction == SaveFileAction)
        {
            startWait();
            Saver::Save(item);
            endWait();
        }
        else if (selectedAction == SaveAsFileAction)
        {
            auto path = QFileDialog::getSaveFileName(this, "另存为文件", "",
                                                            "图文件(*.gr)");
            Saver::SaveAs(item, path);
        }
        else if (selectedAction == showPathAction)
        {
            auto string = "路径：" + item->path() + "\n" +
                    "分支表文件路径：" + item->graph()->branchesPath + "\n" +
                    "节点字典文件路径：" + item->graph()->nodeDictionaryPath + "\n" +
                    "分支字典文件路径：" + item->graph()->branchDictionaryPath + "\n";
            QMessageBox::information(this, "详细信息", string);
        }
        else if (selectedAction == importBranchesAction)
        {
            auto path = QFileDialog::getOpenFileName(this, "导入Branches文件", "", "Branches文件(*.branches)");
            if (path != "")
            {
                item->graph()->branchesPath = path;
                startWait();
                Saver::ImportBranches(item, path);
                endWait();
            }
        }
        else if (selectedAction == importNodeDictionaryPathAction)
        {
            auto path = QFileDialog::getOpenFileName(this, "导入节点字典文件", "", "csv文件(*.csv)");
            if (path != "")
            {
                item->graph()->nodeDictionaryPath = path;
                startWait();
                Saver::ImportDictionary(item->scene()->nodeDictionary, path);
                endWait();
            }
        }
        else if (selectedAction == importBranchDictionaryPathAction)
        {
            auto path = QFileDialog::getOpenFileName(this, "导入分支字典文件", "", "csv文件(*.csv)");
            if (path != "")
            {
                item->graph()->branchDictionaryPath = path;
                startWait();
                Saver::ImportDictionary(item->scene()->branchDictionary, path);
                endWait();
            }
        }
        else if (selectedAction == exportCsvAction)
        {
            auto path = QFileDialog::getSaveFileName(this, "导出csv文件", "", "csv文件(*.csv)");
            if (path != "")
            {
                startWait();
                Saver::ExportCsv(item, path);
                endWait();
            }
        }
        else if (selectedAction == ShowBrachesAction)
        {

        }
    }
}

Graph* MainWindow::graph()
{
    return scene() ? static_cast<Scene*>(scene())->graph : nullptr;
}

Ui::MainWindow* MainWindow::getUi() const
{
    return ui;
}
void MainWindow::on_action1_3_triggered()
{
    QList<Scene*>::iterator iter;
    QJsonArray graphArray;
    QJsonObject qso;
    QString path;

    for(iter=open_scenes.begin();iter!=open_scenes.end();iter++)
    {
        graphArray.append((*iter)->graph->get_JsonObject());
        //save all
       if((*iter)->graph->getPath()=="" ||  (*iter)->graph->getPath()==nullptr)
        {
            //打开文件保存对话框选取路径与文件名，存入PATH
            QFileDialog fileDialog;
            QString fileName = fileDialog.getSaveFileName(this,tr("保存文件"),"请输入文件名",tr("JSON File(*.json)"));
        }
        //存入每一个GRAPH到文件中
          (*iter)->graph->write_to_file(path);
          QJsonObject gqso;
          gqso.insert("FilePath",path);
          gqso.insert("GraphID",(*iter)->graph->GetID());
          graphArray.append(gqso);                     }


            qso.insert("Project",QJsonValue(graphArray));
            //save qso into json file
            QJsonDocument doc;
            doc.setObject(qso);
               //打开项目文件，这一部分的项目文件名，应当是右边TREEVIEW项目保存时给定的项目文件名，在TREEVIEW没有做好之前暂时用以下文件名作调试。
            QFile file(QApplication::applicationDirPath()+"/1.json");
            if(!file.open(QIODevice::WriteOnly))
            {
                qDebug() << "File open failed!";
            }
            else
            {
                qDebug() <<"File open successfully!";
            }
                 file.write(doc.toJson(QJsonDocument::Indented)); //Indented:表示自动添加/n回车符
                 file.close();
}

void onCloseTab(QWidget* tab, Item* item)
{
    for (auto i = 0; i < item->rowCount(); i++)
    {
        auto child = static_cast<Item*>(item->child(i));
        if (child->tab() == tab)
        {
            child->setTab(nullptr);
            return;
        }
        if (child->itemType() == ItemType::Folder)
        {
            onCloseTab(tab, child);
        }
    }
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    auto tabwidget = ui->tabWidget;
    auto lastIndex = tabwidget->currentIndex();
    tabwidget->setCurrentIndex(index);
    auto widget = tabwidget->currentWidget();
    if (widget == nullptr) return;
    auto layout = widget->layout();
    auto item = layout->itemAt(0);
    auto itemWidget = item->widget();
    auto view = qobject_cast<QGraphicsView*>(itemWidget);
    auto graphicsScene = view->scene();
    auto scene = static_cast<Scene*>(graphicsScene);
    auto isChanged = scene->isChanged;
    if (isChanged)
    {
        auto yesButton = QMessageBox::Yes;
        QString fileName = tabwidget->tabText(index);
        if (fileName.endsWith('*')) fileName = fileName.mid(0, fileName.size() - 1);
        auto message = fileName + "文件有更改，要保存吗？";
        auto result = QMessageBox::information(this, "提示", message,
                                               yesButton | QMessageBox::No,
                                               yesButton);
        if (result == yesButton)
        {
            auto item = tabwidget->tabBar()->tabData(index).value<tab_data>().item;
            startWait();
            Saver::Save(item);
            endWait();
        }
    }
    tabwidget->setCurrentIndex(lastIndex);
    onCloseTab(widget, static_cast<Item*>(model->invisibleRootItem()->child(0)));
}

void MainWindow::treeItemChanged(QStandardItem* item)
{

}

void MainWindow::closeItem(Item* item)
{
    auto texts = getChildrenPaths(item);
    texts.append(item->text());
    auto tabWidget = ui->tabWidget;
    auto count = tabWidget->count();
    for (auto i = count - 1; i >= 0; i--)
    {
        auto text = tabWidget->tabText(i);
        if (texts.contains(text))
        {
            tabWidget->tabCloseRequested(i);
        }
    }
}

void MainWindow::removeItem(Item* item)
{
    closeItem(item);
    auto row = item->row();
    auto parent = item->parent();
    if (parent) parent->removeRow(row);
    else model->removeRow(row);
}

void MainWindow::saveItem(Item *item)
{
    auto type = item->itemType();
    if (type != ItemType::Folder)
    {
        Saver::Save(item);
    }
    if (type != ItemType::File)
    {
        auto count = item->rowCount();
        for (auto i = 0; i < count; i++)
        {
            auto child = item->child(i);
            auto childItem = static_cast<Item*>(child);
            saveItem(childItem);
        }
    }
}

void MainWindow::change()
{
    if (_scene == nullptr) return;
    _scene->isChanged = true;
    auto tabWidget = ui->tabWidget;
    auto index = tabWidget->currentIndex();
    auto oldText = tabWidget->tabText(index);
    if (!oldText.endsWith('*')) tabWidget->setTabText(index, oldText + '*');
}

void MainWindow::startWait()
{
    setCursor(Qt::WaitCursor);
    setEnabled(false);
}

void MainWindow::endWait()
{
    setCursor(Qt::ArrowCursor);
    setEnabled(true);
}

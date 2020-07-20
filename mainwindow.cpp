#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QToolBar>
#include <QPushButton>
#include <QComboBox>
#include <QColorDialog>
#include <QFontComboBox>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //工具栏
    ui->toolBar->addWidget(ui->backBtn);
    ui->toolBar->addWidget(ui->copyBtn);
    ui->toolBar->addWidget(ui->pasteBtn);

    ui->toolBar->addSeparator();

    QFontComboBox* fontBtn = new QFontComboBox(this);
    ui->toolBar->addWidget(fontBtn);

    ui->toolBar->addSeparator();

    QComboBox* fontSizeBtn = new QComboBox(this);
    fontSizeBtn->addItem("8");
    fontSizeBtn->addItem("10");
    ui->toolBar->addWidget(fontSizeBtn);

    ui->toolBar->addSeparator();

    QComboBox* fontColorBtn = new QComboBox(this);
    fontColorBtn->addItem("black");
    fontColorBtn->addItem("blue");
    ui->toolBar->addWidget(fontColorBtn);

    ui->toolBar->addSeparator();

     ui->toolBar->addWidget(ui->boldBtn);
     ui->toolBar->addWidget(ui->italicBtn);
     ui->toolBar->addWidget(ui->underlineBtn);


    //侧边栏
    connect(ui->bgColorBtn,&QPushButton::clicked,[](){
        QColorDialog::getColor(QColor(Qt::white));
    });
    connect(ui->bdColorBtn,&QPushButton::clicked,[](){
        QColorDialog::getColor(QColor(Qt::black));
    });
    connect(ui->arrowColorBtn,&QPushButton::clicked,[](){
        QColorDialog::getColor(QColor(Qt::black));
    });
    ui->arrowComboBox->addItem("实线");
    ui->arrowComboBox->addItem("虚线");




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


    _scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addRectangleButton_clicked()
{

}

void MainWindow::on_addDiamondButton_clicked()
{

}

void MainWindow::on_addArrowButton_clicked()
{

}

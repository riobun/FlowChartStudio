#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QToolBar>
#include <QPushButton>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton* backBtn = new QPushButton("back", this);
    ui->toolBar->addWidget(backBtn);
    QPushButton* copyBtn = new QPushButton("copy", this);
    ui->toolBar->addWidget(copyBtn);
    QPushButton* pasteBtn = new QPushButton("paste", this);
    ui->toolBar->addWidget(pasteBtn);

    QComboBox* fontBtn = new QComboBox(this);
    fontBtn->addItem("宋体");
    fontBtn->addItem("黑体");
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

    _scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene());
}

MainWindow::~MainWindow()
{
    delete ui;
}

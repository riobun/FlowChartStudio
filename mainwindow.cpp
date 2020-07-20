#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QToolBar>
#include <QPushButton>
#include <QComboBox>
#include <QColorDialog>
#include <QFontComboBox>
#include <QFontDialog>
#include <QToolButton>

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

    fontColorToolBtn = new QToolButton(this);
    fontColorToolBtn->setPopupMode(QToolButton::MenuButtonPopup);
    fontColorToolBtn->setMenu(createColorMenu(SLOT(textColorChanged()), Qt::black));
    textAction = fontColorToolBtn->menu()->defaultAction();
    fontColorToolBtn->setIcon(createColorToolButtonIcon(":/images/textpointer.png", Qt::black));
    fontColorToolBtn->setAutoFillBackground(true);
    ui->toolBar->addWidget(fontColorToolBtn);

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
    ui->arrowComboBox->addItem(" 实线");
    ui->arrowComboBox->addItem(" 虚线");




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

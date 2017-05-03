#include "mainwindow.h"
#include "myscene.h"

MainWindow::MainWindow() : QMainWindow(){
    // le widget dans lequel tout s'affiche
    widget_general = new QWidget;
    QHBoxLayout * qbl_general = new QHBoxLayout;
    widget_general->setLayout(qbl_general);
    this->setCentralWidget(widget_general);

    MyScene * myscene = new MyScene(this);
    myview=new QGraphicsView(myscene, this);
    qbl_general->addWidget(myview);

    myview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    myview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    myscene->setBackgroundBrush(QImage(":/mario/fond"));
}

MainWindow::~MainWindow(){

}


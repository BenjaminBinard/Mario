#include "mainwindow.h"
#include "myscene.h"
#include "menu.h"

MainWindow::MainWindow() : QMainWindow(){
    // le widget dans lequel tout s'affiche
    widget_general = new QWidget;
    QHBoxLayout * qbl_general = new QHBoxLayout;
    widget_general->setLayout(qbl_general);
    this->setCentralWidget(widget_general);

    //exemple de creation d'une zone ou mettre boutons...
    //qbl_general->addWidget(BuildGroupBoxControle());

    // exemple de création d'un menu
    menuFichier = menuBar()->addMenu(tr("&Fichier"));

    /*MyScene * myscene = new MyScene(this);
    myview=new QGraphicsView(myscene, this);
    qbl_general->addWidget(myview);*/
    menu * Menu = new menu(this);
    myview=new QGraphicsView(Menu, this);
    qbl_general->addWidget(myview);

    myview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    myview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //myscene->setBackgroundBrush(QImage(":/mario/fond"));
    Menu->setBackgroundBrush(QImage(":/mario/fond"));
}

MainWindow::~MainWindow(){

}


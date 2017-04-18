#include "menu.h"
#include<QPushButton>

menu::menu(QObject *parent):QGraphicsScene(parent){
    jouer = new QPushButton("Jouer", this);
    jouer->setGeometry(QRect(QPoint(100, 100),QSize(200, 50)));
    jouer->move(100,100);
    //this->addItem(jouer);
}


#ifndef MENU_H
#define MENU_H

#include<QWidget>
#include<QGraphicsScene>
#include<QGraphicsView>
#include <QPushButton>

class menu:public QGraphicsScene{
    Q_OBJECT
public:
    menu(QObject *parent=0);
public slots:
    void update();
private slots:
    void handleButton();
protected:
private:
    QPushButton *jouer;
};


#endif // MENU_H

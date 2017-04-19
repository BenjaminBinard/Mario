#ifndef MYSCENE_H
#define MYSCENE_H

#include<QWidget>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QGraphicsRectItem>
#include<QGraphicsTextItem>
#include<QTimer>
#include<QDebug>
#include<QGraphicsEllipseItem>
#include<QGraphicsLineItem>
#include<QPen>
#include<QKeyEvent>
#include<vector>
#include <iostream>
#include <stdlib.h>

#define MARIO 35*2
#define PIC 57*0.8
#define LONG_PLATE 60*2
#define LARG_PLATE 16*2
#define FLAG 128*0.3
#define SPAWN_X 25
#define NBR_PIC 30
#define VIE 5
#define PSEUDO_ALEA 1
#define NBR_PLATE 27

class MyScene:public QGraphicsScene{
    Q_OBJECT
public:
    MyScene(QObject *parent=0);
    std::vector<QGraphicsPixmapItem *> plateforme;
    std::vector<QGraphicsPixmapItem *> etat;
    std::vector<QGraphicsPixmapItem *> pic;
    void initialiser_jeu();
    void degat(int x, int y);
public slots:
    void update();
protected:
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
private:
    QTimer * timer;
    //QGraphicsRectItem * mario;
    //QGraphicsPixmapItem * pic;
    QGraphicsPixmapItem * flag;
    QGraphicsTextItem * gagne;
    QGraphicsTextItem * perdu;
    QGraphicsPixmapItem * mario;
    const int largeur;
    const int hauteur;
    int hauteur_max;
    int vitesse;
    int vie;
    int compteur;
    int pas;
    int pas_anneau;
    bool droite, gauche;
    bool on_descend_au_prochain_tour;
    bool sens_droite;
    bool on_descend;
    bool keyZ,keyD,keyQ;
};

#endif // MYSCENE_H


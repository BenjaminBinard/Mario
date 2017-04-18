#include "myscene.h"
#include<QPushButton>

MyScene::MyScene(QObject *parent):QGraphicsScene(parent), largeur(700), hauteur(500){

    //----- Creation fenetre -----
    QGraphicsRectItem * qgri = new QGraphicsRectItem(0,0,largeur,hauteur);
    qgri->setPen(QPen(Qt::black));
    this->addItem(qgri);

    //----- Creation Mario -----
    /*mario = new QGraphicsRectItem(0,0,MARIO,MARIO);
    mario->setBrush(QColor(139,0,0));
    mario->setPos(30, hauteur-MARIO);
    this->addItem(mario);*/
    compteur=0;
    on_descend=true;
    droite=true;
    gauche=true;
    vitesse=1;
    hauteur_max=100;
    pas=0;

    //----- Creation Tails -----
    mario = new  QGraphicsPixmapItem(QPixmap(":/mario/1D"));
    //mario->setBrush(QBrush(Qt::white));
    mario->opaqueArea();
    //mario->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    mario->setScale(2);
    mario->setOffset(0,0);
    mario->setPos(25, 200);
    this->addItem(mario);

    //----- Creation Pic -----
    pic = new QGraphicsPixmapItem(QPixmap(":/mario/pic"));
    //pic->setBrush(QBrush(QColor(159,232,85)));
    pic->setPos(210, 0);
    //pic->setScale(2);
    //pic->setTransformations();
    this->addItem(pic);

    //----- Creation Flag -----
    flag = new QGraphicsPixmapItem(QPixmap(":/mario/ring1"));
    //flag->setBrush(QBrush(QColor(159,272,85)));
    flag->setPos(430, hauteur-FLAG);
    flag->setScale(0.3);
    this->addItem(flag);
    pas_anneau=0;

    //----- Vecteur plateforme -----
    nbr_plate=4;// Nombre de plateforme
    for(int i=0; i<nbr_plate;i++){
        QGraphicsPixmapItem * plateforme1; //On créé autant d'objet que nécéssaire
        plateforme1 = new QGraphicsPixmapItem(QPixmap(":/mario/plate"));
        //plateforme1->setBrush(QBrush(QColor(159,232,85)));
        plateforme1->setScale(2);
        //plateforme1->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
        this->addItem(plateforme1);
        plateforme.push_back(plateforme1);//On ajoute cet objet au vecteur plateforme
    }
    plateforme.at(0)->setPos(150, 450);//On rentre manuellement la position. Plus tard l'idéal serait d'avoir un hasard.
    plateforme.at(1)->setPos(350, 380);
    plateforme.at(2)->setPos(450, 280);
    plateforme.at(3)->setPos(150, 200);

    //----- Creation Vie -----
    vie=5;
    for(int i=0;i<vie;i++){
        QGraphicsPixmapItem * coeur; //On créé autant d'objet que nécéssaire
        coeur = new  QGraphicsPixmapItem(QPixmap(":/mario/coeur"));
        //coeur->setBrush(QBrush(QColor(159,232,85)));
        this->addItem(coeur);
        coeur->setScale(0.05);
        etat.push_back(coeur);//On ajoute cet objet au vecteur plateforme
    }
    for(int j=0;j<vie;j++){
        //qDebug()<<vie;
        etat.at(j)->setPos(j*40,5);
    }

    //----- Textes -----

    gagne = new QGraphicsTextItem("gagne !");
    gagne->setScale(3);
    gagne->setDefaultTextColor(Qt::white);
    gagne->setVisible(false);
    gagne->setPos(0,0);
    this->addItem(gagne);

    perdu = new QGraphicsTextItem("Appuyer sur espace pour recommencer");
    perdu->setScale(3);
    perdu->setDefaultTextColor(Qt::white);
    perdu->setVisible(false);
    perdu->setPos(0,0);
    this->addItem(perdu);

    //----- Generation Timer -----
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(7);
}

void MyScene::update(){
    int x=mario->x();
    int y=mario->y();
    int xp;
    int yp;
    QList <QGraphicsView*> ListeView = this->views();
    ListeView.at(0)->centerOn(mario);
    //int longu=mario->
    //qDebug()<<"x : "<<x<<"et y : "<<y;
    bool ne_pas_rentrer=false;
    //----- Collision plateforme -----
    for(int i=0;i<nbr_plate;i++){
        xp=plateforme.at(i)->x();
        yp=plateforme.at(i)->y();

        if(plateforme.at(i)->collidesWithItem(mario)==true){
            if(x+MARIO>=xp && x+MARIO<=xp+4){
                //qDebug()<<"Hey, c'est un mur ca !";
                on_descend=true;
                droite=false;
            }
            if(x>=xp+LONG_PLATE){ // CA fonctionne, a garder
                on_descend=true;
                gauche=false;
            }
            qDebug()<<y<<yp+LARG_PLATE;
            if(y+8==yp+LARG_PLATE){ // On ne peut pas traverser les plafons
                on_descend=true;
                qDebug()<<"ECHOOOO";
            }else{
                on_descend=false;

                ne_pas_rentrer=true;
            }
        }
    }
    //----- Saut -----
    if(keyZ==true){
        //qDebug()<<compteur;
        if(compteur==hauteur_max && ne_pas_rentrer==false){// Le compteur gere le nombre d'iteration pour le saut (compteur_max)
            on_descend=true; // On et arrivé en haut de la courbe, on descend maintenant !
            compteur=0;//On reinitialise le compteur pour la prochaine fois
        }
        else if(on_descend==false){
            mario->setY(y-2*vitesse);//on monte de compteur_max*vitesse = pixels
            compteur++;
        }
        mario->setY(y-2*vitesse);
    }
    else if(ne_pas_rentrer==false){
        on_descend=true;
    }
    //----- Gestion de la vie -----
    if(mario->collidesWithItem(pic)==true){
        //qDebug()<<x-20<<x;
        on_descend=true;
        //mario->setPos(0,200);
        vie=vie-1;
        etat.at(vie)->setVisible(false);
        pic->setPos(0,0);
        pic->setVisible(false);
        if(vie==0){
            qDebug()<<"PERDU. Appuyer sur espace pour recommencer.";
            perdu->setVisible(true);
            timer->stop();
        }
    }
    //----- C'est Gagné ! -----
    if(mario->collidesWithItem(flag)==true){
        gagne->setVisible(true);
        timer->stop();
    }
    //----- Deplacements gauche et droite -----
    if(keyD && x<largeur-MARIO && droite==true){
        mario->setX(x+vitesse);// A gauche on se deplace
        gauche=true;//Si on avance, on se decolle du mur, donc on peux aller a gauche
        sens_droite=true;
        //mario->setPixmap(QPixmap(":/mario/1D"));
        //qDebug()<<pas;
    }
    if(keyQ && x>0 && gauche==true){
        mario->setX(x-vitesse);//A droite on se deplace
        sens_droite=false;
        droite=true;
        //mario->setPixmap(QPixmap(":/mario/1G"));
    }
    //---- Helicoptère -----
    if(pas<5){
        if(sens_droite==true)
            mario->setPixmap(QPixmap(":/mario/1D"));
        else
            mario->setPixmap(QPixmap(":/mario/1G"));
    }
    else if(pas>5 && pas<10){
        if(sens_droite==true)
            mario->setPixmap(QPixmap(":/mario/2D"));
        else
            mario->setPixmap(QPixmap(":/mario/2G"));
    }
    else if(pas>10){
        pas=0;
    }
    pas++;
    //----- Rotation Anneau -----
    if(pas_anneau<10)
        flag->setPixmap(QPixmap(":/mario/ring2"));
    else if(pas_anneau<20)
        flag->setPixmap(QPixmap(":/mario/ring3"));
    else if(pas_anneau<30)
        flag->setPixmap(QPixmap(":/mario/ring4"));
    else if(pas_anneau<40)
        flag->setPixmap(QPixmap(":/mario/ring1"));
    else
        pas_anneau=0;
    pas_anneau++;
    //----- Gravité -----
    if(on_descend_au_prochain_tour==true){
        on_descend=true;
        on_descend_au_prochain_tour=false;
    }
    if(on_descend==true){ // Du coup on descend
        if(y+vitesse>hauteur-MARIO){ // Mais on ne peux pas descendre plus bas que terre
            on_descend=false;
            compteur=0;
        }
        else{
            mario->setY(y+2*vitesse);
            gauche=true;
            droite=true;
        }
    }

}

void MyScene::keyPressEvent(QKeyEvent *event){
    int key = event->key();
    if(key==Qt::Key_Z){//Saut
        keyZ=true;
    }
    if(key==Qt::Key_D){
        keyD=true;
    }
    if(key==Qt::Key_Q ){
        keyQ=true;
    }
    if(key==Qt::Key_Space){
        qDebug()<<"On rejoue";
    }
}

void MyScene::keyReleaseEvent(QKeyEvent *event){
    int key = event->key();
    if(key==Qt::Key_Z){
        keyZ=false;
        on_descend=true;//On relache la touche de saut, donc on descend. Dependante du timer
    }
    if(key==Qt::Key_D){
        keyD=false;
    }
    if(key==Qt::Key_Q ){
        keyQ=false;
    }
}

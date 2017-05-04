#include "myscene.h"

MyScene::MyScene(QObject *parent):QGraphicsScene(parent), largeur(600), hauteur(1500){

    //----- Creation des boutons du menu -----

    jouer = new QPushButton("Jouer"); //Bouton pour lancer le jeu
    jouer->setGeometry(QRect(QPoint(100, 100),QSize(200, 50)));
    jouer->move(100,100);
    this->addWidget(jouer);
    connect(jouer, SIGNAL (released()),this, SLOT (btn_jouer()));

    quitter=new QPushButton("Retour"); //Bouton pour revenir sur le menu depuis l'aide
    quitter->setGeometry(QRect(QPoint(100, 100),QSize(200, 50)));
    quitter->move(100,400);
    quitter->setVisible(false);
    connect(quitter, SIGNAL (released()),this, SLOT (btn_quitter()));
    this->addWidget(quitter);

    aide=new QPushButton("Aide ?"); //Ouvrir l'aide
    aide->setGeometry(QRect(QPoint(100, 100),QSize(200, 50)));
    aide->move(100,200);
    connect(aide, SIGNAL (released()),this, SLOT (btn_aide()));
    this->addWidget(aide);

    //----- Creation Aide -----
    aide_image = new QGraphicsPixmapItem(QPixmap(":/mario/comment_jouer"));
    aide_image->setPos(0, 0);
    aide_image->setScale(0.8);
    aide_image->setVisible(false);
    this->addItem(aide_image);
    pas_anneau=0;

}

void MyScene::initialiser_jeu(){// On initialise le jeu (peu etre appelé autant de fois que nécéssaire)
    compteur=0;// Le nombre d'itérations du saut est mis/remis à 0
    on_descend=true; //La gravité est activée
    droite=true; //Mario à le droit d'aller à droite ou à gauche
    gauche=true;
    vitesse=2; // On definit sa vitesse
    hauteur_max=70; //La hauteur maximale du saut
    pas=0;
    mario->setPos(SPAWN_X, hauteur-(MARIO+50));// On met mario aux debut du parcour
    vie=VIE; //on initialise/réinitialise la vie
    for(int i=0;i<VIE;i++){
        etat.at(i)->setVisible(true);
    }
    int y1,x1;
    for(int i=0;i<NBR_PIC;i++){ //On distribue de manière purement aléatoire les pics
        y1 = rand() % (hauteur);
        x1 = rand() % (largeur);
        pic.at(i)->setPos(x1,y1);
        pic.at(i)->setVisible(true);
    }
    for(int i=0;i<NBR_PLATE;i++){// On rend visible les plateformes et autre
        plateforme.at(i)->setVisible(true);
    }
    mario->setVisible(true);
    flag->setVisible(true);
    timer->start(7);// On lance le jeu
}

void MyScene::pre_init(){// Pre initialisation du jeu, est lancée une seule fois

    //----- Creation Tails -----
    mario = new  QGraphicsPixmapItem(QPixmap(":/mario/1D"));
    mario->opaqueArea();
    mario->setScale(2);
    mario->setOffset(0,0);
    this->addItem(mario);

    //----- Creation Pic -----
    for(int i=0; i<NBR_PIC;i++){
        QGraphicsPixmapItem * pic1; //On créé autant d'objet que nécéssaire
        pic1 = new QGraphicsPixmapItem(QPixmap(":/mario/pic"));
        pic1->setScale(0.8);
        this->addItem(pic1);
        pic.push_back(pic1);//On ajoute cet objet au vecteur plateforme
    }

    //----- Creation Flag -----
    flag = new QGraphicsPixmapItem(QPixmap(":/mario/ring1"));
    flag->setPos(430, FLAG);
    flag->setScale(0.3);
    this->addItem(flag);
    pas_anneau=0;

    //----- Vecteur plateforme -----
    for(int i=0; i<NBR_PLATE;i++){
        QGraphicsPixmapItem * plateforme1; //On créé autant d'objet que nécéssaire
        plateforme1 = new QGraphicsPixmapItem(QPixmap(":/mario/plate"));
        plateforme1->setScale(2);
        this->addItem(plateforme1);
        plateforme.push_back(plateforme1);//On ajoute cet objet au vecteur plateforme
    }
    plateforme.at(0)->setPos(50, hauteur-50);
    if(PSEUDO_ALEA==0){
        plateforme.at(4)->setPos(150, hauteur-100);
        plateforme.at(5)->setPos(250, hauteur-170);
        plateforme.at(6)->setPos(350, hauteur-240);
        plateforme.at(1)->setPos(450, hauteur-310);
        plateforme.at(2)->setPos(490, hauteur-380);
        plateforme.at(3)->setPos(450, hauteur-450);

    }else if(PSEUDO_ALEA==1){ // C'est moins long et moins fastidieux avec cette méthode
        //(à noter que ce n'est pas pseudo aléatoire mais totalement aléatoire)
        int x1, y1;
        for(int i=1; i<NBR_PLATE;i++){
            x1=rand()%(largeur);
            y1=rand()%(hauteur);
            plateforme.at(i)->setPos(x1, y1);
        }
    }

    //----- Creation Vie -----
    vie=VIE;
    for(int i=0;i<vie;i++){
        QGraphicsPixmapItem * coeur; //On créé autant d'objet que nécéssaire
        coeur = new  QGraphicsPixmapItem(QPixmap(":/mario/coeur"));
        this->addItem(coeur);
        coeur->setScale(0.03);
        etat.push_back(coeur);//On ajoute cet objet au vecteur etat
    }

    //----- Perdu et gagné -----

    gagne = new  QGraphicsPixmapItem(QPixmap(":/mario/gagne"));
    gagne->setScale(0.7);
    gagne->setVisible(false);
    gagne->setPos(0,0);
    this->addItem(gagne);

    perdu = new  QGraphicsPixmapItem(QPixmap(":/mario/perdu"));
    perdu->setScale(0.7);
    perdu->setVisible(false);
    perdu->setPos(0,0);
    this->addItem(perdu);

    recommencer=new QPushButton("Recommencer"); //Création du bouton recommencer
    recommencer->setGeometry(QRect(QPoint(100, 100),QSize(200, 50)));
    recommencer->move(100,200);
    recommencer->setVisible(false);
    connect(recommencer, SIGNAL (released()),this, SLOT (btn_recommencer()));
    this->addWidget(recommencer);

    //----- Generation Timer -----
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

}

void MyScene::btn_jouer(){ //Lorsque l'utilisateur lance le jeu
    quitter->setVisible(false);
    jouer->setVisible(false);
    aide->setVisible(false);
    pre_init();
    initialiser_jeu();
}

void MyScene::btn_aide(){// Lorsque l'utilisateur regarde l'aide
    aide_image->setVisible(true);
    quitter->setVisible(true);
}

void MyScene::btn_quitter(){// Puis quitte cette aide
    aide_image->setVisible(false);
    quitter->setVisible(false);
}

void MyScene::btn_recommencer(){// On reinitialise le jeu
    recommencer->setVisible(false);
    perdu->setVisible(false);
    initialiser_jeu();
}

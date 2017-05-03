#include "myscene.h"

void MyScene::update(){
    int x=mario->x();
    int y=mario->y();
    int xp;
    int yp;

    //----- Gestion de la vue -----
    QList <QGraphicsView*> ListeView = this->views();
    ListeView.at(0)->centerOn(mario);

    bool ne_pas_rentrer=false; //Sous entendu "ne pas rentrer dans la fonction update la prochaine fois"

    //----- Collision plateforme -----
    for(int i=0;i<NBR_PLATE;i++){
        xp=plateforme.at(i)->x();
        yp=plateforme.at(i)->y();

        if(plateforme.at(i)->collidesWithItem(mario)==true){
            if(x+MARIO>=xp && x+MARIO<=xp+4){// Si on n'est plus sur la plateforme
                on_descend=true;// Alors on active la gravité
                droite=false;
            }
            if(x>=xp+LONG_PLATE){ //
                on_descend=true;
                gauche=false;
            }
            if(y+8>=yp+LARG_PLATE){ // On ne peut pas traverser les plafons
                on_descend=true;
            }else{
                on_descend=false;
                compteur=0;
                ne_pas_rentrer=true;
            }
        }
    }
    //----- Saut -----
    if(keyZ==true){
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

    //----- Affichage de la vie -----
    for(int j=0;j<vie;j++){
        etat.at(j)->setPos((j*27)+x-10,y-50);
    }
    //----- Gestion de la vie -----
    for(int i=0; i<NBR_PIC;i++){
        if(mario->collidesWithItem(pic.at(i))==true){
            on_descend=true;
            pic.at(i)->setPos(0,0);//On enleve le pic et le rend invisible sans le desinstencier
            pic.at(i)->setVisible(false);
            degat(x,y,ListeView);// Mario perd 1 coeur
        }
    }

    //----- C'est Gagné ! -----
    if(mario->collidesWithItem(flag)==true){
        qDebug()<<"gagné. Appuyer sur espace pour recommencer.";
        gagne->setPos(x-(LONG_FRAME*0.7/2),y-(LARG_FRAME*0.7/2));// On essaye de mettre le plus au centre de la fenetre possible
        gagne->setVisible(true);
        recommencer->setVisible(true);
        recommencer->move(x-(200/2)+20,y+(50/2));//Meme chose pour le bouton recommencer
        for(int i=0;i<NBR_PIC;i++){ // On rend invisble tout le reste
            pic.at(i)->setVisible(false);
        }
        for(int i=0;i<NBR_PLATE;i++){
            plateforme.at(i)->setVisible(false);
        }
        mario->setVisible(false);
        flag->setVisible(false);
        timer->stop();
        timer->stop();
    }
    //----- Deplacements gauche et droite -----
    if(keyD && droite==true){
        mario->setX(x+vitesse);// A gauche on se deplace
        gauche=true;//Si on avance, on se decolle du mur, donc on peux aller a gauche
        sens_droite=true;
    }
    if(keyQ && gauche==true){
        mario->setX(x-vitesse);//A droite on se deplace
        sens_droite=false;
        droite=true;
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
            mario->setPos(SPAWN_X,hauteur-(MARIO+LARG_PLATE));
            degat(x,y, ListeView);
        }
        else{
            mario->setY(y+2*vitesse);
            gauche=true;
            droite=true;
        }
    }
}

#include "myscene.h"

void MyScene::degat(int x, int y){ //Permet de faire perdre 1 coeur à Tail
    vie--;
    etat.at(vie)->setVisible(false);
    if(vie==0){
        qDebug()<<"PERDU. Appuyer sur espace pour recommencer.";
        perdu->setPos(x-(LONG_FRAME*0.7/2),y-(LARG_FRAME*0.7/2));
        perdu->setVisible(true);
        recommencer->setVisible(true);
        recommencer->move(x-(200/2)+20,y+(50/2));
        for(int i=0;i<NBR_PIC;i++){
            pic.at(i)->setVisible(false);
        }
        for(int i=0;i<NBR_PLATE;i++){
            plateforme.at(i)->setVisible(false);
        }
        mario->setVisible(false);
        flag->setVisible(false);
        timer->stop();
    }
}

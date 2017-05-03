#include "myscene.h"

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
        initialiser_jeu();
    }
}

void MyScene::keyReleaseEvent(QKeyEvent *event){
    int key = event->key();
    if(key==Qt::Key_Z){
        keyZ=false;
        on_descend=true;//On relache la touche de saut, donc on descend. Dependante au timer
    }
    if(key==Qt::Key_D){
        keyD=false;
    }
    if(key==Qt::Key_Q ){
        keyQ=false;
    }
}

#include "gui_glut/gui.h"

void display() {
    GUI::displayInit();

    GUI::setLight(0,0,2,0,true);

    GUI::setColor(0.8,0.2,0.2,1.0,true);
    GUI::drawFloor(5.0,5.0,0.5,0.5);

    GUI::setColor(0.5,0.5,0.5);
    GUI::drawQuadBox(-3,0.2,-3,3,3,3,0.03,0.03,true);

    GUI::displayEnd();
}

void key(unsigned char key, int x, int y) {
    GUI::keyInit(key,x,y);
}

int main() {
    GUI gui(800,600,display,key);
}



//int main() {
//    int cont = 0;
//    while (true) {

//        displayTeste();
//        interacaoUsuario();


//        cont ++;
//        if (cont>1000000000) {
//            break;
//        }
//    }


//    GUI gui(800,600,displayTeste);
//}

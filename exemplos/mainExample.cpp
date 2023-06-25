#include <iostream>

using namespace std;

#include "gui_glut/gui.h"

float px = 0.0;

void desenha() {
    GUI::displayInit();

    GUI::setLight(0,0.0,2.0,0.0);

    GUI::setColor(1.0,0.0,0.0);
    GUI::drawFloor();

    GUI::setColor(0.0,1.0,0.0);
    GUI::drawSphere(px,0.2,0.0,0.2);

    //px += 0.01;
    if (px>2.0) {
        px = -2.0;
    }

    GUI::displayEnd();
}

void key(unsigned char k, int x, int y) {
    GUI::keyInit(k,x,y);

    switch (k) {
    case 'J':
        px += 0.1;
        break;
    case 'j':
        px -= 0.1;
        break;
    }
}

int main()
{
    cout << "Hello World!" << endl;

    GUI gui(800,600,desenha,key);
}


//while(true) {
//    desenha();
//    key();
//}

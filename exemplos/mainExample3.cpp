#include <iostream>

using namespace std;

#include <gui.h>
#include <vector>

Model3DS modeloCarro = Model3DS("../3ds/cartest.3DS");

class Carrinho {
public:
    float x = 0;
    float z = 0;

    float angY = 45;
    float speed = 0.001;

    Model3DS* model = &modeloCarro;

    //Carrinho() {
    //};
    Carrinho(float x) {
        this->x = x;
    };
    //~Carrinho() {
    //};


    void atualiza() {
        x += speed*cos(angY*(PI/180.0));
        z -= speed*sin(angY*(PI/180.0));
    }

    void desenha() {
        GUI::draw3ds(*model,x,0,z,0,90+angY,0);
    }
};

float px = 2.0;
float py = 1.5;


//Carrinho carrinho;
vector<Carrinho> carros;
int nCarros = 10;

void desenha() {
    GUI::displayInit();

    GUI::setLight(1,0,3,0,true,false);

    GUI::drawOrigin(1);

    GUI::setColor(1,0,0);
    GUI::drawFloor();

    GUI::setColor(0,1,0);
    GUI::drawSphere(px,py,0,0.2);
    //px += 0.01;

    GUI::setColor(0,0,1);
    GUI::drawSphere(glutGUI::tx,glutGUI::ty,glutGUI::tz,0.2);

    //GUI::draw3ds(modeloCarro,0,0,0,0,45,0);
    //    float s = 0.001;
    //    glPushMatrix();
    //        //glTranslatef(0,2,-1000);
    //        glRotatef(-90,1,0,0);
    //        glScalef(s,s,s);
    //        modeloCarro.draw();
    //    glPopMatrix();

    //carrinho.atualiza();
    //carrinho.desenha();
    for (int i = 0; i < carros.size(); ++i) {
        carros[i].atualiza();
        carros[i].desenha();
    }

    GUI::displayEnd();
}

int sel = 0;

void teclado(unsigned char key, int x, int y) {
    GUI::keyInit(key,x,y);

    switch (key) {
    case 'J':
        px += 0.1;
        break;
    case 'j':
        px -= 0.1;
        break;
    case 'K':
        py += 0.1;
        break;
    case 'k':
        py -= 0.1;
        break;

    case 'b':
        sel += 1;
        sel = sel%nCarros;
        break;

    //case 'a':
    //    carrinho.angY += 5;
    //    break;
    //case 'd':
    //    carrinho.angY -= 5;
    //    break;
    //case 'w':
    //    carrinho.speed += 0.001;
    //    break;
    //case 's':
    //    carrinho.speed -= 0.001;
    //    break;
    case 'a':
        carros[sel].angY += 5;
        break;
    case 'd':
        carros[sel].angY -= 5;
        break;
    case 'w':
        carros[sel].speed += 0.001;
        break;
    case 's':
        carros[sel].speed -= 0.001;
        break;

    case 't':
        glutGUI::trans_obj = !glutGUI::trans_obj;
        break;
    case 'l':
        glutGUI::trans_luz = !glutGUI::trans_luz;
        break;
    default:
        break;
    }
}

int main()
{
    cout << "Hello World!" << endl;

    for (int i = 0; i < nCarros; ++i) {
        carros.push_back(Carrinho(i-nCarros/2));
    }

    GUI gui = GUI(800,600,desenha,teclado);
}


//while(true) {
//    desenha();
//    interacaoUsuario();
//}

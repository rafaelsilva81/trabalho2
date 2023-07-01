
#include <iostream>

using namespace std;

#include <vector>
#include <gui.h>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sstream>

// Objeto base
#include "Objeto.h"

// Objetos criados
#include "Balcao.h"
#include "Mesa.h"
#include "Prateleira.h"
#include "Palco.h"
#include "Parede.h" // Não iterativo

// Objetos importados do .3DS
#include "Tamborete.h"
#include "Barril.h"
#include "Caneca.h"
#include "Armario.h"
#include "Microfone.h"

// Objetos inclinados
#include "Cobertura.h"

// Cameras
#include "CameraJogo.h"
#include "CameraDistante.h"
#include "Camera.h"

#include "bib/json.hpp"

using json = nlohmann::json;

int current_object_id = 0;
int max_object_id = -1;

vector<Objeto *> objetos;

// Indica se o usuário está no "modo de seleção" de objetos
bool selecting_state = false;

//-------------------sombra-------------------
bool shadowsWalls = false;
bool drawShadow = false;
bool lightMode = true;
float k = -0.01;

// ------------ picking -----------------------
size_t selectedPoint = 0;

//-------------------viewPorts------------------
bool viewports = false;

void transformObjects()
{

  if ((selectedPoint != 0 and selectedPoint <= objetos.size()))
  {
    // Translações
    objetos[selectedPoint - 1]->trans_x += 10 * glutGUI::dtx;
    objetos[selectedPoint - 1]->trans_y += 10 * glutGUI::dty;
    objetos[selectedPoint - 1]->trans_z += 10 * glutGUI::dtz;

    // Rotações
    objetos[selectedPoint - 1]->rot_x += 10 * glutGUI::dax;
    objetos[selectedPoint - 1]->rot_y += 10 * glutGUI::day;
    objetos[selectedPoint - 1]->rot_z += 10 * glutGUI::daz;

    // Escalas
    objetos[selectedPoint - 1]->scale_x += 10 * glutGUI::dsx;
    objetos[selectedPoint - 1]->scale_y += 10 * glutGUI::dsy;
    objetos[selectedPoint - 1]->scale_z += 10 * glutGUI::dsz;
  }
}

int giveId()
{
  /*  cout << "Atribuindo id:" + to_string(max_object_id) << endl; */
  max_object_id = +1;
  return max_object_id;
}

void readSave()
{

  // Balcao, armario e prateleira no fundo
  Balcao *balcao = new Balcao(giveId(), -0.8, 0.0, -3, 0., 360., 0., 1., 1., 1., false, false);

  Armario *armario_fundo = new Armario(giveId(), -3.0, 0.0, -4.4, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false);
  Barril *barril_armario_fundo_1 = new Barril(giveId(), -3.0, 0.1, -4.4, 0., 0., 0., 1., 1., 1., false, false);

  Prateleira *prateleira_fundo = new Prateleira(giveId(), -1., 2.2, -4.6, 0., 0., 0., 1., 1., 1., false, false);
  Caneca *caneca_prateleira_fundo_1 = new Caneca(giveId(), -0.5, 2.4, -4.6, 0., 180., 0., 1., 1., 1., false, false);

  Tamborete *tamborete_balcao_1 = new Tamborete(giveId(), -3.1, 0.0, -2.2, 0., 0., 0., 1., 1., 1., false, false); // demora
  Caneca *caneca_balcao_1 = new Caneca(giveId(), -3.1, 1, -3, 0., 10, 0., 1., 1., 1., false, false);

  Mesa *mesa_1 = new Mesa(giveId(), 3.0, 0.0, 2.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false);
  Tamborete *tamborete_1_mesa_1 = new Tamborete(giveId(), 2.3, 0.0, 2.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false);
  Tamborete *tamborete_2_mesa_1 = new Tamborete(giveId(), 3.8, 0.0, 2.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false);
  Caneca *caneca_1_mesa_1 = new Caneca(giveId(), 3.1, 1, 2.1, 0.0, 90.0, 0.0, 1.0, 1.0, 1.0, false, false);
  Caneca *caneca_2_mesa_1 = new Caneca(giveId(), 2.8, 1, 2, 0.0, -90.0, 0.0, 1.0, 1.0, 1.0, false, false);

  Mesa *mesa_2 = new Mesa(giveId(), -2.5, 0.0, 0.5, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false);
  Tamborete *tamborete_1_mesa_2 = new Tamborete(giveId(), -3.2, 0.0, 0.5, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false);
  Caneca *caneca_1_mesa_2 = new Caneca(giveId(), -2.8, 1, 0.6, 0.0, -84.0, 0.0, 1.0, 1.0, 1.0, false, false);

  objetos.push_back(balcao);

  objetos.push_back(armario_fundo);
  objetos.push_back(barril_armario_fundo_1);

  objetos.push_back(prateleira_fundo);
  /* objetos.push_back(caneca_prateleira_fundo_1); */

  /* objetos.push_back(tamborete_balcao_1); */

  /* objetos.push_back(caneca_balcao_1); */

  objetos.push_back(mesa_1);
  objetos.push_back(tamborete_1_mesa_1);
  /* objetos.push_back(tamborete_2_mesa_1); */
  /* objetos.push_back(caneca_1_mesa_1); */
  /* objetos.push_back(caneca_2_mesa_1); */

  objetos.push_back(mesa_2);
  objetos.push_back(tamborete_1_mesa_2);
  /* objetos.push_back(caneca_1_mesa_2); */
}

void teclado(unsigned char tecla, int mouseX, int mouseY)
{
  GUI::keyInit(tecla, mouseX, mouseY);

  switch (tecla)
  {
  // ------------------------- TECLAS: sombra -------------------------
  case 's':
    // Sombra
    if (selecting_state)
    {
      drawShadow = !drawShadow;
    }
    break;
  case 't':
    // mostra sombras em planos arbitrários(parede, chão, plano inclinado)
    shadowsWalls = !shadowsWalls;
    break;
  case 'i':
    // Troca entre luz pontual próxima e luz distante
    lightMode = !lightMode;
    break;
  // ------------------------- TECLAS: legado -------------------------
  case 'p':
    /*  objetos[current_object_id]->selected = false;
     // Alterar o modo de seleção
     selecting_state = !selecting_state;

     // Atualizar o objeto selecionado
     current_object_id = 0;
     if (selecting_state)
     {
       objetos[current_object_id]->selected = true;
     }
     break; */
    glutGUI::trans_obj = !glutGUI::trans_obj;
    break;
  case 'r':
    glutGUI::trans_obj = !glutGUI::trans_obj;
    break;
  case 'l':
    glutGUI::trans_luz = !glutGUI::trans_luz;
    break;
  // ------------------------- TECLAS: viewports/persectiva -------------------------
  case 'v':
    viewports = !viewports;
    break;
  case '1':
    // Perpectiva: 1 ponto de fuga
    glutGUI::cam->e.x = 1.5;
    glutGUI::cam->e.y = -0.25;
    glutGUI::cam->e.z = 0;
    glutGUI::cam->c.x = 0;
    glutGUI::cam->c.y = 1;
    glutGUI::cam->c.z = 0;
    glutGUI::cam->u.x = 0;
    glutGUI::cam->u.y = 1;
    glutGUI::cam->u.z = 0;
    break;
  case '2':
    // Perpectiva: 2 pontos de fuga
    glutGUI::cam->e.x = 1.25;
    glutGUI::cam->e.y = 0.5;
    glutGUI::cam->e.z = -1.25;
    glutGUI::cam->c.x = 0;
    glutGUI::cam->c.y = 1;
    glutGUI::cam->c.z = 0;
    glutGUI::cam->u.x = 0;
    glutGUI::cam->u.y = 1;
    glutGUI::cam->u.z = 0;
    break;
  case '3':
    // Perpectiva: 3 pontos de fuga
    glutGUI::cam->e.x = 1.5;
    glutGUI::cam->e.y = -0.25;
    glutGUI::cam->e.z = 1.5;
    glutGUI::cam->c.x = 0;
    glutGUI::cam->c.y = 1;
    glutGUI::cam->c.z = 0;
    glutGUI::cam->u.x = 0;
    glutGUI::cam->u.y = 1;
    glutGUI::cam->u.z = 0;
    break;
  case '4':
    // Ortográfica(vista): Frontal
    glutGUI::cam->e.x = 0;
    glutGUI::cam->e.y = 0.5;
    glutGUI::cam->e.z = 2;
    glutGUI::cam->c.x = 0;
    glutGUI::cam->c.y = 0.5;
    glutGUI::cam->c.z = 0;
    glutGUI::cam->u.x = 0;
    glutGUI::cam->u.y = 1;
    glutGUI::cam->u.z = 0;
    break;
  case '5':
    // Ortográfica(vista): Lateral
    glutGUI::cam->e.x = 2;
    glutGUI::cam->e.y = 0.5;
    glutGUI::cam->e.z = 0;
    glutGUI::cam->c.x = 0;
    glutGUI::cam->c.y = 0.5;
    glutGUI::cam->c.z = 0;
    glutGUI::cam->u.x = 0;
    glutGUI::cam->u.y = 1;
    glutGUI::cam->u.z = 0;
    break;
  case '6':
    // Ortográfica(vista): Planta
    glutGUI::cam->e.x = 0;
    glutGUI::cam->e.y = 4;
    glutGUI::cam->e.z = 0;
    glutGUI::cam->c.x = 0;
    glutGUI::cam->c.y = 0;
    glutGUI::cam->c.z = 0;
    glutGUI::cam->u.x = 0;
    glutGUI::cam->u.y = 0;
    glutGUI::cam->u.z = -1;
    break;
  case '7':
    // Ortográfica(axonométrica): Isométrica
    glutGUI::cam->e.x = 3;
    glutGUI::cam->e.y = 2;
    glutGUI::cam->e.z = 3;
    glutGUI::cam->c.x = 0;
    glutGUI::cam->c.y = 1;
    glutGUI::cam->c.z = 0;
    glutGUI::cam->u.x = 0;
    glutGUI::cam->u.y = 1;
    glutGUI::cam->u.z = 0;
    break;
  case '8':
    // Ortográfica(axonométrica): Dimétrica
    glutGUI::cam->e.x = 3;
    glutGUI::cam->e.y = 1;
    glutGUI::cam->e.z = 3;
    glutGUI::cam->c.x = 0;
    glutGUI::cam->c.y = 1;
    glutGUI::cam->c.z = 0;
    glutGUI::cam->u.x = 0;
    glutGUI::cam->u.y = 1;
    glutGUI::cam->u.z = 0;
    break;
  case '9':
    // Ortográfica(axonométrica): Trimétrica
    glutGUI::cam->e.x = 3;
    glutGUI::cam->e.y = 1;
    glutGUI::cam->e.z = 2.5;
    glutGUI::cam->c.x = 0;
    glutGUI::cam->c.y = 1;
    glutGUI::cam->c.z = 0;
    glutGUI::cam->u.x = 0;
    glutGUI::cam->u.y = 1;
    glutGUI::cam->u.z = 0;
    break;
  case 'o':
    glutGUI::perspective = !glutGUI::perspective;
    break;
  default:
    break;
  }
}

void montarCena()
{

  // GUI::setLight(0,  3,5,4, true,false);//(tecla de apagar, x,y,z , desligar e ligar luz, (false = forte, true = atenuada))

  GUI::setColor(0.0118, 0.7333, 0.5216, 1, true); //(red,green,blue,opacidade,componente_de_reflexão)

  glPushMatrix();
  //-------------------sombra-------------------
  glTranslated(0.0, k, 0.0); // glTranslated(0.0,k-0.001,0.0);
  GUI::setColor(0.8, 0.8, 0.8, 1, true);
  GUI::drawFloor(10, 10, 3, 0.1); //(largura, comprimento, vertices largura, vertices comprimento)
  //-------------------sombra-------------------
  glPopMatrix();

  for (int i = 0; i < objetos.size(); ++i)
  {
    glPushMatrix();
    objetos[i]->desenha();
    glPopMatrix();
  }

  //-------------------sombra-------------------
  // definindo a luz que sera usada para gerar a sombra
  float lightPos[4] = {1.5f + glutGUI::lx, 1.5f + glutGUI::ly, 1.5f + glutGUI::lz, lightMode};
  // GUI::setLight(0,lightPos[0],lightPos[1],lightPos[2],true,false,false,false,pontual);
  GUI::setLight(0, 3, 5, 4, true, false, false, false, lightMode);
  // desenhando os objetos projetados
  glPushMatrix();

  GLfloat sombra[4][4];
  GUI::shadowMatrixYk(sombra, lightPos, k);

  glMultTransposeMatrixf((GLfloat *)sombra);

  glDisable(GL_LIGHTING);
  glColor3d(0.0, 0.0, 0.0);
  if (drawShadow)
  {
    bool aux = glutGUI::draw_eixos;
    glutGUI::draw_eixos = false;
    glPushMatrix();
    objetos[current_object_id]->desenha();
    glPopMatrix();
    glutGUI::draw_eixos = aux;
  }
  glEnable(GL_LIGHTING);
  glPopMatrix();
  //-------------------sombra-------------------
}

// TODO: Mudar nome
void sombraPlano(GLfloat plano[4], float lightPos[4])
{
  bool aux = glutGUI::draw_eixos;
  glutGUI::draw_eixos = false;

  for (size_t i = 0; i < objetos.size(); i++)
  {
    glDisable(GL_LIGHTING);
    glColor4d(0.0, 0.0, 0.0, 0.5);

    GLfloat sombra[4][4];

    glPushMatrix();
    GUI::shadowMatrix(sombra, plano, lightPos);
    glMultTransposeMatrixf((GLfloat *)sombra);
    objetos[current_object_id]->desenha();
    glEnable(GL_LIGHTING);
    glPopMatrix();
  }
}

void sombraParede()
{
  float lightM = lightMode ? 1.0f : 0.0f;
  float lightPos[4] = {glutGUI::lx, glutGUI::ly, glutGUI::lz, lightM};

  GUI::setLight(0, lightPos[0], lightPos[1], lightPos[2], true, false, false, false, lightMode);
  GLfloat chao[4] = {0, 1, 0, -0.001};
  sombraPlano(chao, lightPos);

  GUI::setColor(1, 0.98, 0.98);
  glPushMatrix();
  GUI::drawBox(-5, 0, -5, -4.8, 5, 5);
  glPopMatrix();
  GLfloat paredeEsquerda[4] = {0.63, 0, 0, 3.00 - 0.001};
  sombraPlano(paredeEsquerda, lightPos);

  GUI::setColor(1, 0.98, 0.98);
  glPushMatrix();
  GUI::drawBox(-4.8, 0, -5, 5, 5, -4.8);
  glPopMatrix();
  GLfloat paredeTras[4] = {0, 0, 0.63, 3.00 - 0.001};
  sombraPlano(paredeTras, lightPos);

  GUI::setColor(1, 0.98, 0.98);
  glPushMatrix();
  glTranslatef(-4.04, 0, -2.5);
  glRotatef(-45, 0, 0, 1);
  GUI::drawQuad(2, 5);
  glPopMatrix();
  GLfloat rampa[4] = {0.63, 0.63, 0, 2.54 - 0.001};
  sombraPlano(rampa, lightPos);
}

void drawViewports()
{
  GUI::displayInit();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glViewport(0, 0, glutGUI::width / 2, glutGUI::height / 2);
  gluLookAt(glutGUI::cam->e.x, glutGUI::cam->e.y, glutGUI::cam->e.z, glutGUI::cam->c.x, glutGUI::cam->c.y, glutGUI::cam->c.z, glutGUI::cam->u.x, glutGUI::cam->u.y, glutGUI::cam->u.z);
  montarCena();

  glLoadIdentity();
  glViewport(0, glutGUI::height / 2, glutGUI::width / 2, glutGUI::height / 2);
  gluLookAt(0, 10, 0, 0, 0, 0, 0, 0, 1);
  montarCena();

  glLoadIdentity();
  glViewport(glutGUI::width / 2, 0, glutGUI::width / 2, glutGUI::height / 2);
  gluLookAt(0, 1, -10, 0, 1, 0, 0, 1, 0);
  montarCena();

  glLoadIdentity();
  glViewport(glutGUI::width / 2, glutGUI::height / 2, glutGUI::width / 2, glutGUI::height / 2);
  gluLookAt(10, 1, 0, 0, 1, 0, 0, 1, 0);
  montarCena();
}

void desenha()
{
  GUI::displayInit();

  glClearColor(0.53, 0.81, 0.92, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  if (!viewports)
  {
    montarCena();
  }
  else
  {
    drawViewports();
  }

  // TODO: Alterar nomes
  if (shadowsWalls)
  {
    sombraParede();
  }

  transformObjects();

  GUI::displayEnd();
}

void desenhaPontosDeControle()
{
  for (size_t i = 0; i < objetos.size(); i++)
  {
    cout << "desenhando objeto " << i << endl;
    glPushName(i + 1);
    objetos[i]->desenha();
    glPopName();
  }
}

int picking(GLint cursorX, GLint cursorY, int w, int h)
{
  int BUFSIZE = 512;
  GLuint selectBuf[512];
  GUI::pickingInit(cursorX, cursorY, w, h, selectBuf, BUFSIZE);
  GUI::displayInit();
  objetos[current_object_id]->selected = false;
  desenhaPontosDeControle();
  return GUI::pickingClosestName(selectBuf, BUFSIZE);
}

void mouse(int button, int state, int x, int y)
{
  GUI::mouseButtonInit(button, state, x, y);

  // if the left button is pressed
  if (button == GLUT_LEFT_BUTTON)
  {
    // when the button is pressed
    if (state == GLUT_DOWN)
    {
      // picking
      int pick = picking(x, y, 5, 5);
      if (pick != 0)
      {
        selecting_state = true;
        selectedPoint = pick;
        objetos[selectedPoint - 1]->selected = true;
        selectedPoint = selectedPoint - 1;
        glutGUI::lbpressed = false;
      }
      else
      {
        selecting_state = false;
      }
    }
  }
}

int main(int argc, char *argv[])
{
  readSave();
  // GUI gui(800,600); // (largura, altura)
  GUI gui = GUI(800, 600, desenha, teclado, mouse);
  // TODO: GUI gui = GUI(800, 600, desenha, teclado, mouse);
  // GUI gui2 = GUI(500, 200, desenha2);
}

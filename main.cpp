
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

// Paredes (não serão objetos interativos)
Parede *paredeLeft = new Parede(1, -5., 0., 0., 0., 270., 0., 1., 1., 1., false, false);
Parede *paredeBack = new Parede(1, 0., 0., -5., 0., 180., 0., 1., 1., 1., false, false);

int current_object_id = 0;
int max_object_id = -1;

vector<Objeto *> objetos;

// Indica se o usuário está no "modo de seleção" de objetos
bool selecting_state = false;

// Indica a camera
int camera_presets = 0;

std::ofstream myfile;

//-------------------sombra-------------------
bool sombras_planos = false;
bool drawShadow = false;
bool tipo_luz = true;
float k = 0.0;

// ------------ picking -----------------------
size_t pontoSelecionado = 0;

//-------------------viewPorts------------------
bool viewports = false;
bool scissored = false;

void transformObjects()
{

  if ((pontoSelecionado != 0 and pontoSelecionado <= objetos.size()))
  {
    // Translações
    objetos[pontoSelecionado - 1]->trans_x += 10 * glutGUI::dtx;
    objetos[pontoSelecionado - 1]->trans_y += 10 * glutGUI::dty;
    objetos[pontoSelecionado - 1]->trans_z += 10 * glutGUI::dtz;

    // Rotações
    objetos[pontoSelecionado - 1]->rot_x += 10 * glutGUI::dax;
    objetos[pontoSelecionado - 1]->rot_y += 10 * glutGUI::day;
    objetos[pontoSelecionado - 1]->rot_z += 10 * glutGUI::daz;

    // Escalas
    objetos[pontoSelecionado - 1]->scale_x += 10 * glutGUI::dsx;
    objetos[pontoSelecionado - 1]->scale_y += 10 * glutGUI::dsy;
    objetos[pontoSelecionado - 1]->scale_z += 10 * glutGUI::dsz;
  }
}

int giveId()
{
  /*  cout << "Atribuindo id:" + to_string(max_object_id) << endl; */
  max_object_id = +1;
  return max_object_id;
}

void saveScene()
{
  // Pegar todos os objetos, e salvar no arquivo save

  std::ifstream f("save.json");

  // Limpar o arquivo (precaução)
  f.clear();

  // Salvar os objetos
  json j;

  // iniciar o json com array vazio
  j = json::array();

  for (auto &obj : objetos)
  {
    /* cout << "Salvando objeto " << obj->getClassName() << endl; */
    json objJson;
    objJson["id"] = obj->object_id;
    objJson["class"] = obj->getClassName(); // Nome da classe legivel (Mesa, Balcao)
    objJson["t_x"] = obj->trans_x;
    objJson["t_y"] = obj->trans_y;
    objJson["t_z"] = obj->trans_z;
    objJson["r_x"] = obj->rot_x;
    objJson["r_y"] = obj->rot_y;
    objJson["r_z"] = obj->rot_z;
    objJson["s_x"] = obj->scale_x;
    objJson["s_y"] = obj->scale_y;
    objJson["s_z"] = obj->scale_z;
    objJson["selected"] = false; // Nunca vai estar selecionado

    j.push_back(objJson);
  }

  // Salvar o json no arquivo
  std::ofstream o("save.json");
  o << std::setw(4) << j << std::endl; // 4 espaços de indentação
}

void readSave()
{
  // Lê o arquivo de save
  ifstream save;
  save.open("save.json");

  if (!save.is_open())
  {
    cout << "ARQUIVO DE SAVE NÃO ENCONTRADO" << endl;
    cout << "Criando cena padrao" << endl;

    // Criar o arquivo
    // @TODO: Re-habilitar isso depois
    /*     ofstream createSave;
        createSave.open("save.json");
        createSave.close();
        saveScene();
     */

    // Balcao, armario e prateleira no fundo
    Balcao *balcao = new Balcao(giveId(), -0.8, 0.0, -3, 0., 360., 0., 1., 1., 1., false, false);

    Armario *armario_fundo = new Armario(giveId(), -3.0, 0.0, -4.4, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false);
    Barril *barril_armario_fundo_1 = new Barril(giveId(), -3.0, 0.1, -4.4, 0., 0., 0., 1., 1., 1., false, false);

    Prateleira *prateleira_fundo = new Prateleira(giveId(), -1., 2.2, -4.6, 0., 0., 0., 1., 1., 1., false, false);
    Cobertura *cobertura_prateleira_fundo = new Cobertura(giveId(), -1., 1.75, -5, 0., 0., 0., 1., 1., 1., false, false);
    Caneca *caneca_prateleira_fundo_1 = new Caneca(giveId(), -0.5, 2.4, -4.6, 0., 180., 0., 1., 1., 1., false, false);

    Tamborete *tamborete_balcao_1 = new Tamborete(giveId(), -3.1, 0.0, -2.2, 0., 0., 0., 1., 1., 1., false, false);
    Caneca *caneca_balcao_1 = new Caneca(giveId(), -3.1, 1, -3, 0., 10, 0., 1., 1., 1., false, false);

    Mesa *mesa_1 = new Mesa(giveId(), 3.0, 0.0, 2.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false);
    Tamborete *tamborete_1_mesa_1 = new Tamborete(giveId(), 2.3, 0.0, 2.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false);
    Tamborete *tamborete_2_mesa_1 = new Tamborete(giveId(), 3.8, 0.0, 2.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false);
    Caneca *caneca_1_mesa_1 = new Caneca(giveId(), 3.1, 1, 2.1, 0.0, 90.0, 0.0, 1.0, 1.0, 1.0, false, false);
    Caneca *caneca_2_mesa_1 = new Caneca(giveId(), 2.8, 1, 2, 0.0, -90.0, 0.0, 1.0, 1.0, 1.0, false, false);

    Mesa *mesa_2 = new Mesa(giveId(), -2.5, 0.0, 0.5, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false);
    Tamborete *tamborete_1_mesa_2 = new Tamborete(giveId(), -3.2, 0.0, 0.5, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false);
    Caneca *caneca_1_mesa_2 = new Caneca(giveId(), -2.8, 1, 0.6, 0.0, -84.0, 0.0, 1.0, 1.0, 1.0, false, false);

    Palco *palco = new Palco(giveId(), 4, 0.0, -4.5, 0.0, 0.0, 0.0, 0.6, 0.9, 0.9, false, false);
    Microfone *microfone = new Microfone(giveId(), 3.5, 0.85, -3.8, 0.0, 50.0, 0.0, 0.6, 0.9, 0.9, false, false);

    objetos.push_back(balcao);

    objetos.push_back(armario_fundo);
    objetos.push_back(barril_armario_fundo_1);

    objetos.push_back(prateleira_fundo);
    objetos.push_back(cobertura_prateleira_fundo);
    objetos.push_back(caneca_prateleira_fundo_1);

    objetos.push_back(tamborete_balcao_1);

    objetos.push_back(caneca_balcao_1);

    objetos.push_back(mesa_1);
    objetos.push_back(tamborete_1_mesa_1);
    objetos.push_back(tamborete_2_mesa_1);
    objetos.push_back(caneca_1_mesa_1);
    objetos.push_back(caneca_2_mesa_1);

    objetos.push_back(mesa_2);
    objetos.push_back(tamborete_1_mesa_2);
    objetos.push_back(caneca_1_mesa_2);

    objetos.push_back(palco);
    objetos.push_back(microfone);
  }
  else
  {

    for (auto &obj : json::parse(save))
    {
      // Cria o objeto baseado na classe
      string classe = obj["class"];

      int id = obj["id"];
      float t_x = obj["t_x"];
      float t_y = obj["t_y"];
      float t_z = obj["t_z"];
      float r_x = obj["r_x"];
      float r_y = obj["r_y"];
      float r_z = obj["r_z"];
      float s_x = obj["s_x"];
      float s_y = obj["s_y"];
      float s_z = obj["s_z"];

      // Criar o objeto
      if (classe == "Mesa")
      {
        objetos.push_back(new Mesa(id, t_x, t_y, t_z, r_x, r_y, r_z, s_x, s_y, s_z, false, false));
      }
      else if (classe == "Balcao")
      {
        objetos.push_back(new Balcao(id, t_x, t_y, t_z, r_x, r_y, r_z, s_x, s_y, s_z, false, false));
      }
      else if (classe == "Prateleira")
      {
        objetos.push_back(new Prateleira(id, t_x, t_y, t_z, r_x, r_y, r_z, s_x, s_y, s_z, false, false));
      }
      else if (classe == "Tamborete")
      {
        objetos.push_back(new Tamborete(id, t_x, t_y, t_z, r_x, r_y, r_z, s_x, s_y, s_z, false, false));
      }
      else if (classe == "Barril")
      {
        objetos.push_back(new Barril(id, t_x, t_y, t_z, r_x, r_y, r_z, s_x, s_y, s_z, false, false));
      }
      else if (classe == "Caneca")
      {
        objetos.push_back(new Caneca(id, t_x, t_y, t_z, r_x, r_y, r_z, s_x, s_y, s_z, false, false));
      }
      else if (classe == "Armario")
      {
        objetos.push_back(new Armario(id, t_x, t_y, t_z, r_x, r_y, r_z, s_x, s_y, s_z, false, false));
      }
      else if (classe == "Parede")
      {
        objetos.push_back(new Parede(id, t_x, t_y, t_z, r_x, r_y, r_z, s_x, s_y, s_z, false, false));
      }
      else if (classe == "Palco")
      {
        objetos.push_back(new Palco(id, t_x, t_y, t_z, r_x, r_y, r_z, s_x, s_y, s_z, false, false));
      }
      else if (classe == "Microfone")
      {
        objetos.push_back(new Microfone(id, t_x, t_y, t_z, r_x, r_y, r_z, s_x, s_y, s_z, false, false));
      }
    }
  }

  cout << "PROCESSO DE LEITURA DE SAVE CONCLUIDO" << endl;
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
    sombras_planos = !sombras_planos;
    break;
  case 'i':
    // Troca entre luz pontual próxima e luz distante
    tipo_luz = !tipo_luz;
    break;
  // ------------------------- TECLAS: legado -------------------------
  case 'p':
    objetos[current_object_id]->selected = false;
    // Alterar o modo de seleção
    selecting_state = !selecting_state;

    // Atualizar o objeto selecionado
    current_object_id = 0;
    if (selecting_state)
    {
      objetos[current_object_id]->selected = true;
    }
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
    // Isométrica
    glutGUI::perspective = !glutGUI::perspective;
    break;
  default:
    break;
  }
}

void montarCena()
{

  glClearColor(0.53, 0.81, 0.92, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  // GUI::setLight(0,  3,5,4, true,false);//(tecla de apagar, x,y,z , desligar e ligar luz, (false = forte, true = atenuada))

  GUI::drawOrigin(1); // tamanho de cada eixo

  GUI::setColor(0.0118, 0.7333, 0.5216, 1, true); //(red,green,blue,opacidade,componente_de_reflexão)

  glPushMatrix();
  //-------------------sombra-------------------
  glTranslated(0.0, k, 0.0); // glTranslated(0.0,k-0.001,0.0);
  GUI::setColor(0.8, 0.8, 0.8, 1, true);
  GUI::drawFloor(10, 10, 0.1, 0.1); //(largura, comprimento, vertices largura, vertices comprimento)
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
  float lightPos[4] = {1.5 + glutGUI::lx, 1.5 + glutGUI::ly, 1.5 + glutGUI::lz, tipo_luz};
  // GUI::setLight(0,lightPos[0],lightPos[1],lightPos[2],true,false,false,false,pontual);
  GUI::setLight(0, 3, 5, 4, true, false, false, false, tipo_luz);
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
void sombra_plano_qualquer(GLfloat plano[4], float lightPos[4])
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

// TODO: Mudar nome
void mostrarSombrasNosPlanos()
{
  float lightPos[4] = {glutGUI::lx, glutGUI::ly, glutGUI::lz, tipo_luz ? 1.0f : 0.0f};

  GUI::setLight(0, lightPos[0], lightPos[1], lightPos[2], true, false, false, false, tipo_luz);
  GLfloat plano_chao[4] = {0, 1, 0, -0.001};
  sombra_plano_qualquer(plano_chao, lightPos);

  // lateral
  GUI::setColor(1, 0.98, 0.98);
  glPushMatrix();
  GUI::drawBox(-5, 0, -5, -4.8, 5, 5);
  glPopMatrix();
  GLfloat plano_lateral[4] = {0.63, 0, 0, 3.00 - 0.001};
  sombra_plano_qualquer(plano_lateral, lightPos);

  // frente
  GUI::setColor(1, 0.98, 0.98);
  glPushMatrix();
  GUI::drawBox(-4.8, 0, -5, 5, 5, -4.8);
  glPopMatrix();
  GLfloat plano_frente[4] = {0, 0, 0.63, 3.00 - 0.001};
  sombra_plano_qualquer(plano_frente, lightPos);

  // inclinado
  GUI::setColor(1, 0.98, 0.98);
  glPushMatrix();
  glTranslatef(-4.04, 0, -2.5);
  glRotatef(-45, 0, 0, 1);
  GUI::drawQuad(2, 5);
  glPopMatrix();
  GLfloat plano_inclinado[4] = {0.63, 0.63, 0, 2.54 - 0.001};
  sombra_plano_qualquer(plano_inclinado, lightPos);
}

void desenha_viewports_gerais()
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

  if (!viewports)
  {

    montarCena();
  }
  else
  {
    desenha_viewports_gerais();
  }

  // TODO: Alterar nomes
  if (sombras_planos)
  {
    mostrarSombrasNosPlanos();
  }

  transformObjects();

  GUI::displayEnd();
}

int main(int argc, char *argv[])
{

  readSave();
  // GUI gui(800,600); // (largura, altura)
  GUI gui = GUI(800, 600, desenha, teclado);
  // TODO: GUI gui = GUI(800, 600, desenha, teclado, mouse);
  // GUI gui2 = GUI(500, 200, desenha2);
}

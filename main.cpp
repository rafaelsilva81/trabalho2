
#include <iostream>
#include <thread>

using namespace std;

#include <vector>
#include <gui.h>
#include <fstream>
#include <string>
#include <unistd.h>

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
int max_object_id = 0;

vector<Objeto *> objetos;

// Indica se o usuário está no "modo de seleção" de objetos
bool selecting_state = false;

// Indica se o usuário pediu pra salvar a cena
bool asked_to_save = false;

// Indica se o usuário esta no modo de transformação
bool transforming_state = false;

// Indica se o usuário esta no modo de movimentação de luz
bool moving_light_state = false;

// Indica a camera
int camera_presets = 0;

std::ofstream myfile;

void transformObjects()
{
  // Aplicando transformações no objeto selecionado
  if (selecting_state)
  {
    /* cout << "Aplicando transformações no objeto " + to_string(current_object_id) << endl; */
    // Translações
    objetos[current_object_id]->trans_x += 10 * glutGUI::dtx;
    objetos[current_object_id]->trans_y += 10 * glutGUI::dty;
    objetos[current_object_id]->trans_z += 10 * glutGUI::dtz;

    // Rotações
    objetos[current_object_id]->rot_x += 10 * glutGUI::dax;
    objetos[current_object_id]->rot_y += 10 * glutGUI::day;
    objetos[current_object_id]->rot_z += 10 * glutGUI::daz;

    // Escalas
    objetos[current_object_id]->scale_x += 10 * glutGUI::dsx;
    objetos[current_object_id]->scale_y += 10 * glutGUI::dsy;
    objetos[current_object_id]->scale_z += 10 * glutGUI::dsz;
  }
}

int giveId()
{
  /*  cout << "Atribuindo id:" + to_string(max_object_id) << endl; */
  max_object_id += 1;
  return max_object_id;
}

void grid()
{
  glBegin(GL_LINES);
  GUI::setColor(0.5, 0.5, 0.5);
  for (float i = -5; i <= 5; i += 1.0)
  {
    // Draw lines along the x-axis
    glVertex3f(i, 0, -5);
    glVertex3f(i, 0, 5);

    // Draw lines along the z-axis
    glVertex3f(-5, 0, i);
    glVertex3f(5, 0, i);
  }
  glEnd();
}

void saveScene()
{
  // Pegar todos os objetos, e salvar no arquivo save

  std::ifstream f("save.json");

  // Limpar o arquivo (precaução)
  f.clear();

  /*

    Mesa *mesa = new Mesa(1, 3.0, 0.0, 2.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false);
    FORMATO DO JSON
    [
      {
        id: 1,
        class: "Mesa",
        t_x: 3.0,
        t_y: 0.0,
        t_z: 2.0,
        r_x: 0.0,
        r_y: 0.0,
        r_z: 0.0,
        s_x: 1.0,
        s_y: 1.0,
        s_z: 1.0,
        selected: false
      },
    ]
  */

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

  asked_to_save = true;
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
    Balcao *balcao = new Balcao(giveId(), -2.0, 0.0, -2.5, 0., 360., 0., 1., 1., 1., false, false);

    Armario *armario_fundo = new Armario(giveId(), -4.0, 0.0, -4.5, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false);
    Barril *barril_armario_fundo_1 = new Barril(giveId(), -4.0, 0.1, -4.5, 0., 0., 0., 1., 1., 1., false, false);
    Barril *barril_armario_fundo_2 = new Barril(giveId(), -4.0, 1.5, -4.5, 0., 0., 0., 1., 1., 1., false, false);

    Prateleira *prateleira_fundo = new Prateleira(giveId(), -2., 2.2, -4.7, 0., 0., 0., 1., 1., 1., false, false);
    Cobertura *cobertura_prateleira_fundo = new Cobertura(giveId(), -2., 1.85, -5, 0., 0., 0., 1., 1., 1., false, false);
    Caneca *caneca_prateleira_fundo_1 = new Caneca(giveId(), -1.5, 2.4, -4.7, 0., 180., 0., 1., 1., 1., false, false);
    Caneca *caneca_prateleira_fundo_2 = new Caneca(giveId(), -1.8, 2.4, -4.7, 0., 180., 0., 1., 1., 1., false, false);
    /* Caneca *caneca_prateleira_fundo_3 = new Caneca(giveId(), -2.2, 2.4, -4.7, 0., 180., 0., 1., 1., 1., false, false); */

    Tamborete *tamborete_balcao_1 = new Tamborete(giveId(), -4.2, 0.0, -1.9, 0., 0., 0., 1., 1., 1., false, false);
    Tamborete *tamborete_balcao_2 = new Tamborete(giveId(), -3, 0.0, -1.9, 0., 0., 0., 1., 1., 1., false, false);
    Tamborete *tamborete_balcao_3 = new Tamborete(giveId(), -1.8, 0.0, -1.9, 0., 0., 0., 1., 1., 1., false, false);
    Tamborete *tamborete_balcao_4 = new Tamborete(giveId(), -0.6, 0.0, -1.9, 0., 0., 0., 1., 1., 1., false, false);

    Caneca *caneca_balcao_1 = new Caneca(giveId(), -4.3, 1, -2.4, 0., 10, 0., 1., 1., 1., false, false);
    Caneca *caneca_balcao_2 = new Caneca(giveId(), -3.3, 1, -2.4, 0., -20, 0., 1., 1., 1., false, false);
    Caneca *caneca_balcao_3 = new Caneca(giveId(), -1.8, 1, -2.4, 0., 30, 0., 1., 1., 1., false, false);
    /* Caneca *caneca_balcao_4 = new Caneca(giveId(), -0.3, 1, -2.4, 0., 45, 0., 1., 1., 1., false, false); */

    Mesa *mesa_1 = new Mesa(giveId(), 3.0, 0.0, 2.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false);
    Tamborete *tamborete_1_mesa_1 = new Tamborete(giveId(), 2.3, 0.0, 2.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false);
    Tamborete *tamborete_2_mesa_1 = new Tamborete(giveId(), 3.8, 0.0, 2.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false);
    Caneca *caneca_1_mesa_1 = new Caneca(giveId(), 3.1, 1, 2.1, 0.0, 90.0, 0.0, 1.0, 1.0, 1.0, false, false);
    Caneca *caneca_2_mesa_1 = new Caneca(giveId(), 2.8, 1, 2, 0.0, -90.0, 0.0, 1.0, 1.0, 1.0, false, false);

    Mesa *mesa_2 = new Mesa(giveId(), -3.0, 0.0, 0.5, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false);
    Tamborete *tamborete_1_mesa_2 = new Tamborete(giveId(), -3.6, 0.0, 0.5, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false);
    Tamborete *tamborete_2_mesa_2 = new Tamborete(giveId(), -2.2, 0.0, 0.5, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false);
    Caneca *caneca_1_mesa_2 = new Caneca(giveId(), -3.1, 1, 0.6, 0.0, -84.0, 0.0, 1.0, 1.0, 1.0, false, false);
    /* Caneca *caneca_2_mesa_2 = new Caneca(giveId(), -2.8, 1, 0.5, 0.0, 98.0, 0.0, 1.0, 1.0, 1.0, false, false); */

    Mesa *mesa_3 = new Mesa(giveId(), -2.5, 0.0, 3.5, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false);
    Tamborete *tamborete_1_mesa_3 = new Tamborete(giveId(), -2.5, 0.0, 4.2, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false);
    Tamborete *tamborete_2_mesa_3 = new Tamborete(giveId(), -2.5, 0.0, 2.8, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false);
    /*  Caneca *caneca_1_mesa_3 = new Caneca(giveId(), -2.4, 1, 3.3, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false); */
    Caneca *caneca_2_mesa_3 = new Caneca(giveId(), -2.6, 1, 3.6, 0.0, 180.0, 0.0, 1.0, 1.0, 1.0, false, false);

    Palco *palco = new Palco(giveId(), 3.5, 0.0, -4.5, 0.0, 0.0, 0.0, 0.9, 0.9, 0.9, false, false);
    Microfone *microfone = new Microfone(giveId(), 3, 0.85, -3.8, 0.0, 50.0, 0.0, 0.9, 0.9, 0.9, false, false);

    objetos.push_back(balcao);

    objetos.push_back(armario_fundo);
    objetos.push_back(barril_armario_fundo_1);
    objetos.push_back(barril_armario_fundo_2);

    objetos.push_back(prateleira_fundo);
    objetos.push_back(cobertura_prateleira_fundo);
    objetos.push_back(caneca_prateleira_fundo_1);
    objetos.push_back(caneca_prateleira_fundo_2);
    /* objetos.push_back(caneca_prateleira_fundo_3); */

    objetos.push_back(tamborete_balcao_1);
    objetos.push_back(tamborete_balcao_2);
    objetos.push_back(tamborete_balcao_3);
    objetos.push_back(tamborete_balcao_4);

    objetos.push_back(caneca_balcao_1);
    objetos.push_back(caneca_balcao_2);
    objetos.push_back(caneca_balcao_3);
    /* objetos.push_back(caneca_balcao_4); */

    objetos.push_back(mesa_1);
    objetos.push_back(tamborete_1_mesa_1);
    objetos.push_back(tamborete_2_mesa_1);
    objetos.push_back(caneca_1_mesa_1);
    objetos.push_back(caneca_2_mesa_1);

    objetos.push_back(mesa_2);
    objetos.push_back(tamborete_1_mesa_2);
    objetos.push_back(tamborete_2_mesa_2);
    objetos.push_back(caneca_1_mesa_2);
    /* objetos.push_back(caneca_2_mesa_2); */

    objetos.push_back(mesa_3);
    objetos.push_back(tamborete_1_mesa_3);
    objetos.push_back(tamborete_2_mesa_3);
    /* objetos.push_back(caneca_1_mesa_3); */
    objetos.push_back(caneca_2_mesa_3);

    objetos.push_back(palco);
    objetos.push_back(microfone);

    // @TODO: Re-habilitar isso depois
    // saveScene();
  }
  else
  {
    cout << "ARQUIVO DE SAVE ENCONTRADO" << endl;
    cout << "Lendo arquivo de save..." << endl;
    // Ler os objetos
    // formato do json:
    /*

      Mesa *mesa = new Mesa(1, 3.0, 0.0, 2.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false);
      FORMATO DO JSON
      [
        {
          id: 1,
          class: "Mesa",
          t_x: 3.0,
          t_y: 0.0,
          t_z: 2.0,
          r_x: 0.0,
          r_y: 0.0,
          r_z: 0.0,
          s_x: 1.0,
          s_y: 1.0,
          s_z: 1.0,
          selected: false
        },
        {}
      ]
    */
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

      // @TODO: Adicionar os novos objetos
    }
  }

  cout << "PROCESSO DE LEITURA DE SAVE CONCLUIDO" << endl;
}

void drawString(std::string str, int x, int y)
{

  /*
    No OpenGL, existem dois modos de exibição principais: o modo de projeção e o modo de modelagem.

    No caso da função em questão, estamos definindo o modo de projeção para desenhar um texto em uma
    janela bidimensional usando a função gluOrtho2D(),
    que define um sistema de coordenadas bidimensional de 800x600.

    Em seguida, o texto é desenhado na tela usando as funções do GLUT glutBitmapCharacter() e glRasterPos2i()

  */
  // Define o modo de projeção para desenhar o texto na tela
  glMatrixMode(GL_PROJECTION);

  // Salva a matriz atual na pilha de matrizes OpenGL
  glPushMatrix();

  // Define a matriz de projeção como uma matriz de identidade para garantir que não haja transformações aplicadas a ela
  glLoadIdentity();

  // Define o sistema de coordenadas bidimensional com o canto inferior esquerdo em (0,0) e o canto superior direito em (800,600)
  gluOrtho2D(0, 800, 0, 600);

  // Define o modo de modelagem para desenhar o texto na tela
  glMatrixMode(GL_MODELVIEW);

  // Salva a matriz atual na pilha de matrizes OpenGL
  glPushMatrix();

  // Define a matriz de modelagem como uma matriz de identidade para garantir que não haja transformações aplicadas a ela
  glLoadIdentity();

  // Define a posição do ponto onde o texto será desenhado com as coordenadas (x,y)
  glRasterPos2i(x, y);

  // Percorre cada caractere da string e desenha na posição atual do raster utilizando uma fonte 9x15 pixels
  for (char c : str)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);

  // Restaura a matriz de modelagem anteriormente salva na pilha de matrizes OpenGL
  glPopMatrix();

  // Define o modo de modelagem para desenhar outros objetos na cena
  glMatrixMode(GL_MODELVIEW);

  // Restaura a matriz de projeção anteriormente salva na pilha de matrizes OpenGL
  glPopMatrix();

  // Define o modo de projeção para desenhar outros objetos na cena
  glMatrixMode(GL_PROJECTION);
}

void writeCamDebug()
{
  std::ofstream camPos;

  // Limpa o arquivo caso ele já exista
  camPos.open("camera.txt", std::ofstream::out | std::ofstream::trunc);

  if (camPos.is_open())
  {
    camPos << "glutGUI::cam->e.x=" << glutGUI::cam->e.x << ";" << endl;
    camPos << "glutGUI::cam->e.y=" << glutGUI::cam->e.y << ";" << endl;
    camPos << "glutGUI::cam->e.z=" << glutGUI::cam->e.z << ";" << endl;
    camPos << "glutGUI::cam->c.x=" << glutGUI::cam->c.x << ";" << endl;
    camPos << "glutGUI::cam->c.y=" << glutGUI::cam->c.y << ";" << endl;
    camPos << "glutGUI::cam->c.z=" << glutGUI::cam->c.z << ";" << endl;
    camPos << "glutGUI::cam->u.x=" << glutGUI::cam->u.x << ";" << endl;
    camPos << "glutGUI::cam->u.y=" << glutGUI::cam->u.y << ";" << endl;
    camPos << "glutGUI::cam->u.z=" << glutGUI::cam->u.z << ";" << endl;
    camPos.close(); // close the file
    std::cout << "Camera salva" << std::endl;
  }
  else
  {
    std::cout << "Erro ao abrir arquivo" << std::endl;
  }
}

void teclado(unsigned char tecla, int mouseX, int mouseY)
{
  GUI::keyInit(tecla, mouseX, mouseY);

  switch (tecla)
  {
  case 't':
    transforming_state = !transforming_state;
    glutGUI::trans_obj = !glutGUI::trans_obj;
    break;
  case 'l':
    moving_light_state = !moving_light_state;
    glutGUI::trans_luz = !glutGUI::trans_luz;
    break;
  case '1':
    // Criar mesa
    objetos.push_back(new Mesa(giveId(), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false));
    break;
  case '2':
    // Criar balcao
    objetos.push_back(new Balcao(giveId(), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false));
    break;
  case '3':
    // Criar prateleira
    objetos.push_back(new Prateleira(giveId(), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false));
    break;
  case '4':
    // Criar tamborete
    objetos.push_back(new Tamborete(giveId(), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false));
    break;
  case '5':
    // Criar barril
    objetos.push_back(new Barril(giveId(), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false));
    break;
  case '6':
    // Criar caneca
    objetos.push_back(new Caneca(giveId(), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false));
    break;
  case '7':
    // Criar armario
    objetos.push_back(new Armario(giveId(), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false));
    break;
  case '8':
    // Criar palco
    objetos.push_back(new Palco(giveId(), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false));
    break;
  case '9':
    // Criar microfone
    objetos.push_back(new Microfone(giveId(), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false));
    break;
  case '[':
    // Criar cobertura
    objetos.push_back(new Cobertura(giveId(), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false, false));
    break;
  case 'd':
    if (selecting_state)
    {
      // Deletar objeto
      objetos.erase(objetos.begin() + current_object_id);

      // Reduzir index
      if (objetos.size() == 0)
      {
        current_object_id = 0;
        selecting_state = false;
      }

      // Volta pro id 1
      current_object_id = 0;
      objetos[current_object_id]->selected = !objetos[current_object_id]->selected;
    }
    break;
  case 'x':
    if (selecting_state)
    {
      // Obter o ultimo indice
      current_object_id = objetos.size() - 1;

      // Deletar objeto
      objetos.erase(objetos.begin() + current_object_id);

      // Reduzir index
      if (objetos.size() == 0)
      {
        current_object_id = 0;
        selecting_state = false;
      }

      // Volta pro id 1
      current_object_id = 0;
      objetos[current_object_id]->selected = true;
    }
    break;
  case 's':
    // Salvar
    saveScene();
    break;
  case 'c':
    camera_presets++;
    /* cout << "Camera Preset: " << camera_presets << endl; */
    // Presets de camera
    switch (camera_presets)
    {
    case 0:
      // Camera inicial
      break;
    case 1:
      // Camera atrás do balcão
      glutGUI::cam->e.x = -0.41;
      glutGUI::cam->e.y = 1.9;
      glutGUI::cam->e.z = -4.75;
      glutGUI::cam->c.x = -0.53;
      glutGUI::cam->c.y = 1.69;
      glutGUI::cam->c.z = -3.43;
      glutGUI::cam->u.x = -0.015;
      glutGUI::cam->u.y = 0.987;
      glutGUI::cam->u.z = 0.16;
      break;
    case 2:
      // Camera no palco (microfone)
      glutGUI::cam->e.x = 4.235;
      glutGUI::cam->e.y = 3.018;
      glutGUI::cam->e.z = -5.60;
      glutGUI::cam->c.x = 3.60;
      glutGUI::cam->c.y = 2.54;
      glutGUI::cam->c.z = -4.15;
      glutGUI::cam->u.x = -0.12;
      glutGUI::cam->u.y = 0.96;
      glutGUI::cam->u.z = 0.27;
      break;
    case 3:
      // Camera na mesa 3 (olhando pro palco)
      glutGUI::cam->e.x = -2.9;
      glutGUI::cam->e.y = 1.45;
      glutGUI::cam->e.z = 5.22;
      glutGUI::cam->c.x = -0.643;
      glutGUI::cam->c.y = 1;
      glutGUI::cam->c.z = 0.176;
      glutGUI::cam->u.x = 0.032;
      glutGUI::cam->u.y = 0.997;
      glutGUI::cam->u.z = -0.0728;
      break;
    case 4:
      // Visão completa zoom out
      glutGUI::cam->e.x = 11.571;
      glutGUI::cam->e.y = 12.1003;
      glutGUI::cam->e.z = 17.1499;
      glutGUI::cam->c.x = -0.0428;
      glutGUI::cam->c.y = 1.51;
      glutGUI::cam->c.z = -0.46;
      glutGUI::cam->u.x = -0.25;
      glutGUI::cam->u.y = 0.894;
      glutGUI::cam->u.z = -0.374;
      break;
    case 5:
      // Visão da mesa pro balcao
      glutGUI::cam->e.x = 4.535;
      glutGUI::cam->e.y = 1.446;
      glutGUI::cam->e.z = 2.134;
      glutGUI::cam->c.x = 4.034;
      glutGUI::cam->c.y = 1.390;
      glutGUI::cam->c.z = 1.993;
      glutGUI::cam->u.x = -0.102;
      glutGUI::cam->u.y = 0.994;
      glutGUI::cam->u.z = -0.0288;
      break;
    case 6:
      // visão do balcao para o palco
      glutGUI::cam->e.x = -3.16;
      glutGUI::cam->e.y = 1.28;
      glutGUI::cam->e.z = -1.78;
      glutGUI::cam->c.x = -3.067;
      glutGUI::cam->c.y = 1.27;
      glutGUI::cam->c.z = -1.81;
      glutGUI::cam->u.x = -0.0326;
      glutGUI::cam->u.y = 0.1;
      glutGUI::cam->u.z = 0.015;
      break;
    default:
      camera_presets = 0;
      break;
    }
    break;
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
  case 'n':
    // Vai pro proximo objeto
    objetos[current_object_id]->selected = false;
    // Alterar o objeto atualmente selecionado
    if (selecting_state)
    {
      // Alternar o current_id
      if (current_object_id >= objetos.size() - 1)
      {
        current_object_id = 0;
      }
      else
      {
        current_object_id++;
      }

      // Atualizar o objeto selecionado
      objetos[current_object_id]->selected = true;
    }
    break;
  case 'b':
    // Volta pro objeto anterior
    objetos[current_object_id]->selected = false;

    // Alterar o objeto atualmente selecionado
    if (selecting_state)
    {
      // Alternar o current_id
      if (current_object_id <= 0)
      {
        current_object_id = objetos.size() - 1;
      }
      else
      {
        current_object_id--;
      }

      // Atualizar o objeto selecionado
      objetos[current_object_id]
          ->selected = true;
    }
    break;
  case 'v':
    // Vetor de Coordenadas
    if (selecting_state)
    {
      objetos[current_object_id]->show_coord = !objetos[current_object_id]->show_coord;
    }
    break;
  case '-':
    // escrever num arquivo a posição da camera atual (para debug)
    // arquivo camera.txt
    writeCamDebug();
    break;
  default:
    break;
  }
}

void montarCena()
{

  glClearColor(0.53, 0.81, 0.92, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  // Definir iluminação
  GUI::setLight(0, 3, 5, 4, true, false);

  // Debug do eixo
  /* GUI::drawOriginAL(5, 1); */
  GUI::setColor(0.8, 0.8, 0.8, 1, true);
  // Piso
  GUI::drawFloor(10, 10, 0.5, 0.5);

  // GUI::setColor(0,1,0, 1,true);
  // GUI::drawBox(0+desl.x,0+desl.y,0+desl.z, 1+desl.x,1+desl.y,1+desl.z);//(x0,y0,z0, xf,yf,zf)

  // Adiciona as paredes
  glPushMatrix();
  paredeLeft->desenha();
  paredeBack->desenha();
  glPopMatrix();

  for (int i = 0; i < objetos.size(); ++i)
  {
    // Itera pelos objetos e desenha
    glPushMatrix();
    objetos[i]->desenha();
    glPopMatrix();
  }
}

void desenha()
{
  GUI::displayInit();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(glutGUI::cam->e.x, glutGUI::cam->e.y, glutGUI::cam->e.z, glutGUI::cam->c.x, glutGUI::cam->c.y, glutGUI::cam->c.z, glutGUI::cam->u.x, glutGUI::cam->u.y, glutGUI::cam->u.z);

  montarCena();

  grid();

  if (asked_to_save)
  {
    drawString("SALVO COM SUCESSO!", 4, 75);
    asked_to_save = false;
  }

  drawString("CAMERA PRESET:" + to_string(camera_presets), 4, 60);

  if (selecting_state && objetos[current_object_id]->show_coord)
  {
    drawString("MOSTRANDO COORDENADAS", 4, 45);
  }

  if (transforming_state)
  {
    drawString("TRANSFORMANDO OBJETO", 4, 30);
  }

  if (moving_light_state)
  {
    drawString("MOVENDO LUZ", 4, 15);
  }

  if (selecting_state)
  {
    string s = "SELECIONANDO:" + objetos[current_object_id]->getClassName() + " id " + to_string(current_object_id);
    // Irá mostrar na tela quando um objeto estiver selecionado
    drawString(s, 4, 1);
  }

  transformObjects();

  GUI::displayEnd();
}

int main(int argc, char *argv[])
{

  cout << "CONFIGURAÇÃO DE TECLAS" << endl;
  cout << "p: Selecionar objeto" << endl;
  cout << "n: Selecionar próximo objeto" << endl;
  cout << "b: Selecionar objeto anterior" << endl;
  cout << "v: Mostrar vetor de coordenadas" << endl;
  cout << "1: Adicionar mesa" << endl;
  cout << "2: Adicionar balcão" << endl;
  cout << "3: Adicionar prateleira" << endl;
  cout << "4: Adicionar cadeira" << endl;
  cout << "5: Adicionar barril" << endl;
  cout << "6: Adicionar canera" << endl;
  cout << "7: Adicionar armario" << endl;
  cout << "8: Adicionar palco" << endl;
  cout << "9: Adicionar microfone" << endl;
  cout << "[: Adicionar cobertura" << endl;
  cout << "c: Alternar camera" << endl;
  cout << "s: Salvar cena" << endl;
  cout << "t: Transformar objeto" << endl;
  cout << "l: Mover luz" << endl;
  cout << "d: Remover objeto selecionado" << endl;
  cout << "x: Remover ultimo objeto" << endl;
  cout << "=: Remover arquivo de save e reiniciar" << endl; // TODO: this
  cout << "q: Fechar" << endl;

  readSave();
  // GUI gui(800,600); // (largura, altura)
  GUI gui = GUI(800, 600, desenha, teclado);

  // GUI gui2 = GUI(500, 200, desenha2);
}

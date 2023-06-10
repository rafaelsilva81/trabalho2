#include "Balcao.h"
#include <gui.h>

using namespace std;

Balcao::Balcao(int id, float t_x, float t_y, float t_z,
               float r_x, float r_y, float r_z,
               float s_x, float s_y, float s_z,
               bool sel, bool coord)
{
  object_id = id;
  trans_x = t_x;
  trans_y = t_y;
  trans_z = t_z;
  rot_x = r_x;
  rot_y = r_y;
  rot_z = r_z;
  scale_x = s_x;
  scale_y = s_y;
  scale_z = s_z;
  selected = sel;
  show_coord = coord;
}

void Balcao::criar()
{

  if (show_coord)
  {
    GUI::drawOrigin(1);
  }

  if (selected)
  {
    // Amarelo se estiver selecionado
    GUI::setColor(1, 1, 0, 1, true);
  }
  else
  {
    GUI::setColor(0.9373, 0.2667, 0.2667, 1, true);
  }

  // Face frontal
  glBegin(GL_POLYGON);
  glNormal3f(0.0, 0.0, 0.3);
  glVertex3f(-3.0, 0, 0.3);
  glVertex3f(3.0, 0, 0.3);
  glVertex3f(3.0, 1.0, 0.3);
  glVertex3f(-3.0, 1.0, 0.3);
  glEnd();

  // Face traseira
  glBegin(GL_POLYGON);
  glNormal3f(0.0, 0.0, -0.3);
  glVertex3f(-3.0, 0, -0.3);
  glVertex3f(-3.0, 1.0, -0.3);
  glVertex3f(3.0, 1.0, -0.3);
  glVertex3f(3.0, 0, -0.3);
  glEnd();

  // Face direita
  glBegin(GL_POLYGON);
  glNormal3f(1.0, 0.0, 0.0);
  glVertex3f(-3.0, 0, -0.3);
  glVertex3f(-3.0, 0, 0.3);
  glVertex3f(-3.0, 1.0, 0.3);
  glVertex3f(-3.0, 1.0, -0.3);
  glEnd();

  // Face esquerda
  glBegin(GL_POLYGON);
  glNormal3f(-1.0, 0.0, 0.0);
  glVertex3f(3.0, 0, -0.3);
  glVertex3f(3.0, 1.0, -0.3);
  glVertex3f(3.0, 1.0, 0.3);
  glVertex3f(3.0, 0, 0.3);
  glEnd();

  // Face inferior
  glBegin(GL_POLYGON);
  glNormal3f(0.0, 0, 0.0);
  glVertex3f(-3.0, 0, -0.3);
  glVertex3f(3.0, 0, -0.3);
  glVertex3f(3.0, 0, 0.3);
  glVertex3f(-3.0, 0, 0.3);
  glEnd();

  // Face superior
  glBegin(GL_POLYGON);
  glNormal3f(0.0, 1.0, 0.0);
  glVertex3f(-3.0, 1.0, -0.3);
  glVertex3f(-3.0, 1.0, 0.3);
  glVertex3f(3.0, 1.0, 0.3);
  glVertex3f(3.0, 1.0, -0.3);
  glEnd();

  /*
    Retangulo 2 vertical (e um pouco menor)
    Esse retangulo se extende atras do retangulo 1 e no fim do retangulo 1

    FORMATO:
         ##
         ##
         ##
  */

  // Face lateral direita
  glBegin(GL_POLYGON);
  glNormal3f(-1.0, 0.0, 0.0);
  glVertex3f(3.0, 0.0, -0.3);
  glVertex3f(3.0, 0.0, -1.2);
  glVertex3f(3.0, 1.0, -1.2);
  glVertex3f(3.0, 1.0, -0.3);
  glEnd();

  // Face traseira
  glBegin(GL_POLYGON);
  glNormal3f(0.0, 0.0, -1.2);
  glVertex3f(3.0, 0.0, -1.2);
  glVertex3f(2.3, 0.0, -1.2);
  glVertex3f(2.3, 1.0, -1.2);
  glVertex3f(3.0, 1.0, -1.2);
  glEnd();

  // Face lateral esquerda
  glBegin(GL_POLYGON);
  glNormal3f(0.0, 0.0, 1.0);
  glVertex3f(2.3, 0.0, -1.2);
  glVertex3f(2.3, 0.0, -0.3);
  glVertex3f(2.3, 1.0, -0.3);
  glVertex3f(2.3, 1.0, -1.2);
  glEnd();

  // Face Superior
  glBegin(GL_POLYGON);
  glNormal3f(0.0, 1.0, 0.0);
  glVertex3f(3.0, 1.0, -1.2);
  glVertex3f(2.3, 1.0, -1.2);
  glVertex3f(2.3, 1.0, -0.3);
  glVertex3f(3.0, 1.0, -0.3);
  glEnd();

  // Face inferior
  glBegin(GL_POLYGON);
  glNormal3f(0.0, 0, 0.0);
  glVertex3f(3.0, 0, -1.2);
  glVertex3f(3.0, 0, -0.3);
  glVertex3f(2.3, 0, -0.3);
  glVertex3f(2.3, 0, -1.2);
  glEnd();
}

void Balcao::desenha()
{
  glPushMatrix();
  Objeto::desenha(); // T.Rz.Ry.Rx.S. p
  criar();
  glPopMatrix();
}

std::string Balcao::getClassName()
{
  return "Balcao";
}
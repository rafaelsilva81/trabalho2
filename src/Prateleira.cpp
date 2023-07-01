#include "Prateleira.h"
#include <gui.h>

using namespace std;

Prateleira::Prateleira(int id, float t_x, float t_y, float t_z,
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

void Prateleira::criar()
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
    // Pintura do objeto (cor de madeira #966F33)
    GUI::setColor(0.588, 0.439, 0.2, 1, true);
  }

  // Face frontal
  glBegin(GL_POLYGON);
  glNormal3f(0.0, 0.0, 0.3);
  glVertex3f(-0.8, 0, 0.3);
  glVertex3f(0.8, 0, 0.3);
  glVertex3f(0.8, 0.2, 0.3);
  glVertex3f(-0.8, 0.2, 0.3);
  glEnd();

  // Face traseira
  glBegin(GL_POLYGON);
  glNormal3f(0.0, 0.0, -0.3);
  glVertex3f(-0.8, 0, -0.3);
  glVertex3f(-0.8, 0.2, -0.3);
  glVertex3f(0.8, 0.2, -0.3);
  glVertex3f(0.8, 0, -0.3);
  glEnd();

  // Face direita
  glBegin(GL_POLYGON);
  glNormal3f(1.0, 0.0, 0.0);
  glVertex3f(-0.8, 0, -0.3);
  glVertex3f(-0.8, 0, 0.3);
  glVertex3f(-0.8, 0.2, 0.3);
  glVertex3f(-0.8, 0.2, -0.3);
  glEnd();

  // Face esquerda
  glBegin(GL_POLYGON);
  glNormal3f(-1.0, 0.0, 0.0);
  glVertex3f(0.8, 0, -0.3);
  glVertex3f(0.8, 0.2, -0.3);
  glVertex3f(0.8, 0.2, 0.3);
  glVertex3f(0.8, 0, 0.3);
  glEnd();

  // Face inferior
  glBegin(GL_POLYGON);
  glNormal3f(0.0, 0, 0.0);
  glVertex3f(-0.8, 0, -0.3);
  glVertex3f(0.8, 0, -0.3);
  glVertex3f(0.8, 0, 0.3);
  glVertex3f(-0.8, 0, 0.3);
  glEnd();

  // Face superior
  glBegin(GL_POLYGON);
  glNormal3f(0.0, 1.0, 0.0);
  glVertex3f(-0.8, 0.2, -0.3);
  glVertex3f(-0.8, 0.2, 0.3);
  glVertex3f(0.8, 0.2, 0.3);
  glVertex3f(0.8, 0.2, -0.3);
  glEnd();

  // green
  GUI::setColor(0, 1, 0, 1, true);
}

void Prateleira::desenha()
{
  glPushMatrix();
  Objeto::desenha(); // T.Rz.Ry.Rx.S. p
  criar();
  glPopMatrix();
}

std::string Prateleira::getClassName()
{
  return "Prateleira";
}
#include "Mesa.h"
#include <gui.h>

using namespace std;

Mesa::Mesa(int id, float t_x, float t_y, float t_z,
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

void Mesa::criar()
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
    GUI::setColor(0.5451, 0.2706, 0.0745, 1, true);
  }

  glDisable(GL_CULL_FACE);

  // Perna da mesa

  glBegin(GL_POLYGON);
  glNormal3f(0.0, 0.0, -1.0);
  glVertex3f(-0.05, 0.0, -0.05);
  glVertex3f(-0.05, 1.0, -0.05);
  glVertex3f(0.05, 1.0, -0.05);
  glVertex3f(0.05, 0.0, -0.05);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(0.0, 0.0, 1.0);
  glVertex3f(-0.05, 0.0, 0.05);
  glVertex3f(-0.05, 1.0, 0.05);
  glVertex3f(0.05, 1.0, 0.05);
  glVertex3f(0.05, 0.0, 0.05);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(-1.0, 0.0, 0.0);
  glVertex3f(-0.05, 0.0, -0.05);
  glVertex3f(-0.05, 1.0, -0.05);
  glVertex3f(-0.05, 1.0, 0.05);
  glVertex3f(-0.05, 0.0, 0.05);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(1.0, 0.0, 0.0);
  glVertex3f(0.05, 0.0, -0.05);
  glVertex3f(0.05, 1.0, -0.05);
  glVertex3f(0.05, 1.0, 0.05);
  glVertex3f(0.05, 0.0, 0.05);
  glEnd();

  // Tampo da mesa
  // Alterar a cor para #ef4444
  if (!selected)
  {
    GUI::setColor(0.9373, 0.2667, 0.2667, 1, true);
  }

  // Faces do tampo da mesa

  glBegin(GL_POLYGON);
  glNormal3f(0.0, 1.0, 0.0);
  glVertex3f(-0.45, 1.0, -0.5);
  glVertex3f(-0.45, 1.0, 0.5);
  glVertex3f(0.45, 1.0, 0.5);
  glVertex3f(0.45, 1.0, -0.5);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(0.0, -1.0, 0.0);
  glVertex3f(-0.45, 0.95, -0.5);
  glVertex3f(-0.45, 0.95, 0.5);
  glVertex3f(0.45, 0.95, 0.5);
  glVertex3f(0.45, 0.95, -0.5);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(0.0, 0.0, -1.0);
  glVertex3f(-0.45, 0.95, -0.5);
  glVertex3f(-0.45, 1.0, -0.5);
  glVertex3f(0.45, 1.0, -0.5);
  glVertex3f(0.45, 0.95, -0.5);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(0.0, 0.0, 1.0);
  glVertex3f(-0.45, 0.95, 0.5);
  glVertex3f(-0.45, 1.0, 0.5);
  glVertex3f(0.45, 1.0, 0.5);
  glVertex3f(0.45, 0.95, 0.5);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(-1.0, 0.0, 0.0);
  glVertex3f(-0.45, 0.95, -0.5);
  glVertex3f(-0.45, 1.0, -0.5);
  glVertex3f(-0.45, 1.0, 0.5);
  glVertex3f(-0.45, 0.95, 0.5);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(1.0, 0.0, 0.0);
  glVertex3f(0.45, 0.95, -0.5);
  glVertex3f(0.45, 1.0, -0.5);
  glVertex3f(0.45, 1.0, 0.5);
  glVertex3f(0.45, 0.95, 0.5);
  glEnd();

  glEnable(GL_CULL_FACE);
}

void Mesa::desenha()
{
  glPushMatrix();
  Objeto::desenha(); // T.Rz.Ry.Rx.S. p
  criar();
  glPopMatrix();
}

std::string Mesa::getClassName()
{
  return "Mesa";
}
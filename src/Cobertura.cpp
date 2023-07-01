#include "Cobertura.h"
#include <gui.h>

using namespace std;

Cobertura::Cobertura(int id, float t_x, float t_y, float t_z,
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

void Cobertura::criar()
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
    GUI::setColor(0.588, 0.439, 0.2, 1, true);
  }

  glDisable(GL_CULL_FACE);

  // Losango
  glBegin(GL_POLYGON);
  glNormal3f(0, 1, 1);
  glVertex3f(-0.8, 1, 0.8);
  glVertex3f(0.8, 1, 0.8);
  glVertex3f(0.8, 1.3, 0);
  glVertex3f(-0.8, 1.3, 0);
  glEnd();

  glEnable(GL_CULL_FACE);
}

void Cobertura::desenha()
{
  glPushMatrix();
  Objeto::desenha(); // T.Rz.Ry.Rx.S. p
  criar();
  glPopMatrix();
}

std::string Cobertura::getClassName()
{
  return "Cobertura";
}
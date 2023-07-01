#include "Parede.h"
#include <gui.h>

using namespace std;

Parede::Parede(int id, float t_x, float t_y, float t_z,
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

void Parede::criar()
{

  // Habilita o culling para que a parede não atrapalhe a camera
  glDisable(GL_CULL_FACE);

  // Alterar a cor da parede para #1e293b
  GUI::setColor(0.1176, 0.1607, 0.2313, 1, true);

  glBegin(GL_QUADS);
  glNormal3f(0, 0.0, -1.0);
  glVertex3f(-5.0, 0.0, -0.05);
  glVertex3f(-5.0, 5.0, -0.05);
  glVertex3f(5.0, 5.0, -0.05);
  glVertex3f(5.0, 0.0, -0.05);
  glEnd();

  glEnable(GL_CULL_FACE);
}

void Parede::desenha()
{
  glPushMatrix();
  Objeto::desenha(); // T.Rz.Ry.Rx.S. p
  criar();
  glPopMatrix();
}

std::string Parede::getClassName()
{
  return "Parede";
}

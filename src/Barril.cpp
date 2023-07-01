#include "Barril.h"
#include <gui.h>

using namespace std;

Barril::Barril(int id, float t_x, float t_y, float t_z,
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
  model = new Model3DS("./3ds/barril.3DS");
}

void Barril::criar()
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

  glTranslatef(0, 0, 0);
  glRotatef(-90, 1, 0, 0);
  glScalef(0.02, 0.02, 0.02);

  model->draw(false); // Só pinta se não estiver selecionado
}

void Barril::desenha()
{
  glPushMatrix();
  Objeto::desenha(); // T.Rz.Ry.Rx.S. p
  criar();
  glPopMatrix();
}

std::string Barril::getClassName()
{
  return "Barril";
}

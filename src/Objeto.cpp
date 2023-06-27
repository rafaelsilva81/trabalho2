#include "Objeto.h"
#include <gui.h>
#include <string>

using namespace std;

void Objeto::desenha()
{

  glTranslatef(trans_x, trans_y, trans_z);
  glRotatef(rot_x, 0, 0, 1);
  glRotatef(rot_y, 0, 1, 0);
  glRotatef(rot_z, 1, 0, 0);
  glScalef(scale_x, scale_y, scale_z);
}

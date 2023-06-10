#ifndef TAMBORETE_H
#define TAMBORETE_H

#include <Objeto.h>

using namespace std;

class Tamborete : public Objeto
{
public:
  Model3DS *model;

public:
  Tamborete(
      int id,
      float t_x, float t_y, float t_z,
      float r_x, float r_y, float r_z,
      float s_x, float s_y, float s_z,
      bool sel, bool coord);
  void criar();
  void desenha();
  std::string getClassName();
};

#endif // TAMBORETE_H

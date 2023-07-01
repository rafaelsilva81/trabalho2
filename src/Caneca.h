#ifndef CANECA_H
#define CANECA_H

#include <Objeto.h>

using namespace std;

class Caneca : public Objeto
{
public:
  Model3DS *model;

public:
  Caneca(
      int id,
      float t_x, float t_y, float t_z,
      float r_x, float r_y, float r_z,
      float s_x, float s_y, float s_z,
      bool sel, bool coord);
  void criar();
  void desenha();
  std::string getClassName();
};

#endif // CANECA_H

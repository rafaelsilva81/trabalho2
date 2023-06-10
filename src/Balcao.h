#ifndef BALCAO_H
#define BALCAO_H

#include <Objeto.h>

using namespace std;

class Balcao : public Objeto
{
public:
  Balcao(
      int id,
      float t_x, float t_y, float t_z,
      float r_x, float r_y, float r_z,
      float s_x, float s_y, float s_z,
      bool sel, bool coord);
  void criar();
  void desenha();
  std::string getClassName();
};

#endif // MESA_H

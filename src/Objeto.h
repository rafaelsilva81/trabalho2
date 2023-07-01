#ifndef OBJETO_H
#define OBJETO_H

#include <string>
#include <gui.h>

class Objeto
{
public:
  int object_id;                   // save
  float trans_x, trans_y, trans_z; // translação
  float rot_x, rot_y, rot_z;       // rotação
  float scale_x, scale_y, scale_z; // escala
  bool selected;                   // indica se está selecionado
  bool show_coord;                 // mostrar coordenadas locais
  virtual void desenha();
  virtual std::string getClassName() = 0; // Palco = "Palco"
};

#endif // OBJETO_H

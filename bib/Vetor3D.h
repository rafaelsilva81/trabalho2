#ifndef VETOR3D_H
#define VETOR3D_H

#ifndef PI
  #define PI 3.14159265359
#endif

#define radToGrau(a) ((180.0/PI)*a) // converte de radiano para grau
#define grauToRad(a) ((PI/180.0)*a) // converte de grau para radiano

#include <math.h>

typedef float dReal;

class Vetor3D
{
   public:

      // coordenadas do vetor
      dReal x;
      dReal y;
      dReal z;

      Vetor3D();
      Vetor3D(dReal x, dReal y, dReal z);
      ~Vetor3D();

      void setVetor3D(dReal x, dReal y, dReal z);
      dReal modulo();
      dReal modulo2(); //quadrado do modulo (nao tira a raiz quadrada)
      void normaliza();
      Vetor3D getUnit();
      Vetor3D projectedOn(Vetor3D v);
      void recebe(Vetor3D v);
      Vetor3D soma(Vetor3D v);
      void add(Vetor3D v);
      Vetor3D subtracao(Vetor3D v);
      Vetor3D multiplicacao(dReal escalar);
      dReal getDistance(Vetor3D v);
      Vetor3D prodVetorial(Vetor3D v);
      dReal prodEscalar(Vetor3D v);

      Vetor3D operator+(Vetor3D v);
      Vetor3D operator-(Vetor3D v);
      Vetor3D operator*(dReal escalar);
      dReal operator*(Vetor3D v);
      Vetor3D operator^(Vetor3D v);
      Vetor3D operator!();
};

#endif

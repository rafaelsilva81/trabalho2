#include "Camera.h"
//---------------------------------------------------------------------------
Camera::Camera()
{
  e = Vetor3D();
  c = Vetor3D();
  u = Vetor3D();

  e.x=0;
  e.y=1;
  e.z=10;

  c.x=0;
  c.y=1;
  //c.z=0 ou e.z-1;

  u.x=0;
  u.y=1;
  u.z=0;

  estilo = 0;
}
//---------------------------------------------------------------------------
Camera::Camera(Vetor3D e, Vetor3D c, Vetor3D u)
{
  this->e = Vetor3D();
  this->c = Vetor3D();
  this->u = Vetor3D();

  this->e.x=e.x;
  this->e.y=e.y;
  this->e.z=e.z;

  this->c.x=c.x;
  this->c.y=c.y;
  this->c.z=c.z;

  this->u.x=u.x;
  this->u.y=u.y;
  this->u.z=u.z;

  estilo = 0;
}
//---------------------------------------------------------------------------
Camera::Camera(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat cx, GLfloat cy, GLfloat cz, GLfloat ux, GLfloat uy, GLfloat uz)
{
  e = Vetor3D();
  c = Vetor3D();
  u = Vetor3D();

  e.x=ex;
  e.y=ey;
  e.z=ez;

  c.x=cx;
  c.y=cy;
  c.z=cz;

  u.x=ux;
  u.y=uy;
  u.z=uz;

  estilo = 0;
}
//---------------------------------------------------------------------------
void Camera::adaptavetorcdisttojogo(){
    //vetor do olho(eye) ao centro(center)
    Vetor3D Vec = c.subtracao(e);
    //normalizando o Vec
    Vec.normaliza();
    //adaptando o vetor c
    c = e.soma(Vec);
}
//---------------------------------------------------------------------------
void Camera::adaptavetorcjogotodist(GLfloat r){
    //vetor do olho(eye) ao centro(center)
    Vetor3D Vec = c.subtracao(e);
    //adaptando o vetor c
    c = e.soma(Vec.multiplicacao(r));
}
//---------------------------------------------------------------------------

#include "CameraDistante.h"
//---------------------------------------------------------------------------
CameraDistante::CameraDistante() : Camera()
{
  c.z=0;

  estilo = CAMDIST;
}
//---------------------------------------------------------------------------
CameraDistante::CameraDistante(Vetor3D e, Vetor3D c, Vetor3D u) :
      Camera(e, c, u)
{
  estilo = CAMDIST;
}
//---------------------------------------------------------------------------
CameraDistante::CameraDistante(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat cx, GLfloat cy, GLfloat cz, GLfloat ux, GLfloat uy, GLfloat uz) :
      Camera(ex, ey, ez, cx, cy, cz, ux, uy, uz)
{
  estilo = CAMDIST;
}
//---------------------------------------------------------------------------
//desloca o olho em direcao ao centro
void CameraDistante::zoom(GLfloat new_y, GLfloat last_y){
  //vetor do olho(eye) ao centro(center)
  Vetor3D Vec = c - e; // -z_
  //normalizando o Vec
  !Vec; //normaliza (torna unitario)

  //estrategia para nao deixar o olho passar do centro
  Vetor3D eNovo = e + ( Vec * ( (new_y - last_y)/20.0 ) );
  if ( (c - eNovo) * (Vec) >= 0.0001 ) { //se e e eNovo estao do mesmo lado em relacao a c
    e = eNovo;
  }
}
//---------------------------------------------------------------------------
void CameraDistante::translatex(GLfloat new_x, GLfloat last_x){
  //vetor do olho(eye) ao centro(center)
  Vetor3D Vec = c - e; // -z_
  //x local
  Vetor3D x_ = Vec ^ u; //x_
  !x_; //normaliza (torna unitario)

  e = e + ( x_ * ( Vec.modulo()*(last_x - new_x)/300.0 ) );
  c = c + ( x_ * ( Vec.modulo()*(last_x - new_x)/300.0 ) );
}
//---------------------------------------------------------------------------
void CameraDistante::translatey(GLfloat new_y, GLfloat last_y){
  //vetor do olho(eye) ao centro(center)
  Vetor3D Vec = c - e; // -z_

  e = e - ( u * ( Vec.modulo()*(last_y - new_y)/300.0 ) );
  c = c - ( u * ( Vec.modulo()*(last_y - new_y)/300.0 ) );
}
//---------------------------------------------------------------------------
void CameraDistante::rotatex(GLfloat new_y, GLfloat last_y){
  //vetor do centro(center) ao olho(eye)
  Vetor3D Vce = e - c; // z_
  //distancia do centro(center) ao olho(eye)
  GLfloat Dce = Vce.modulo();
  //deslocando o olho verticalmente
  e = e + ( u * ( ((1.0/30.0)*Dce)*(new_y - last_y)/5.0 ) );
  //mantendo distancia (raio/rotacao) consistente
  //vetor do centro(center) ao novo olho(eye)
  Vce = e - c;
  !Vce; //normaliza (torna unitario)
  Vce = Vce * ( Dce );
  e = c + Vce;

  //mantendo u perpendicular a x_ e z_ (u = y_)
  //x local
  Vetor3D x_ = u ^ Vce; //x_ (neste caso, nao precisa usar x_ unitario)
  u = Vce ^ x_;
  !u; //normaliza (torna unitario)
}
//---------------------------------------------------------------------------
void CameraDistante::rotatey(GLfloat new_x, GLfloat last_x){
  //vetor do centro(center) ao olho(eye)
  Vetor3D Vce = e - c; // z_
  //distancia do centro(center) ao olho(eye)
  GLfloat Dce = Vce.modulo();
  //deslocando o olho horizontalmente
  //x local
  Vetor3D x_ = u ^ Vce; //x_
  !x_; //normaliza (torna unitario)
  e = e + ( x_ * ( ((1.0/30.0)*Dce)*(last_x - new_x)/5.0 ) );
  //mantendo distancia (raio/rotacao) consistente
  //vetor do centro(center) ao novo olho(eye)
  Vce = e - c;
  !Vce; //normaliza (torna unitario)
  Vce = Vce * ( Dce );
  e = c + Vce;

  //novo-----------------------------------
  //atualizacao de u correspondente a nao deixar rotacionar em torno de z_
  Vetor3D up;
  if (u.y>=0.0) {
    up = Vetor3D(0.0,1.0,0.0);
  } else {
    up = Vetor3D(0.0,-1.0,0.0);
  }
  //mantendo u perpendicular a x_ e z_ (u = y_)
  //x local atualizado
  x_ = up ^ Vce; //x_ (neste caso, nao precisa usar x_ unitario)
  u = Vce ^ x_;
  !u; //normaliza (torna unitario)
  //fim_novo-------------------------------
}
//---------------------------------------------------------------------------
void CameraDistante::rotatez(GLfloat new_x, GLfloat last_x){
  //vetor do olho(eye) ao centro(center)
  Vetor3D Vec = c - e; // -z_
  //x local
  Vetor3D x_ = Vec ^ u; //x_
  !x_; //normaliza (torna unitario)

  //modificando o vetor up
  u = u + ( x_ * ( (last_x - new_x)/300.0 ) );
  !u; //normaliza (torna unitario)
}
//---------------------------------------------------------------------------
//passando o ponto local a camera (x,y,-1) para as coordenadas do mundo
Vetor3D CameraDistante::getPickedPoint(GLfloat x, GLfloat y){
  //calculando a base da camera
  //vetor do centro(center) ao olho(eye) - Zpos
  Vetor3D Vce = e.subtracao(c);
  Vce.normaliza();
  //vetor no sentido positivo da direcao x
  Vetor3D Xpos = u.prodVetorial(Vce);
  Xpos.normaliza();

  //mudanca da base da camera para a base do mundo (canonica)
  float dx = Xpos.x * x + u.x * y + Vce.x * -1;
  float dy = Xpos.y * x + u.y * y + Vce.y * -1;
  float dz = Xpos.z * x + u.z * y + Vce.z * -1;

  //translacao em relacao a posicao da camera
  dx += e.x;
  dy += e.y;
  dz += e.z;

  return Vetor3D(dx,dy,dz);
}
//---------------------------------------------------------------------------

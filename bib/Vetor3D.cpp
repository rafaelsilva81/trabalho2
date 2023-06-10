#include "Vetor3D.h"
//---------------------------------------------------------------------------
//Construtor
Vetor3D::Vetor3D()
{
  this->x = 0.0;
  this->y = 0.0;
  this->z = 0.0;
}
//---------------------------------------------------------------------------
//Construtor
Vetor3D::Vetor3D(dReal x, dReal y, dReal z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}
//---------------------------------------------------------------------------
//Destrutor
Vetor3D::~Vetor3D()
{
}
//---------------------------------------------------------------------------
//atualiza o vetor
void Vetor3D::setVetor3D(dReal x, dReal y, dReal z) {
  this->x = x;
  this->y = y;
  this->z = z;
}
//---------------------------------------------------------------------------
//retorna o modulo do vetor
dReal Vetor3D::modulo() {
  return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}
//---------------------------------------------------------------------------
//retorna o quadrado do modulo do vetor (nao tira a raiz quadrada)
dReal Vetor3D::modulo2() {
  return (this->x * this->x + this->y * this->y + this->z * this->z);
}
//---------------------------------------------------------------------------
//normaliza o vetor
void Vetor3D::normaliza() {
  dReal m = modulo();

  if (m > 0.0) {
    m = 1 / m;

    this->x *= m; // X
    this->y *= m; // Y
    this->z *= m; // Z
  }
}
//---------------------------------------------------------------------------
Vetor3D Vetor3D::getUnit() {
  Vetor3D u = *this;
    u.normaliza();

  return u;
}
//---------------------------------------------------------------------------
Vetor3D Vetor3D::projectedOn(Vetor3D v) {
  Vetor3D v_u = v.getUnit();
  Vetor3D projection = v_u.multiplicacao( this->prodEscalar( v_u ) );

  return projection;
}
//---------------------------------------------------------------------------
//atribuicao
void Vetor3D::recebe(Vetor3D v) {
  this->x = v.x;
  this->y = v.y;
  this->z = v.z;
}
//---------------------------------------------------------------------------
//soma
Vetor3D Vetor3D::soma(Vetor3D v) {
  return Vetor3D(
                 this->x + v.x,
                 this->y + v.y,
                 this->z + v.z
                 );
}
//---------------------------------------------------------------------------
//add - adiciona
void Vetor3D::add(Vetor3D v) {
  this->x += v.x;
  this->y += v.y;
  this->z += v.z;
}
//---------------------------------------------------------------------------
//subtracao
Vetor3D Vetor3D::subtracao(Vetor3D v) {
  return Vetor3D(
                 this->x - v.x,
                 this->y - v.y,
                 this->z - v.z
                 );
}
//---------------------------------------------------------------------------
//multiplicacao
Vetor3D Vetor3D::multiplicacao(dReal escalar) {
  return Vetor3D(
                 this->x * escalar,
                 this->y * escalar,
                 this->z * escalar
                 );
}
//---------------------------------------------------------------------------
//distancia
dReal Vetor3D::getDistance(Vetor3D v) {
  return subtracao(v).modulo();
}
//---------------------------------------------------------------------------
//produto vetorial
Vetor3D Vetor3D::prodVetorial(Vetor3D v) {
  return Vetor3D(
                 this->y * v.z - this->z * v.y,
                 this->z * v.x - this->x * v.z,
                 this->x * v.y - this->y * v.x
                 );
}
//---------------------------------------------------------------------------
//produto escalar
dReal Vetor3D::prodEscalar(Vetor3D v) {
    return (this->x * v.x + this->y * v.y + this->z * v.z);
}
//---------------------------------------------------------------------------
Vetor3D Vetor3D::operator+(Vetor3D v)
{
    return this->soma(v);
}
//---------------------------------------------------------------------------
Vetor3D Vetor3D::operator-(Vetor3D v)
{
    return this->subtracao(v);
}
//---------------------------------------------------------------------------
Vetor3D Vetor3D::operator*(dReal escalar)
{
    return this->multiplicacao(escalar);
}
//---------------------------------------------------------------------------
dReal Vetor3D::operator*(Vetor3D v)
{
    return this->prodEscalar(v);
}
//---------------------------------------------------------------------------
Vetor3D Vetor3D::operator^(Vetor3D v)
{
    return this->prodVetorial(v);
}
//---------------------------------------------------------------------------
Vetor3D Vetor3D::operator!()
{
    this->normaliza();
    return *this;
}
//---------------------------------------------------------------------------

#ifndef CAMERA_H
#define CAMERA_H

#define CAMDIST 1
#define CAMJOGO 2

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Vetor3D.h"

class Camera
{
   public:

      Vetor3D e;
      Vetor3D c;
      Vetor3D u;

      int estilo;

      Camera();
      Camera(Vetor3D e, Vetor3D c, Vetor3D u);
      Camera(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat cx, GLfloat cy, GLfloat cz, GLfloat ux, GLfloat uy, GLfloat uz);
      ~Camera(){};

      //vetor Vec e u sempre perpendiculares e u sempre unitario
      virtual void zoom(GLfloat, GLfloat) = 0;
      virtual void translatex(GLfloat, GLfloat) = 0;
      virtual void translatey(GLfloat, GLfloat) = 0;
      virtual void rotatex(GLfloat, GLfloat) = 0;
      virtual void rotatey(GLfloat, GLfloat) = 0;
      virtual void rotatez(GLfloat, GLfloat) = 0;
      virtual Vetor3D getPickedPoint(GLfloat, GLfloat) = 0;
      void adaptavetorcdisttojogo();
      void adaptavetorcjogotodist(GLfloat r);
};

#endif

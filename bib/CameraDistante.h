#ifndef CAMERADISTANTE_H
#define CAMERADISTANTE_H

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Camera.h"

class CameraDistante : public Camera
{
   public:

      CameraDistante();
      CameraDistante(Vetor3D e, Vetor3D c, Vetor3D u);
      CameraDistante(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat cx, GLfloat cy, GLfloat cz, GLfloat ux, GLfloat uy, GLfloat uz);
      ~CameraDistante(){};

      //vetor Vec e u sempre perpendiculares e u sempre unitario
      virtual void zoom(GLfloat, GLfloat);
      virtual void translatex(GLfloat, GLfloat);
      virtual void translatey(GLfloat, GLfloat);
      virtual void rotatex(GLfloat, GLfloat);
      virtual void rotatey(GLfloat, GLfloat);
      virtual void rotatez(GLfloat, GLfloat);
      virtual Vetor3D getPickedPoint(GLfloat, GLfloat);

};

#endif

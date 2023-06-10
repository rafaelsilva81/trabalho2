#include "Desenha.h"
//---------------------------------------------------------------------------
// Draws a simple box using the given corners
void Desenha::drawBox(GLfloat xmin, GLfloat ymin, GLfloat zmin, GLfloat xmax, GLfloat ymax, GLfloat zmax) {
  glBegin(GL_QUADS);
    glNormal3f(0.,0.,-1.);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xmin, ymin, zmin);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xmin, ymax, zmin);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xmax, ymax, zmin);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xmax, ymin, zmin);
  glEnd();

  glBegin(GL_QUADS);
    glNormal3f(1.,0.,0.);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xmax, ymin, zmin);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xmax, ymax, zmin);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xmax, ymax, zmax);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xmax, ymin, zmax);
  glEnd();

  glBegin(GL_QUADS);
    glNormal3f(0.,0.,1.);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xmax, ymin, zmax);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xmax, ymax, zmax);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xmin, ymax, zmax);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xmin, ymin, zmax);
  glEnd();

  glBegin(GL_QUADS);
    glNormal3f(-1.,0.,0.);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xmin, ymin, zmax);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xmin, ymax, zmax);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xmin, ymax, zmin);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xmin, ymin, zmin);
  glEnd();

  glBegin(GL_QUADS);
    glNormal3f(0.,1.,0.);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xmin, ymax, zmin);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xmin, ymax, zmax);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xmax, ymax, zmax);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xmax, ymax, zmin);
  glEnd();

  glBegin(GL_QUADS);
    glNormal3f(0.,-1.,0.);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xmax, ymin, zmin);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xmax, ymin, zmax);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xmin, ymin, zmax);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xmin, ymin, zmin);
  glEnd();
  }
//---------------------------------------------------------------------------
// Draws a simple box using the given corners
void Desenha::drawWireBox(GLfloat xmin, GLfloat ymin, GLfloat zmin, GLfloat xmax, GLfloat ymax, GLfloat zmax) {
  glBegin(GL_LINES);
    glVertex3f(xmin, ymin, zmin);
    glVertex3f(xmax, ymin, zmin);
    glVertex3f(xmax, ymin, zmin);
    glVertex3f(xmax, ymax, zmin);
    glVertex3f(xmax, ymax, zmin);
    glVertex3f(xmin, ymax, zmin);
    glVertex3f(xmin, ymax, zmin);
    glVertex3f(xmin, ymin, zmin);

    glVertex3f(xmin, ymin, zmax);
    glVertex3f(xmax, ymin, zmax);
    glVertex3f(xmax, ymin, zmax);
    glVertex3f(xmax, ymax, zmax);
    glVertex3f(xmax, ymax, zmax);
    glVertex3f(xmin, ymax, zmax);
    glVertex3f(xmin, ymax, zmax);
    glVertex3f(xmin, ymin, zmax);

    glVertex3f(xmin, ymin, zmin);
    glVertex3f(xmin, ymin, zmax);
    glVertex3f(xmax, ymin, zmin);
    glVertex3f(xmax, ymin, zmax);
    glVertex3f(xmax, ymax, zmin);
    glVertex3f(xmax, ymax, zmax);
    glVertex3f(xmin, ymax, zmin);
    glVertex3f(xmin, ymax, zmax);
  glEnd();
}
//---------------------------------------------------------------------------
// Draws a simple box using the given corners
//drawSelectedBox nao define normais
//cor deve ser definida desligando a iluminacao e usando glColor
void Desenha::drawSelectedBox(GLfloat xmin, GLfloat ymin, GLfloat zmin, GLfloat xmax, GLfloat ymax, GLfloat zmax) {
  float dx = (xmax - xmin)/8.0;
  float dy = (ymax - ymin)/8.0;
  float dz = (zmax - zmin)/8.0;

  glBegin(GL_LINES);
    glVertex3f(xmin, ymin, zmin);
      glVertex3f(xmin + dx, ymin, zmin);
      glVertex3f(xmax - dx, ymin, zmin);
    glVertex3f(xmax, ymin, zmin);
    glVertex3f(xmax, ymin, zmin);
      glVertex3f(xmax, ymin + dy, zmin);
      glVertex3f(xmax, ymax - dy, zmin);
    glVertex3f(xmax, ymax, zmin);
    glVertex3f(xmax, ymax, zmin);
      glVertex3f(xmax - dx, ymax, zmin);
      glVertex3f(xmin + dx, ymax, zmin);
    glVertex3f(xmin, ymax, zmin);
    glVertex3f(xmin, ymax, zmin);
      glVertex3f(xmin, ymax - dy, zmin);
      glVertex3f(xmin, ymin + dy, zmin);
    glVertex3f(xmin, ymin, zmin);

    glVertex3f(xmin, ymin, zmax);
      glVertex3f(xmin + dx, ymin, zmax);
      glVertex3f(xmax - dx, ymin, zmax);
    glVertex3f(xmax, ymin, zmax);
    glVertex3f(xmax, ymin, zmax);
      glVertex3f(xmax, ymin + dy, zmax);
      glVertex3f(xmax, ymax - dy, zmax);
    glVertex3f(xmax, ymax, zmax);
    glVertex3f(xmax, ymax, zmax);
      glVertex3f(xmax - dx, ymax, zmax);
      glVertex3f(xmin + dx, ymax, zmax);
    glVertex3f(xmin, ymax, zmax);
    glVertex3f(xmin, ymax, zmax);
      glVertex3f(xmin, ymax - dy, zmax);
      glVertex3f(xmin, ymin + dy, zmax);
    glVertex3f(xmin, ymin, zmax);

    glVertex3f(xmin, ymin, zmin);
      glVertex3f(xmin, ymin, zmin + dz);
      glVertex3f(xmin, ymin, zmax - dz);
    glVertex3f(xmin, ymin, zmax);
    glVertex3f(xmax, ymin, zmin);
      glVertex3f(xmax, ymin, zmin + dz);
      glVertex3f(xmax, ymin, zmax - dz);
    glVertex3f(xmax, ymin, zmax);
    glVertex3f(xmax, ymax, zmin);
      glVertex3f(xmax, ymax, zmin + dz);
      glVertex3f(xmax, ymax, zmax - dz);
    glVertex3f(xmax, ymax, zmax);
    glVertex3f(xmin, ymax, zmin);
      glVertex3f(xmin, ymax, zmin + dz);
      glVertex3f(xmin, ymax, zmax - dz);
    glVertex3f(xmin, ymax, zmax);
  glEnd();
}
//---------------------------------------------------------------------------
// desenha um quadrado da grade
void Desenha::drawQuad(GLfloat xmin, GLfloat y, GLfloat zmin, GLfloat lado) {
  glBegin(GL_LINES);
    glVertex3f(xmin, y, zmin);
    glVertex3f(xmin, y, zmin + lado);

    glVertex3f(xmin, y, zmin + lado);
    glVertex3f(xmin + lado, y, zmin + lado);

    glVertex3f(xmin + lado, y, zmin + lado);
    glVertex3f(xmin + lado, y, zmin);

    glVertex3f(xmin + lado, y, zmin);
    glVertex3f(xmin, y, zmin);
  glEnd();
  }
//---------------------------------------------------------------------------
// desenha a grade
void Desenha::drawGrid(int meionx, GLfloat y, int meionz, int dimensao) {
  glPushMatrix();
    int i,k;
    for (i=-meionx*dimensao; i<=(meionx-1)*dimensao; i+=dimensao)
      {
      for (k=-meionz*dimensao; k<=(meionz-1)*dimensao; k+=dimensao)
        {
        drawQuad(i, y, k, dimensao);
        }
      }
  glPopMatrix();
  }
//---------------------------------------------------------------------------
// desenha um cilindro fechado
void Desenha::gluClosedCylinder(GLUquadric* quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks) {
	gluQuadricNormals(quad, GLU_SMOOTH);			// Create Smooth Normals
    gluQuadricTexture(quad, GL_TRUE);		  		// Create Texture Coords
  glPushMatrix();
    gluCylinder(quad, base, top, height, slices, stacks);
    glTranslated(0,0,height);
    gluDisk(quad, 0, top, slices, stacks);
    glRotated(180,0,1,0);
    glTranslated(0,0,height);
    gluDisk(quad, 0, base, slices, stacks);
  glPopMatrix();
  }
//---------------------------------------------------------------------------
// desenha uma capsula (cilindro + 2 esferas nas pontas)
void Desenha::gluCapsule(GLUquadric* quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks) {
	gluQuadricNormals(quad, GLU_SMOOTH);			// Create Smooth Normals
    gluQuadricTexture(quad, GL_TRUE);		  		// Create Texture Coords
  glPushMatrix();
    gluCylinder(quad, base, top, height, slices, stacks);
    gluSphere(quad, base, slices, stacks);
    glTranslated(0,0,height);
    gluSphere(quad, top, slices, stacks);
  glPopMatrix();
  }
//---------------------------------------------------------------------------
// desenha os tres eixos x, y e z
/*
void Desenha::drawEixos(GLfloat tam) {
  const GLfloat redMaterial[]={0.3,0.,0.,1.};
  const GLfloat greenMaterial[]={0.,0.3,0.,1.};
  const GLfloat blueMaterial[]={0.,0.,0.3,1.};

  //x
    glMaterialfv(GL_FRONT, GL_AMBIENT, redMaterial);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, redMaterial);

    //Desenha::drawArrow( Vetor3D(0.0,0.0,0.0), Vetor3D(tam,0.0,0.0) );

  //y
    glMaterialfv(GL_FRONT, GL_AMBIENT, greenMaterial);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, greenMaterial);

    //Desenha::drawArrow( Vetor3D(0.0,0.0,0.0), Vetor3D(0.0,tam,0.0) );

  //z
    glMaterialfv(GL_FRONT, GL_AMBIENT, blueMaterial);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, blueMaterial);

    //Desenha::drawArrow( Vetor3D(0.0,0.0,0.0), Vetor3D(0.0,0.0,tam) );
}
*/
//---------------------------------------------------------------------------
// desenha os tres eixos x, y e z
//*
void Desenha::drawEixos(GLfloat tam) {
  const GLfloat redMaterial[]={0.3,0.,0.,1.};
  const GLfloat greenMaterial[]={0.,0.3,0.,1.};
  const GLfloat blueMaterial[]={0.,0.,0.3,1.};


  GLUquadricObj *quad = gluNewQuadric();

  glLineWidth( 2 ) ;

  //x
    glMaterialfv(GL_FRONT, GL_AMBIENT, redMaterial);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, redMaterial);
    glColor3d(0.3,0.0,0.0);

  glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(tam,0,0);
  glEnd();
  glPushMatrix();
    glRotated(90,0,1,0);
    glTranslated(0,0,tam);
    Desenha::gluClosedCylinder(quad, 0.1*tam, 0, 0.2*tam, 10, 10);
  glPopMatrix();

  //y
    glMaterialfv(GL_FRONT, GL_AMBIENT, greenMaterial);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, greenMaterial);
    glColor3d(0.0,0.3,0.0);

  glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(0,tam,0);
  glEnd();
  glPushMatrix();
    glRotated(90,-1,0,0);
    glTranslated(0,0,tam);
    Desenha::gluClosedCylinder(quad, 0.1*tam, 0, 0.2*tam, 10, 10);
  glPopMatrix();

  //z
    glMaterialfv(GL_FRONT, GL_AMBIENT, blueMaterial);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, blueMaterial);
    glColor3d(0.0,0.0,0.3);

  glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(0,0,tam);
  glEnd();
  glPushMatrix();
    glTranslated(0,0,tam);
    Desenha::gluClosedCylinder(quad, 0.1*tam, 0, 0.2*tam, 10, 10);
  glPopMatrix();

  glLineWidth( 1 ) ;

  gluDeleteQuadric( quad );
  }
//*/
//---------------------------------------------------------------------------
//aplica T.R.v
void Desenha::setTransformODE(const dReal* pos, const dReal* R)
{
  GLfloat matrix[16];
    matrix[0]=R[0];
    matrix[1]=R[4];
    matrix[2]=R[8];
    matrix[3]=0;
    matrix[4]=R[1];
    matrix[5]=R[5];
    matrix[6]=R[9];
    matrix[7]=0;
    matrix[8]=R[2];
    matrix[9]=R[6];
    matrix[10]=R[10];
    matrix[11]=0;
    matrix[12]=pos[0];
    matrix[13]=pos[1];
    matrix[14]=pos[2];
    matrix[15]=1;

  glMultMatrixf (matrix);
}
//---------------------------------------------------------------------------


#ifndef GUI_H
#define GUI_H

typedef void (* displayFunction)( void );
typedef void (* keyFunction)( unsigned char, int, int );
typedef void (* mouseButtonFunction)( int, int, int, int );

#include "extra.h"
#include "../bib/model3ds.h"

class GUI {
    private:
        int id;
        const char *wTitle; //window title
        int wWidth, wHeight; //window dimensions
        displayFunction display;
        keyFunction key;
        mouseButtonFunction mouseButton;

    public:
        GUI( int width, int height, displayFunction dFunction = glutGUI::defaultDisplay, keyFunction kFunction = glutGUI::defaultKey, mouseButtonFunction mbFunction = glutGUI::defaultMouseButton, const char *title = "GLUT" );
        void GLUTInit();
        void GLInit();
        ~GUI();

        void setTitle(const char *title);
        void setDimensions(int width, int height);
        void setDisplay( displayFunction dFunction );
        void setKey( keyFunction kFunction );
        void setMouseButton( mouseButtonFunction mbFunction );

        static void displayInit();
        static void displayEnd();
        static void keyInit(unsigned char key, int x, int y);
        static void mouseButtonInit(int button, int state, int x, int y);
        static void setLight(int id, float posx, float posy, float posz, bool onOffKeyDefault = false, bool attenuated = true, bool low = false, bool hidden = false, bool pontual = true, bool spot = false, bool onOffUserControl = true);
        static void setColor(float r, float g, float b, float a = 1.0, bool specular = false);

        //---------------transformacoes---------------
        static void glShearXf(float shY, float shZ); //Y e Z fixos
        static void glShearYf(float shX, float shZ); //X e Z fixos
        static void glShearZf(float shX, float shY); //X e Y fixos
        static void glShearXYf(float shX, float shY); //Z fixo
        static void glShearXZf(float shX, float shZ); //Y fixo
        static void glShearYZf(float shY, float shZ); //X fixo
        static void glReflectPlaneYZf(); //inverte sinal de X
        static void glReflectPlaneXZf(); //inverte sinal de Y
        static void glReflectPlaneXYf(); //inverte sinal de Z
        //---------------transformacoes---------------

        //-------------------camera-------------------
        static void camera2global( Vetor3D olho, Vetor3D centro, Vetor3D up );
        static void global2camera( Vetor3D olho, Vetor3D centro, Vetor3D up );
        static void global2cameraAlternativa( Vetor3D olho, Vetor3D centro, Vetor3D up );
        //-------------------camera-------------------

        //-------------------sombra-------------------
        static void shadowMatrixYk(GLfloat shadowMat[4][4], GLfloat lightpos[4], GLfloat k);
        static void shadowMatrix(GLfloat shadowMat[4][4], GLfloat groundplane[4], GLfloat lightpos[4]);
        //-------------------sombra-------------------

        //-------------------picking------------------
        static int processHits(GLint hits, GLuint buffer[]);
        static void pickingInit(GLint cursorX, GLint cursorY, int w, int h, GLuint* selectBuf, int BUFSIZE);
        static int pickingClosestName(GLuint* selectBuf, int BUFSIZE);
        //-------------------picking------------------

        //-------------------viewPorts------------------
        static void glScissoredViewport(int x, int y, int width, int height);
        //-------------------viewPorts------------------

        static void drawSphere(float x, float y, float z, float radius);
        static void drawQuad(float width = 5.0, float height = 5.0, float discrWidth = 0.3, float discrHeight = 0.3, float texWidth = 5.0, float texHeight = 5.0, bool inverted = false);
        static void drawOriQuad(float angle = 0.0, float ex = 1.0, float ey = 0.0, float ez = 0.0, float width = 5.0, float height = 5.0, float discrWidth = 0.3, float discrHeight = 0.3, float texWidth = 5.0, float texHeight = 5.0, bool inverted = false);
        static void drawQuadBox(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax, float discrWidth = 0.3, float discrHeight = 0.3, bool inverted = false);
        static void drawBox(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax, bool inverted = false);
        static void drawScaledBox(float scale, float xmin, float ymin, float zmin, float xmax, float ymax, float zmax, bool inverted = false);
        static void drawFloor(float width = 5.0, float height = 5.0, float discrWidth = 0.3, float discrHeight = 0.3, float texWidth = 5.0, float texHeight = 5.0);
        static void drawPlane(GLfloat planeABCD[], float width = 5.0, float height = 5.0, float discrWidth = 0.03, float discrHeight = 0.03, float texWidth = 5.0, float texHeight = 5.0);
        static void drawPlaneAL(GLfloat planeABCD[], float width = 15.0, float height = 15.0, float discrWidth = 0.5, float discrHeight = 0.5, float texWidth = 15.0, float texHeight = 15.0);
        static void drawPlane(Vetor3D n, GLfloat distMinPlanoOrigem, float width = 5.0, float height = 5.0, float discrWidth = 0.03, float discrHeight = 0.03, float texWidth = 5.0, float texHeight = 5.0);
        static void drawOrigin(float tamanho = 0.1);
        static void drawOriginAL(float tam = 0.1, float discr = 0.5);
        static void drawCamera(float tamanho = 0.5);
        static void draw3ds(Model3DS &model3DS, float tx=0, float ty=0, float tz=0,
                                                float ax=0, float ay=0, float az=0,
                                                float sx=1, float sy=1, float sz=1);
};

#endif

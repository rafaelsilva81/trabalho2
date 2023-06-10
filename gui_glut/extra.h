#ifndef EXTRA_H
#define EXTRA_H

//#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <iomanip>
using namespace std;

#include "../bib/CameraDistante.h"
#include "../bib/CameraJogo.h"
#include "../bib/Desenha.h"

//texture
//#include "OpenTextures.h"

//definido para usar no metodo autoCamMotion
#define HALF_PI 237.58 //90 graus => 237.58

enum MouseLock{NOT_LOCKED,ONLY_X,ONLY_Y};
enum Axis{AXIS_X,AXIS_Y,AXIS_Z};

class glutGUI {
public:
    static bool iluminacao3D;// = true;

    static int width;// = 400;
    static int height;// = 300;

    static bool perspective;// = true;
    static float orthof;// = 0.003; //orthoFactor

    static bool picking;// = false;

    static bool lbpressed;// = false;
    static bool mbpressed;// = false;
    static bool rbpressed;// = false;

    static MouseLock mouse_lock;// = NOT_LOCKED;
    static float last_x;// = 0.0;
    static float last_y;// = 0.0;

    static Camera* cam;// = new CameraDistante();
    static float savedCamera[9];

    static int contRotation;// = 9999;
    static float value;// = 90;
    static Axis axis;// = AXIS_Y;
    static int nIterations;// = 10;


    static int slices;// = 200; //400;//16;
    static int stacks;// = 200; //400;//16;

    static int posCam;// = 1;

    static bool iluminacao;// = true;
    static bool enabled_light[8];// = {false,false,false,false,false,false,false,false};
    static bool hidden_light[8];// = {false,false,false,false,false,false,false,false};
    static bool pontual_light[8];// = {true,true,true,true,true,true,true,true};
    static bool spot_light[8];// = {false,false,false,false,false,false,false,false};
    static float spot_angle;// = 25.0;
    static bool trans_luz;// = false;

    static bool obj_transp;// = false;
    static float transparencia;// = 0.5;

    static bool multiple_viewports;// = false;

    static bool draw_eixos;// = true;

    static bool trans_obj;// = false;

    static float tx;// = 0.0;
    static float ty;// = 0.0;
    static float tz;// = 0.0;

    static float ax;// = 0.0;
    static float ay;// = 0.0;
    static float az;// = 0.0;

    static float sx;// = 1.0;
    static float sy;// = 1.0;
    static float sz;// = 1.0;

    static float lx;// = 0.0;
    static float ly;// = 0.0;
    static float lz;// = 0.0;

    static float dtx;// = 0.0;
    static float dty;// = 0.0;
    static float dtz;// = 0.0;

    static float dax;// = 0.0;
    static float day;// = 0.0;
    static float daz;// = 0.0;

    static float dsx;// = 0.0;
    static float dsy;// = 0.0;
    static float dsz;// = 0.0;

    //static float delta;// = 5.0;

public:
    static void resize(int w, int h);
    static void defaultDisplay();
    static void defaultKey(unsigned char key, int x, int y);
    static void autoCamMove(float value, Axis axis, int nIterations = 10);
    static void autoCamMotion(float value, Axis axis, int nIterations = 10);
    static void idle(void);
    static void defaultMouseButton(int button, int state, int x, int y);
    static void mouseMove(int x, int y);

    static void multGLMatrixByVector(float res[], float matriz[], float entr[]);
    static void showGLMatrixIn2D(float matriz[]);
    static void composite();
    static void showLocalAndGlobalCoords(float pl[]);
};

#endif // EXTRA_H

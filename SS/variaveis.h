#include <iostream>
#include <fstream>

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>

using namespace std;
int xCursor, yCursor, zCursor;  //guarda o centro do cursor
// Variáveis das luzes
static int distancia = 0;
static bool light0Ligada = 1;   // Luz branca ligada?
static bool light1Ligada = 1;   // Luz verde ligada?
static float d = 1.0;           // Intensidade da cor difusa da luz branca
static float e = 1.0;           // Intensidade da cor especular da luz branca
static float m = 0.2;           // Intensidade da luz ambiente global
static float p = 1.0;           // A luz branca é posicional?
static float s = 50.0;          // Expoente especular do material (shininess)
float matShine[] = { s };                       // expoente especular (shininess)
static float xAngle = 0.0, yAngle = 0.0;        // Rotação da luz branca
static bool isLightingOn = false;               // O sistema de iluminação está ligado?


// Variáveis camêra e mouse
//static float xMouse = 250, yMouse = 250;        // (x,y) do ponteiro do mouse
static float larguraJanela, alturaJanela;       // (w,h) da janela
static bool localViewer = false;

// Variáveis fontes
static long font = (long)GLUT_BITMAP_8_BY_13;   // Fonte usada para imprimir na tela
static char theStringBuffer[10];                // String buffer



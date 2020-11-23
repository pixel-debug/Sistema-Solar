#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "variaveis.h"
#include "texto.h"
#include "planetas.h"
#include "camera.h"
#include "luz.h"



void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 27:    //aperte ESC para fechar
            exit(0);
            break;
        case 's':   //andar pelo plano X-Z utilizando W A S D
            xCursor++;
            distancia -= 0.9f;
            break;
        case 'w':
            xCursor--;
            distancia += .9f;
            break;
        case 'a':
            zCursor++;
            break;
        case 'd':
            zCursor--;
            break;
        case '1':
            modoCAM = TERCEIRA_PESSOA;
            break;
        case '2':
            modoCAM = PRIMEIRA_PESSOA;
            break;
        case '3':
            modoCAM = ESTATICA;
        case 'o':
        case 'O':
            if (light0Ligada) light0Ligada = false;
            else light0Ligada = true;
            break;
        case 'l':
        case 'L':
            isLightingOn = !isLightingOn;
        break;
        default:
            break;
    }
}

// Callback para setas do teclado
void specialKeyInput(int key, int x, int y)
{
    if(key == GLUT_KEY_DOWN)
    {
        xAngle++;
        if (xAngle > 360.0) xAngle -= 360.0;
    }
    if(key == GLUT_KEY_UP)
    {
        xAngle--;
        if (xAngle < 0.0) xAngle += 360.0;
    }
    if(key == GLUT_KEY_RIGHT)
    {
        yAngle++;
        if (yAngle > 360.0) yAngle -= 360.0;
    }
    if(key == GLUT_KEY_LEFT)
    {
        yAngle--;
        if (yAngle < 0.0) yAngle += 360.0;
    }
    glutPostRedisplay();
}

// callback de atualização
void atualiza(int time) {
    glutPostRedisplay();
    glutTimerFunc(time, atualiza, time);
}

void redimensiona(int w, int h){
    larguraJanela = w;
    alturaJanela = h;
    glEnable(GL_DEPTH_TEST);                // Ativa o Z buffer
    glViewport (0, 0, w, h);                //define a proporção da janela de visualização
    glMatrixMode (GL_PROJECTION);           //define o tipo de matriz de transformação que será utilizada
    glLoadIdentity();                       //carrega a matriz identidade do tipo GL_PROJECTION configurado anteriormente
    gluPerspective(60.0, (float)w/(float)h, 0.2, 400.0);    //funciona como se fosse o glOrtho, mas para o espaço 3D
    glMatrixMode(GL_MODELVIEW);                             //ativa o modo de matriz de visualização para utilizar o LookAt
}


void rotaciona() {
    rodaMarte += 3.1f;
   // anguloSol += .1f;
    rodaJupiter += 3.1f;
    rodaMercurio += 1.0f;
    rodaVenus += 5.0f;
    rodaTerra += 3.0f;
    rodaUrano += 3.1f;
    rodaPlutao += 3.1f;
    rodaSaturno += 3.1f;
    rodaNetuno += 3.1f;
    glutPostRedisplay();
}
void rotacionaEsfera() {
    anguloMarte += .1f;
    anguloSol += .1f;
    anguloJupiter += .1f;
    anguloMercurio += .1f;
    anguloVenus += .1f;
    anguloTerra += .1f;
    anguloUrano += .1f;
    anguloPlutao += .1f;
    anguloSaturno += .1f;
    anguloNetuno += .1f;
    rotaciona();
    glutPostRedisplay();
}
void inicializa(){
    glClearColor(0,0,0, 0.0);                          //cor de fundo branca
    glEnable(GL_BLEND);                                //ativa a mesclagem de cores
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //ativando o blend, podemos criar objetos transparentes
    xCursor = 0;                                       //a câmera começa olhando para o ponto 0
    yCursor = 0;
    zCursor = 0;

    solTexture = carregaTextura("imagens/sun.jpg");
    marsTexture = carregaTextura("imagens/mars.jpg");
    jupiterTexture = carregaTextura("imagens/jupiter.jpg");
    mercurioTexture = carregaTextura("imagens/mercurio.jpeg");
    venusTexture = carregaTextura("imagens/venus.jpg");
    terraTexture = carregaTextura("imagens/terra.jpg");
    uranoTexture = carregaTextura("imagens/urano.jpg");
    plutaoTexture = carregaTextura("imagens/plutao.jpg");
    netunoTexture = carregaTextura("imagens/netuno.jpg");
    saturnoTexture = carregaTextura("imagens/saturno.jpg");
    spaceTexture = carregaTextura("imagens/space.jpg");

    // Propriedades do material da esfera
    float matAmbAndDif[] = {1.0, 1.0, 1.0, 1.0};    // cor ambiente e difusa: branca
    float matSpec[] = { 1.0, 1.0, 1,0, 1.0 };       // cor especular: branca

    // Definindo as propriedades do material
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Não mostrar faces do lado de dentro
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
}

//função que desenhará tudo o que aparece na tela
void desenhaCena() {
    
    luzes();
   // informacoesTela();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    posicaoCamera();

 // Define (atualiza) o valor do expoente de especularidade
    matShine[0] = s;
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    glColor3f(1, 1, 1);
    
   /* glMaterialfv(GL_FRONT, GL_DIFFUSE, matShine);
    glTranslatef(-2, 10, 0);
    solidSphere(1, 100, 20);
    */
    geraMundos();
    geraOrbita();
    glutSwapBuffers();
}


int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition (0, 0);

    glutCreateWindow("Sistema Solar");
    // glutEnterGameMode();                 // fullscreen baby! 
    // glutSetCursor(GLUT_CURSOR_NONE);     // esconde o cursor do sistema

    glutDisplayFunc(desenhaCena);
    glutReshapeFunc(redimensiona);
    // atualização próxima de 60fps (1000/16 = 62.5 fps
    glutTimerFunc(16, atualiza, 16);

    glutKeyboardFunc(teclado);
    // usada para capturar o posicionamento do mouse
    glutPassiveMotionFunc(posicionaCamera);
    
//    glutIdleFunc(rotaciona);
    glutIdleFunc(rotacionaEsfera);
    inicializa();
    glutMainLoop();

    return 0;
}

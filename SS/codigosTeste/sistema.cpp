#include <iostream>
#include <fstream>

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>

#include "variaveis.h"
#include "texto.h"
#include "planetas.h"
#include "camera.h"
GLuint carregaTextura(const char* arquivo){
	// Carrega a textura
    GLuint idTextura = SOIL_load_OGL_texture
	(
		arquivo,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(idTextura == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }
    

    // Esconder o ponteiro do mouse quando dentro da janela
   // glutSetCursor(GLUT_CURSOR_NONE);
   return idTextura;
}
// Configuração inicial do OpenGL e GLUT
void setup(void)
{
    //glClearColor(.4,.4,.4, 0.0);                    // fundo cinza
    glClearColor(0,0,0, 0.0);
    glEnable(GL_DEPTH_TEST);                        // Ativa teste Z

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
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

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
}



// Callback de desenho
void desenhaCena()
{
    // Limpa a tela e o z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

//    informacoesTela();

    // Posiciona a câmera de acordo com posição x,y do mouse na janela
    gluLookAt(1*(xMouse-larguraJanela/2)/(larguraJanela/16), -1*(yMouse-alturaJanela/2)/(alturaJanela/16) + 3, 5,
              0, 0, 0,
              0, 1, 0);

    // Define (atualiza) o valor do expoente de especularidade
    matShine[0] = s;
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    glColor3f(1, 1, 1);

    
   /* glMaterialfv(GL_FRONT, GL_DIFFUSE, matShine);
    glTranslatef(-2, 10, 0);
    solidSphere(1, 100, 20);
*/
    geraMundos();
    glutSwapBuffers();
}

// Callback do evento de teclado
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    default:
        break;
    }
    glutPostRedisplay();
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

// Callback de redimensionamento
void resize(int w, int h)
{
    larguraJanela = w;
    alturaJanela = h;

    glViewport (0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w/(float)h, 0.2, 400.0);
    glMatrixMode(GL_MODELVIEW);
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
    glutPostRedisplay();
}


int main(int argc, char *argv[])
{
  //  imprimirAjudaConsole();
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("Luz e Materiais");
    glutDisplayFunc(desenhaCena);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
   // glutPassiveMotionFunc(posicionaCamera); //comanda a camera
    glutSpecialFunc(specialKeyInput);
    glutIdleFunc(rotacionaEsfera);

    setup();

    glutMainLoop();
}

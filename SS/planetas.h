#include <iostream>
#include <fstream>

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>

// Variáveis MARTE
static float anguloMarte = 10;                 // Rotação da esfera em torno do eixo y
static int marteLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static int marsTexture;
static bool usarMarte = true;

// Variáveis VENUS
static float anguloVenus = 30;                 // Rotação da esfera em torno do eixo y
static int venusLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static int venusTexture;
static bool usarVenus = true;

// Variáveis TERRA
static float anguloTerra = 10;                 // Rotação da esfera em torno do eixo y
static int terraLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static int terraTexture;
static bool usarTerra = true;

// Variáveis PLUTAO
static float anguloPlutao = 10;                 // Rotação da esfera em torno do eixo y
static int plutaoLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static int plutaoTexture;
static bool usarPlutao = true;

// Variáveis SATURNO
static float anguloSaturno = 10;                 // Rotação da esfera em torno do eixo y
static int saturnoLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static int saturnoTexture;
static bool usarSaturno = true;

// Variáveis MERCURIO
static float anguloMercurio = 90;                 // Rotação da esfera em torno do eixo y
static int mercurioLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static int mercurioTexture;
static bool usarMercurio = true;

// Variáveis URANO
static float anguloUrano = 10;                 // Rotação da esfera em torno do eixo y
static int uranoLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static int uranoTexture;
static bool usarUrano = true;

// Variáveis JUPITER
static float anguloJupiter = 78;                 // Rotação da esfera em torno do eixo y
static int jupiterLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static int jupiterTexture;
static bool usarJupiter = true;

// Variáveis NETUNO
static float anguloNetuno = 0;                 // Rotação da esfera em torno do eixo y
static int netunoLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static int netunoTexture;
static bool usarNetuno = true;

// Variáveis SOL
static float anguloSol = 0;                 // Rotação da esfera em torno do eixo y
static int solLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static int solTexture;
static bool usarSol = true;

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

void solidSphere(float radius, int stacks, int columns){
    GLUquadric* quadObj = gluNewQuadric();
    gluQuadricDrawStyle(quadObj, GLU_FILL);
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    gluQuadricTexture(quadObj, GL_TRUE);
    gluSphere(quadObj, radius, stacks, columns);
    gluDeleteQuadric(quadObj);
}
void aneis(float anguloRotacao, float anguloInclinacao, int posicao, GLdouble dentro, GLdouble fora){
    GLUquadric *disk;
    disk = gluNewQuadric(); 

    glPushMatrix();
        glRotatef(anguloRotacao, 0, -1, 0); // gira para o outro lado
        glRotatef(anguloInclinacao, 1, 0, 0);
        glTranslatef(posicao, -1, 0); 
        gluDisk(disk, dentro, fora, 600, 600);
    glPopMatrix();
    gluDeleteQuadric(disk);
}



void geraMundos(){

    
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, solTexture);
    
    glPushMatrix();
        glRotatef(anguloSol, 0, 1, 0);
        glRotatef(90, 1, 0, 0);
        solidSphere(10.0, solLados, solLados);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, mercurioTexture);   
    glPushMatrix();
        glRotatef(anguloMercurio, 0, 1, 0);
        glRotatef(90, 1, 0, 0);
        glTranslatef(0, -20.0, 0); //posiciona em outro ponto
        solidSphere(3.0, mercurioLados, mercurioLados);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, venusTexture);   
    glPushMatrix();
        glRotatef(anguloVenus, 0, 1, 0);
        glRotatef(90, 1, 0, 0);
        glTranslatef(0, 30.0, 0); //posiciona em outro ponto
        solidSphere(4.0, venusLados, venusLados);
    glPopMatrix();
    
    glBindTexture(GL_TEXTURE_2D, terraTexture);   
    glPushMatrix();
        glRotatef(anguloTerra, 0, -1, 0); // gira para o outro lado
        glRotatef(90, 1, 0, 0);
        glTranslatef(0, -40, 0); 
        solidSphere(5.0, terraLados, terraLados);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, marsTexture);   
    glPushMatrix();
        glRotatef(anguloMarte, 0, 1, 0);
        glRotatef(90, 1, 0, 0);
        glTranslatef(0, 50.0, 0); //posiciona em outro ponto
        solidSphere(6.0, marteLados, marteLados);
    glPopMatrix();
    
    
    glBindTexture(GL_TEXTURE_2D, jupiterTexture);   
    glPushMatrix();
        glRotatef(anguloJupiter, 0, -1, 0); // gira para o outro lado
        glRotatef(90, 1, 0, 0);
        glTranslatef(0, -60, 0); 
        solidSphere(8.0, jupiterLados, jupiterLados);
    glPopMatrix();



    glBindTexture(GL_TEXTURE_2D, saturnoTexture);  
    glPushMatrix();
        aneis(anguloSaturno - 90,43,-60,9.0,15.0);
        glRotatef(anguloSaturno, 0, -1, 0); // gira para o outro lado
        glRotatef(90, 1, 0, 0);
        glTranslatef(0, 60, 0); 
        solidSphere(6.0, saturnoLados, saturnoLados);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, uranoTexture);   
    glPushMatrix();
        glRotatef(anguloUrano, 0, -1, 0); // gira para o outro lado
        glRotatef(90, 1, 0, 0);
        glTranslatef(0, -70, 0); 
        solidSphere(5.0, uranoLados, uranoLados);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, netunoTexture);   
    glPushMatrix();
        glRotatef(anguloNetuno, 0, -1, 0); // gira para o outro lado
        glRotatef(90, 1, 0, 0);
        glTranslatef(0, 70, 0); 
        solidSphere(4.0, netunoLados, netunoLados);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, plutaoTexture);   
    glPushMatrix();
        glRotatef(anguloPlutao, 0, -1, 0); // gira para o outro lado
        glRotatef(-90, 1, 0, 0);
        glTranslatef(0, -80, 0); 
        solidSphere(3.0, plutaoLados, plutaoLados);
    glPopMatrix();

    
    
    glDisable(GL_TEXTURE_2D);
    

}
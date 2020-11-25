#include <iostream>
#include <fstream>

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>

static int spaceTexture;

// Variáveis MARTE
static float anguloMarte = 10;                 // Rotação da esfera em torno do eixo y
static int marteLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static int marsTexture;
static bool usarMarte = true;
static float rodaMarte = 10;

// Variáveis VENUS
static float anguloVenus = 30;                 // Rotação da esfera em torno do eixo y
static int venusLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static int venusTexture;
static bool usarVenus = true;
static float rodaVenus = 10;

// Variáveis TERRA
static float anguloTerra = 90;                 // Rotação da esfera em torno do eixo y
static int terraLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static int terraTexture;
static bool usarTerra = true;
static float rodaTerra = 90;

// Variáveis PLUTAO
static float anguloPlutao = 10;                 // Rotação da esfera em torno do eixo y
static int plutaoLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static int plutaoTexture;
static bool usarPlutao = true;
static float rodaPlutao = 10;

// Variáveis SATURNO
static float anguloSaturno = 10;                 // Rotação da esfera em torno do eixo y
static int saturnoLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static int saturnoTexture;
static bool usarSaturno = true;
static float rodaSaturno = 10;

// Variáveis MERCURIO
static float anguloMercurio = 90;                 // Rotação da esfera em torno do eixo y
static int mercurioLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static int mercurioTexture;
static bool usarMercurio = true;
static float rodaMercurio = 10;

// Variáveis URANO
static float anguloUrano = 10;                 // Rotação da esfera em torno do eixo y
static int uranoLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static int uranoTexture;
static bool usarUrano = true;
static float rodaUrano = 10;

// Variáveis JUPITER
static float anguloJupiter = 78;                 // Rotação da esfera em torno do eixo y
static int jupiterLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static int jupiterTexture;
static bool usarJupiter = true;
static float rodaJupiter = 10;

// Variáveis NETUNO
static float anguloNetuno = 0;                 // Rotação da esfera em torno do eixo y
static int netunoLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static int netunoTexture;
static bool usarNetuno = true;
static float rodaNetuno = 90;

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
        glTranslatef(posicao, 0, 0);
        gluDisk(disk, dentro, fora, 600, 600);
    glPopMatrix();
    gluDeleteQuadric(disk);
}
void geraOrbita(){
   aneis(0,90,0,158,158.5); //MERCURIO
   aneis(0,90,0,208,208.5); //VENUS
   aneis(0,90,0,250,250.5); //TERRA
   aneis(0,90,0,330,330.5); //MARTE
   aneis(0,90,0,878,878.5); //JUPITER
   aneis(0,90,0,1529,1529.5); //SATURNO
   aneis(0,90,0,2970,2970.5); //URANO
   aneis(0,90,0,4604,4604.5); //NETUNO
   aneis(0,90,0,6022,6022.5); //PLUTÃO
 
}

void sol(){
    
    glEnable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, solTexture);
    glPushMatrix();
        glRotatef(anguloSol, 0, 1, 0);
        glRotatef(90, 1, 0, 0);
        solidSphere(100.0 , solLados, solLados);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    
}

void geraMundos(){
    glEnable(GL_TEXTURE_2D);

//skybox de raio 300 a partir do sol
    glBindTexture(GL_TEXTURE_2D, spaceTexture);
    glPushMatrix();
        glTranslatef(xCursor, yCursor, zCursor); 
        solidSphere(7000.0, solLados, solLados);
    glPopMatrix();
//fim da skybox

    //Mercurio
    glBindTexture(GL_TEXTURE_2D, mercurioTexture);   
    glPushMatrix();
        glRotatef(anguloMercurio, 0, 1, 0);
        glTranslatef(158, 0.0, 0); //posiciona em outro ponto
        glRotatef(rodaMercurio, 0, 1, 0);
        glRotatef(97, 1, 0, 0); 
        solidSphere(0.5*tamanhoVisivel, mercurioLados, mercurioLados);
    glPopMatrix();

    //Venus
    glBindTexture(GL_TEXTURE_2D, venusTexture);   
    glPushMatrix();
        glRotatef(anguloVenus, 0, 1, 0);
        glTranslatef(208, 0.0, 0); //posiciona em outro ponto
        glRotatef(rodaVenus, 0, 1, 0);
        glRotatef(-267, 1, 0, 0);        
        solidSphere(0.95*tamanhoVisivel, venusLados, venusLados);
    glPopMatrix();
    
    //Terra
    glBindTexture(GL_TEXTURE_2D, terraTexture);   
    glPushMatrix();
        glRotatef(anguloTerra, 0, 1, 0); // gira ao redor do sol
        glTranslatef(250, 0, 0);
        glRotatef(rodaTerra, 0, 1, 0);       // gira ao redor dela mesmo
        glRotatef(-133.5, 1, 0, 0);              // angulação do eixo
        solidSphere(1.0*tamanhoVisivel, terraLados, terraLados);
        
    glPopMatrix();

    //Marte
    glBindTexture(GL_TEXTURE_2D, marsTexture);   
    glPushMatrix();
        glRotatef(anguloMarte, 0, 1, 0);
        
        glTranslatef(330, 0.0, 0); //posiciona em outro ponto
        glRotatef(rodaMarte, 0, 1, 0);
        glRotatef(115, 1, 0, 0); 
        solidSphere(0.53*tamanhoVisivel, marteLados, marteLados);
    glPopMatrix();
    
    //Jupiter
    glBindTexture(GL_TEXTURE_2D, jupiterTexture);   
    glPushMatrix();
        glRotatef(anguloJupiter, 0, -1, 0); // gira para o outro lado
        glTranslatef(878, 0, 0); 
        glRotatef(rodaJupiter, 0, 1, 0);
        glRotatef(93, 1, 0, 0); 
        solidSphere(11.2*tamanhoVisivel, jupiterLados, jupiterLados);
    glPopMatrix();


    //Saturno
    glBindTexture(GL_TEXTURE_2D, saturnoTexture);  
    glPushMatrix();
        aneis(anguloSaturno,55,1529,10.0*tamanhoVisivel,12.0*tamanhoVisivel);
        aneis(anguloSaturno,55,1529,12.5*tamanhoVisivel,14.0*tamanhoVisivel);
        glRotatef(anguloSaturno, 0, -1, 0); // gira para o outro lado
        glTranslatef(1529, 0, 0); 
        glRotatef(rodaSaturno, 0, 1, 0);
        glRotatef(117, 1, 0, 0); 
        solidSphere(9.45*tamanhoVisivel, saturnoLados, saturnoLados);
    glPopMatrix();

    //Uranio
    glBindTexture(GL_TEXTURE_2D, uranoTexture);   
    glPushMatrix();
        aneis(anguloUrano,45,2970,7.4*tamanhoVisivel,7.6*tamanhoVisivel);
        aneis(anguloUrano,45,2970,7.7*tamanhoVisivel,7.8*tamanhoVisivel);
        aneis(anguloUrano,45,2970,8.0*tamanhoVisivel,8.5*tamanhoVisivel);
        glRotatef(anguloUrano, 0, -1, 0); // gira para o outro lado
        glTranslatef(2970, 0, 0); 
        glRotatef(rodaUrano, 0, 1, 0);
        glRotatef(-188, 1, 0, 0); 
        solidSphere(4.1*tamanhoVisivel, uranoLados, uranoLados);
    glPopMatrix();

    //Netuno
    glBindTexture(GL_TEXTURE_2D, netunoTexture);   
    glPushMatrix();
        glRotatef(anguloNetuno, 0, -1, 0); // gira para o outro lado
        glTranslatef(4604, 0, 0); 
        glRotatef(rodaNetuno, 0, 1, 0);
        glRotatef(120, 1, 0, 0); 
        solidSphere(3.88*tamanhoVisivel, netunoLados, netunoLados);
    glPopMatrix();

    //Plutão é um planeta?
    glBindTexture(GL_TEXTURE_2D, plutaoTexture);   
    glPushMatrix();
        glRotatef(anguloPlutao, 0, -1, 0); // gira para o outro lado
        glTranslatef(6022, 0, 0); 
        glRotatef(rodaPlutao, 0, 1, 0);
        glRotatef(212, 1, 0, 0); 
        solidSphere(1.0*tamanhoVisivel, plutaoLados, plutaoLados);
    glPopMatrix();

    
    
    glDisable(GL_TEXTURE_2D);
    

}

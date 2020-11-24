enum CAMERAS { TERCEIRA_PESSOA = 1, PRIMEIRA_PESSOA, ESTATICA };
int modoCAM = TERCEIRA_PESSOA;            //variável responsável por guardar o modo de câmera que está sendo utilizado

int xMouse = 0, yMouse = 0;     //variáveis globais que serão usadas na função posicionaCamera

float phi = 90, teta = 0;       //ângulos das coordenadas esféricas


// estrutura de dados que representará as coordenadas da câmera
struct {
  float x, y, z;
  float targetX, targetY, targetZ;
} camera;

//capturar posicionamento do mouse
void posicionaCamera(int x, int y){
    // variáveis que guardam o vetor 2D de movimento do mouse na tela
    // xMouse e yMouse são os valores de x e y no frame anterior
    float xChange = x - xMouse;
    float yChange = y - yMouse;

    // este exemplo usa coordenadas esféricas para controlar a câmera...
    // teta e phi guardam a conversão do vetor 2D para um espaço 3D
    // com coordenada esférica
    teta = (teta + xChange/150);
    phi = (phi - yChange/150);

    if(phi >= 180){
      //limite de 180 para o phi
      phi = 180;
    }

    // guarda o x e y do mouse para usar na comparação do próximo frame
    xMouse = x;
    yMouse = y;
}
void posicaoCamera(){
  //esfera de raio 100
    camera.x = 400 * sin(phi) * cos(teta);  //coordenada x denotada em coordenadas esféricas
    camera.z = 400 * sin(phi) * sin(teta); //coordenada z denotada em coordenadas esféricas
    camera.y = 400 * cos(phi);          //coordenada y denotada em coordenadas esféricas

    switch (modoCAM) {
    case TERCEIRA_PESSOA:
        gluLookAt(xCursor+camera.x, camera.y, zCursor+camera.z,//câmera posicionada na casca da esfera calculada (terceira pessoa)
            xCursor+0, 0, zCursor+0,                          //centro da esfera, o ponto em que estamos olhando
            0, 1, 0);                                        //vetor UP, apontando para o eixo Y (para cima)
        break;

    case PRIMEIRA_PESSOA:
        gluLookAt( xCursor+0, 0, zCursor+0,                    //já aqui, a câmera está posicionada no centro da esfera
            xCursor+camera.x, camera.y, zCursor+camera.z,     //e a câmera estará olhando para a casca da esfera (primeira pessoa)
            0, 1, 0);                                        //vetor UP, apontando para o eixo Y (para cima)
        break;

    case ESTATICA:
    default:
        gluLookAt(0, 0, 800,   // Z=400
                  0, 0, 0,    // (0, 0, 0) origem do mundo
                  0, 1, 0);  //nesse exemplo mais simples, estamos no ponto Z=200 olhando para o ponto 0
        break;
    }
}

// Escreve uma cadeia de caracteres
void escreveTextoNaTela(void *font, char *string)
{
    char *c;
    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Converte um número decimal em string
void floatParaString(char * destStr, int precision, float val)
{
    sprintf(destStr,"%f",val);
    destStr[precision] = '\0';
}

// Escreve as informações variáveis na tela
void informacoesTela(void)
{
    glDisable(GL_LIGHTING); // Desabilita iluminação
    glColor3f(.85f, .85f, .85f);

    glRasterPos3f(100, 110, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Iluminacao (l): ");
    escreveTextoNaTela((void*)font, (char*)(isLightingOn ? "ligada" : "desligada"));

    glRasterPos3f(100, 120, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Musica (p): ");
    escreveTextoNaTela((void*)font, (char*)(pause ? "desligada" : "ligada"));

    glRasterPos3f(100, 130, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Tamanho proporcional (t): ");
    escreveTextoNaTela((void*)font, (char*)(tamanhoVisivel2 ? "x10" : "x1"));

    glRasterPos3f(100, 140, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Orbita visivel(v): ");
    escreveTextoNaTela((void*)font, (char*)(orbita ? "Sim" : "Nao"));

    glRasterPos3f(100, 150, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Fim da vida como conhecemos? (o): ");
    escreveTextoNaTela((void*)font, (char*)(light0Ligada ? "Nao" : "Sim"));

    glRasterPos3f(100, 100, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Camera: 1-Camera movel / 2- Camera interna / 3-Camera estatica");


    glColor3f(.01f, .01f, .01f);

    glRasterPos3f(1, 0.65, -2);
    escreveTextoNaTela((void*)font, (char*)"Pressione 'w'");
    glRasterPos3f(1, 0.60, -2);
    escreveTextoNaTela((void*)font, (char*)"'a' 's' ou 'd'");
    glRasterPos3f(1, 0.55, -2);
    escreveTextoNaTela((void*)font, (char*)"para sair do Sol");
     

}
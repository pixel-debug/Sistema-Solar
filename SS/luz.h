

void luzes(){
    // Propriedades das fontes de luz
    float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
    float lightDif0[] = { d, d, d, 1.0 };
    float lightSpec0[] = { e, e, e, 1.0 };
    float lightPos0[] = { 0.0, 0.0, 3.0, p };
    float lightDifAndSpec1[] = { 0.0, 1.0, 0.0, 1.0 };
    float lightPos1[] = { 1.0, 2.0, 0.0, 1.0 };
    float globAmb[] = { m, m, m, 1.0 };

    // Propriedades da fonte de luz LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec0);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);        // Luz ambiente global
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, localViewer);// Enable local viewpoint

    // Ativa as fontes de luz do sistema 
    // MAS NÃO SEI PORQUÊ DIABOS NÃO PEGA O SOL
    if (light0Ligada) {
        glEnable(GL_LIGHT0);
    } else {
        glDisable(GL_LIGHT0);
    }
    // Desabilita iluminação para desenhar as esferas que representam as luzes
    glDisable(GL_LIGHTING);
    // Light0 e esfera indicativa (ou seta)
    glPushMatrix();
        glRotatef(xAngle, 1.0, 0.0, 0.0); // Rotação no eixo x
        glRotatef(yAngle, 0.0, 1.0, 0.0); // Rotação no eixo y
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
        glTranslatef(lightPos0[0], lightPos0[1], lightPos0[2]);
        glColor3f(d, d, d);
        if (light0Ligada)
        {
                glLineWidth(3.0);
                glBegin(GL_LINES);
                glVertex3f(0.0, 0.0, 0.25);
                glVertex3f(0.0, 0.0, -0.25);
                glVertex3f(0.0, 0.0, -0.25);
                glVertex3f(0.05, 0.0, -0.2);
                glVertex3f(0.0, 0.0, -0.25);
                glVertex3f(-0.05, 0.0, -0.2);
                glEnd();
                glLineWidth(1.0);
            
        }
    glPopMatrix();
    if (isLightingOn) {
        glEnable(GL_LIGHTING);
    }

}
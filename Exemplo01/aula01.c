#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Define a cor de fundo como branco
}

void Desenha(void) {
    // Limpa a janela de visualização com a cor de fundo definida
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha uma casinha composta de um quadrado e um triângulo

    // Altera a cor do desenho para azul
    glColor3f(0.0f, 0.0f, 1.0f);
    // Desenha o retângulo da casa
    glBegin(GL_POLYGON);
    glVertex2f(-0.5f, -0.5f); // Canto inferior esquerdo
    glVertex2f(-0.5f, 0.5f);  // Canto superior esquerdo
    glVertex2f(0.5f, 0.5f);   // Canto superior direito
    glVertex2f(0.5f, -0.5f);  // Canto inferior direito
    glEnd();

    // Altera a cor do desenho para vermelho
    glColor3f(1.0f, 0.0f, 0.0f);
    // Desenha o telhado da casa (triângulo)
    glBegin(GL_POLYGON);
    glVertex2f(-0.7f, 0.5f); // Canto superior esquerdo
    glVertex2f(0.0f, 1.2f);  // Ponto mais alto
    glVertex2f(0.7f, 0.5f);  // Canto superior direito
    glEnd();

    // Executa os comandos OpenGL
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutInitWindowPosition(100, 10);
    glutCreateWindow("Minha Casinha OpenGL");
    init();
    glutDisplayFunc(Desenha);
    glutMainLoop();
    return 0;
}

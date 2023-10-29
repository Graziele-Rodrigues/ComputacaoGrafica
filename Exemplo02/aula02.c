#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

float dx = 0.0;
float dy = 0.0;
float ang = 0.0;
float tamanho=1;

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Define a cor de fundo como branco
}

void teclado (unsigned char tecla, int x, int y)
{
    switch (tecla) {
    case 'l': dx = dx - 0.1; glutPostRedisplay(); break; //anda lado esquerdo
    case 'r': dx =dx + 0.1; glutPostRedisplay(); break;  //anda lado direito
    case 't': dy = dy - 0.1; glutPostRedisplay(); break; //sobe
    case 'd': dy =dy + 0.1; glutPostRedisplay(); break;  //desce
    case 'x': ang=ang+45; glutPostRedisplay(); break;  //rotaciona
    case '+': tamanho=tamanho+0.1; glutPostRedisplay(); break;  //aumenta tamanho
    case '-': tamanho=tamanho-0.1; glutPostRedisplay(); break;  //diminui tamanho
    }
}

void Desenha(void) {
    // Limpa a janela de visualização com a cor de fundo definida
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha uma casinha composta de um quadrado e um triângulo

    // Altera a cor do desenho para azul
    glColor3f(0.0f, 0.0f, 1.0f);

    glLoadIdentity();
    //desloca na horizontal e vertical pelo valor obtido em dx/dy
    glTranslatef(dx, dy, 0.0);
    //rotaciona
    glRotatef(ang, 0,0,1);
    //muda tamanho
    glScalef(1,tamanho,1);
    // Desenha o retângulo da casa
    glBegin(GL_POLYGON);
    glVertex2f(-0.5f, -0.5f); // Canto inferior esquerdo
    glVertex2f(-0.5f, 0.5f);  // Canto superior esquerdo
    glVertex2f(0.5f, 0.5f);   // Canto superior direito
    glVertex2f(0.5f, -0.5f);  // Canto inferior direito
    glEnd();

    // Altera a cor do desenho para vermelho
    glColor3f(1.0f, 0.0f, 0.0f);

    glLoadIdentity();
    //desloca na horizontal e vertical pelo valor obtido em dx/dy
    glTranslatef(dx, dy, 0.0);
    //rotaciona
    glRotatef(ang, 0,0,1);
    //muda tamanho
    glScalef(1,tamanho,1);

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
    glutCreateWindow("Minha Casinha OpenGL se movendo");
    init();
    glutKeyboardFunc(teclado);
    glutDisplayFunc(Desenha);
    glutMainLoop();
    return 0;
}

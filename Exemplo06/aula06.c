#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

float dx = 0.0;
float dy = 0.0;
float ang = 0.0;
float tamanho=1;

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Define a cor de fundo
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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1.0, 0, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 0, 5, 0, 1, 0, 0, 0, 1);

    glClear(GL_COLOR_BUFFER_BIT);

    // desloca na horizontal e vertical pelo valor obtido em dx/dy
    glTranslatef(dx, dy, 0.0);

    // rotaciona em torno do eixo Y
    glRotatef(ang, 0, 1, 0);

    // muda tamanho
    glScalef(1, tamanho, 1);

    // desenha o cone
    glColor3f(1.0, 0.0, 1.0);
    glutWireCone(1.0, 1.0, 10.0, 10.0);

    // desenha a esfera
    glColor3f(0.0, 0.0, 1.0);
    glutWireSphere(0.5, 10, 10);

    // Executa os comandos OpenGL
    glFlush();
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutInitWindowPosition(100, 10);
    glutCreateWindow("Camera 3D");
    init();
    glutKeyboardFunc(teclado);
    glutDisplayFunc(Desenha);
    glutMainLoop();
    return 0;
}

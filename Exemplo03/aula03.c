#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

float dx = 0.0;
float dy = 0.0;
float ang = 0.0;
float tamanho = 1.0;
int modoDesenho = 0; // 0 para círculo, 1 para arco

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Define a cor de fundo como branco
}

void teclado(unsigned char tecla, int x, int y) {
    switch (tecla) {
    case 'l': dx = dx - 0.1; break; // anda para o lado esquerdo
    case 'r': dx = dx + 0.1; break; // anda para o lado direito
    case 't': dy = dy - 0.1; break; // sobe
    case 'd': dy = dy + 0.1; break; // desce
    case 'x': ang = ang + 45; break; // rotaciona
    case '+': tamanho = tamanho + 0.1; break; // aumenta tamanho
    case '-': tamanho = tamanho - 0.1; break; // diminui tamanho
    case 'c': modoDesenho = 0; break; // define desenho como círculo
    case 'a': modoDesenho = 1; break; // define desenho como arco
    }
    glutPostRedisplay();
}

void Desenha(void) {
    // Limpa a janela de visualização com a cor de fundo definida
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.0, 0.0, 0.5); // cor azul marinho

    // desloca na horizontal e vertical pelo valor obtido em dx/dy
    glTranslatef(dx, dy, 0.0);

    // rotaciona
    glRotatef(ang, 0, 0, 1);

    // muda tamanho
    glScalef(1, tamanho, 1);

    // Desenha círculo ou arco
    glBegin(GL_POINTS);
    if (modoDesenho == 0) {
        // Desenha círculo completo
        for (int i = 0; i < 500; ++i) {
            glVertex3f(cos(2 * 3.14159 * i / 500.0), sin(2 * 3.14159 * i / 500.0), 0);
        }
    } else {
        // Desenha arco (um quarto do círculo)
        for (int i = 0; i < 125; ++i) {
            glVertex3f(cos(2 * 3.14159 * i / 500.0), sin(2 * 3.14159 * i / 500.0), 0);
        }
    }
    glEnd();

    // Executa os comandos OpenGL
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(50, 10);
    glutCreateWindow("Curva paramétrica");
    init();
    glutKeyboardFunc(teclado);
    glutDisplayFunc(Desenha);
    glutMainLoop();
    return 0;
}

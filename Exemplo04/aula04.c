#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#define NUM_VIEWPORTS 16

typedef struct {
    float x, y, width, height;
    float r, g, b;
    int selected;
} Viewport;

Viewport viewports[NUM_VIEWPORTS];

void drawCircle(float cx, float cy, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= segments; ++i) {
        float theta = 2.0 * M_PI * (float)(i) / (float)(segments);
        float x = cx + radius * cos(theta);
        float y = cy + radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 600, 0, 600, 1, -1);

    float viewportWidth = 600.0 / 4;
    float viewportHeight = 600.0 / 4;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int index = i * 4 + j;
            viewports[index].x = j * viewportWidth;
            viewports[index].y = i * viewportHeight;
            viewports[index].width = viewportWidth;
            viewports[index].height = viewportHeight;
            viewports[index].r = (float)rand() / RAND_MAX;
            viewports[index].g = (float)rand() / RAND_MAX;
            viewports[index].b = (float)rand() / RAND_MAX;
            viewports[index].selected = 0;
        }
    }
}

void drawFlower() {
    for (int i = 0; i < NUM_VIEWPORTS; ++i) {
        glViewport(viewports[i].x, viewports[i].y, viewports[i].width, viewports[i].height);
        glColor3f(viewports[i].r, viewports[i].g, viewports[i].b);

        // Desenha pétalas da flor
        for (int j = 0; j < 6; ++j) {
            glPushMatrix();
            glTranslatef(50.0, 50.0, 0.0);
            glRotatef(j * 60.0, 0.0, 0.0, 1.0);
            glTranslatef(25.0, 0.0, 0.0);
            drawCircle(0.0, 0.0, 20.0, 100);
            glPopMatrix();
        }

        // Desenha o centro da flor
        glColor3f(1.0, 1.0, 0.0);  // Amarelo
        drawCircle(50.0, 50.0, 10.0, 100);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawFlower();

    glFlush();
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        for (int i = 0; i < NUM_VIEWPORTS; ++i) {
            if (x >= viewports[i].x && x <= viewports[i].x + viewports[i].width &&
                y >= viewports[i].y && y <= viewports[i].y + viewports[i].height) {
                viewports[i].r = (float)rand() / RAND_MAX;
                viewports[i].g = (float)rand() / RAND_MAX;
                viewports[i].b = (float)rand() / RAND_MAX;
                viewports[i].selected = 1;
            } else {
                viewports[i].selected = 0;
            }
        }

        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("16 flores");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);

    glutMainLoop();

    return 0;
}

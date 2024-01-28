#include <iostream>
#include "CarregarArquivo2.cpp"

using namespace std;

CarregarArquivo obj;
float dx = 0.0;
float dy = 0.0;
float dz = 0.0;
float ang = 0.0;
float tamanho=1;

/*void Idle(){

}*/
GLfloat globalAmbient[] = {0.0, 0.0, 0.3, 1.0};
void DefineIluminacao (void)
{
 glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
}

void Teclado(unsigned char tecla, int x, int y){
    switch (tecla) {
        case 'l': dx = dx - 0.1; glutPostRedisplay(); break; //anda lado esquerdo
        case 'r': dx =dx + 0.1; glutPostRedisplay(); break;  //anda lado direito
        case 't': dy = dy - 0.1; glutPostRedisplay(); break; //sobe
        case 'd': dy =dy + 0.1; glutPostRedisplay(); break;  //desce
        case 'f': dz = dz - 0.1; glutPostRedisplay(); break; //frente
        case 'b': dz =dz + 0.1; glutPostRedisplay(); break;  //tras
        case 'x': ang=ang+45; glutPostRedisplay(); break;  //rotaciona
        case '+': tamanho=tamanho+0.1; glutPostRedisplay(); break;  //aumenta tamanho
        case '-': tamanho=tamanho-0.1; glutPostRedisplay(); break;  //diminui tamanho
    }
}

void Inicializa(void){
  glClearColor (1.0, 1.0, 1.0, 0.0); //fundo branco

    // Habilita a definição da cor do material a partir da cor corrente
    glEnable(GL_COLOR_MATERIAL);
    //Habilita o uso de iluminação
    glEnable(GL_LIGHTING);
    // Habilita a luz de número 0
   glEnable(GL_LIGHT0);
   // Habilita o z-buffer
   glEnable(GL_DEPTH_TEST);

   //ajusta perspectiva
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(65, 1, 0.5, 500);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0,0,13, 0,0,0, 0,1,0);

   obj.Carregar("gato.obj");
}


void Piso (float escala, float altura){
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
        glTranslated(0.0, altura, 0.0);
        glScalef(escala, escala, escala);
        glBegin(GL_QUADS);
        glVertex3f(100.00, 0.0, 100.0);
        glVertex3f(-100.00, 0.0, 100.0);
        glVertex3f(-100.00, 0.0, -100.0);
        glVertex3f(100.00, 0.0, -100.0);
        glEnd();
    glPopMatrix();
}

void ObjWireFrame(void)  {
    glPushMatrix();
    for (unsigned int j = 0; j < (obj.faces).size(); ++j )
    {
        glBegin ( GL_LINE_LOOP );
         for (unsigned int i = 0; i < (obj.faces[j]).size() ; ++i )        {
            GLfloat nor[3] =  {(obj.normais[obj.faces[j][i][2]][0]),(obj.normais[obj.faces[j][i][2]][1]),(obj.normais[obj.faces[j][i][2]][2])};
            glNormal3fv (nor);
            GLfloat vert[3] = {(obj.vertices[obj.faces[j][i][0]][0]),(obj.vertices[obj.faces[j][i][0]][1]),(obj.vertices[obj.faces[j][i][0]][2])};
            glVertex3fv ( vert );


         }
        glEnd( );
    }
    glPopMatrix();
}

void ObjSolid(void)  {
    glPushMatrix();
    for (unsigned int j = 0; j < (obj.faces).size(); ++j )
    {
        glBegin ( GL_POLYGON );
        for (unsigned int i = 0; i < (obj.faces[j]).size() ; ++i )
      {
            GLfloat nor[3] =  {(obj.normais[obj.faces[j][i][2]][0]),(obj.normais[obj.faces[j][i][2]][1]),(obj.normais[obj.faces[j][i][2]][2])};
            glNormal3fv (nor);
            GLfloat vert[3] = {(obj.vertices[obj.faces[j][i][0]][0]),(obj.vertices[obj.faces[j][i][0]][1]),(obj.vertices[obj.faces[j][i][0]][2])};
            glVertex3fv ( vert );

        }
        glEnd( );
    }
    glPopMatrix();
}

void Desenha(void){
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      DefineIluminacao();
      Piso(1.0, -5.0); //se desenhar com altura=0.0 não vamos ver,
                              //pois o plano não tem espessura
      glPushMatrix();
          //desloca na horizontal e vertical pelo valor obtido em dx/dy
          glTranslatef(dx, dy, dz);
          //rotaciona em torno do eixo Y
          glRotatef(ang, 0, 1, 0);
          // muda tamanho
          glScalef(1, tamanho, 1);
          //começa a desenhar
          glColor3f(1.0, 0.0, 0.0);
          glScalef(2.0, 2.0, 2.0);
          ObjSolid();
          glPopMatrix();
      glutSwapBuffers();
}


int main(int argc, char** argv){
  glutInit(&argc, argv);

  glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

  glutInitWindowSize (600, 600);

  glutInitWindowPosition (0, 0);

  glutCreateWindow ("Computação Gráfica: G");

  Inicializa();
  glutKeyboardFunc(Teclado);
  glutDisplayFunc(Desenha);
 // glutIdleFunc(Idle);
  glutMainLoop();
  return 0;
}

#define GLUT_DISABLE_ATEXIT_HACK

#include "glut.h"

#define KEY_ESC 27

//dibuja un simple gizmo
void displayGizmo()
{
    glBegin(GL_LINES);
    glColor3d(255,0,0);
    glVertex2d(0, 0);
    glVertex2d(1, 0);
    glColor3d(0, 255, 0);
    glVertex2d(0, 0);
    glVertex2d(0, 1);
    glEnd();
}

//Practica Ejercicio 1 Funcion que Dibujo un Cuadrado: Parámetros centro y tamArista

void displayCuadrado(float x, float y, int tamArista)
{
    /*              1
     *     ------------
     *     |            |
     *  4  |            |      2
     *     |            |
     *     ------------
     *              3
     */
    glBegin(GL_LINES);
    //Lateral 1
    glColor3d(255,0,0);
    glVertex2d(x-tamArista,y+tamArista);
    glVertex2d(x+tamArista, y+tamArista);
    //Lateral 2
    glColor3d(255,0,0);
    glVertex2d(x+tamArista,y+tamArista);
    glVertex2d(x+tamArista,y-tamArista);
    //Lateral 3
    glColor3d(255,0,0);
    glVertex2d(x-tamArista,y-tamArista);
    glVertex2d(x+tamArista,y-tamArista);
    //Lateral 4
    glColor3d(255,0,0);
    glVertex2d(x-tamArista,y+tamArista);
    glVertex2d(x-tamArista,y-tamArista);
    glEnd();


}

void displayCirculo0(float x, float y, int tamRadio)
{
    /*glBegin(GL_LINES);
    float x1,y1,x2,y2,x3,y3,x4,y4,x5,y5;
    x1 = x; y1 = y + tamRadio;
    x2 = x + tamRadio; y2 = y;
    x3 = x; y3 = y - tamRadio;
    x4 = x - tamRadio; y4 = y;
    x5 = x1; y5 = y1;
   */
    //Punto 2
    float x2 = x - tamRadio/2;
    float y2 = y + tamRadio;
    //Punto 3
    float x3 = x +tamRadio/2;
    float y3 = y +tamRadio;
    //Punto 1
    float x1 = x - tamRadio;
    float y1 = y + tamRadio/2;
    //Punto 8
    float x8 = x - tamRadio;
    float y8 = y - tamRadio/2;
    //Punto 4
    float x4 = x + tamRadio;
    float y4 = y + tamRadio/2;
    //Punto 5
    float x5 = x + tamRadio;
    float y5 = y - tamRadio/2;
    //Punto 7
    float x7 = x -tamRadio/2;
    float y7 = y - tamRadio;
    //Punto 6
    float x6 = x + tamRadio/2;
    float y6 = y -tamRadio;


    glBegin(GL_LINES);
    glColor3d(255,0,0);
    glVertex2d(x1,y1);
    glVertex2d(x2,y2);

    glColor3d(255,0,0);
    glVertex2d(x2,y2);
    glVertex2d(x3,y3);

    glColor3d(255,0,0);
    glVertex2d(x3,y3);
    glVertex2d(x4,y4);


    glColor3d(255,0,0);
    glVertex2d(x4,y4);
    glVertex2d(x5,y5);

    glColor3d(255,0,0);
    glVertex2d(x5,y5);
    glVertex2d(x6,y6);

    glColor3d(255,0,0);
    glVertex2d(x6,y6);
    glVertex2d(x7,y7);

    glColor3d(255,0,0);
    glVertex2d(x7,y7);
    glVertex2d(x8,y8);

    glColor3d(255,0,0);
    glVertex2d(x8,y8);
    glVertex2d(x1,y1);


    glEnd();


}

//funcion llamada a cada imagen
void glPaint(void) {

    //El fondo de la escena al color initial
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
    glLoadIdentity();


    //dibuja el gizmo
    //displayGizmo();

    //dibuja el cuadrado
    //displayCuadrado(0,0,5);

    //dibuja el circulo
    displayCirculo0(0,0,5);

    //doble buffer, mantener esta instruccion al fin de la funcion
    glutSwapBuffers();
}

//
//inicializacion de OpenGL
//
void init_GL(void) {
    //Color del fondo de la escena
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro

    //modo projeccion
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-50.0f,  50.0f,-50.0f, 50.0f, -1.0f, 1.0f);
    // todas la informaciones previas se aplican al la matrice del ModelView
    glMatrixMode(GL_MODELVIEW);
}

GLvoid window_key(unsigned char key, int x, int y) {
    switch (key) {
        case KEY_ESC:
            exit(0);
            break;

        default:
            break;
    }

}
//
//el programa principal
//
int main(int argc, char** argv) {

    //Inicializacion de la GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600); //tamaño de la ventana
    glutInitWindowPosition(100, 100); //posicion de la ventana
    glutCreateWindow("TP1 OpenGL : hello_world_OpenGL"); //titulo de la ventana

    init_GL(); //funcion de inicializacion de OpenGL

    glutDisplayFunc(glPaint);
    glutReshapeFunc(&window_redraw);
    // Callback del teclado
    glutKeyboardFunc(&window_key);

    glutMainLoop(); //bucle de rendering

    return 0;
}
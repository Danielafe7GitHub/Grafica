#define GLUT_DISABLE_ATEXIT_HACK
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#define KEY_ESC 27

using namespace std;
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

//ROJO
//1. Elaborar una función que permite crear un cuadrado gracias a una línea cerrada. Esta función tomara como parámetro, su centro y el tamaño de su arista.

void displayCuadrado(float x, float y, int tamArista)
{
    /*    1              2
     *     ------------
     *     |          |
     *     |    xy    |
     *     |          |
     *     ------------
     *   4              3
     */
    glBegin(GL_LINE_LOOP);
    //Lateral 1
    glColor3d(255,0,0);
    glVertex2d(x-tamArista/2,y+tamArista/2);
    //Lateral 2
    glColor3d(255,0,0);
    glVertex2d(x+tamArista/2,y+tamArista/2);
    //Lateral 3
    glColor3d(255,0,0);
    glVertex2d(x+tamArista/2,y-tamArista/2);
    //Lateral 4
    glColor3d(255,0,0);
    glVertex2d(x-tamArista/2,y-tamArista/2);
    glEnd();


}
/// VERDE
///2. Elaborar una función que permite crear un círculo gracias a una línea cerrada. Esta función tomara como parámetro, su centro y su radio.
void displayCirculo(float xo, float yo, int tamRadio)
{
    /*Cos(0),sin(0) = (1,0) so on */
    double PI =  3.1415926;
    int iMax = 3000;
    glColor3d(0,255,1);
    glBegin(GL_LINE_LOOP);
    for(int i =0; i <= iMax  ; i++){
        double angle = 2 * PI * i / iMax ; //A más i más perfecto el círculo
        double x = cos(angle) * tamRadio;   //Lo multiplicamos por el Radio, así se hace más grande la circunferencia
        double y = sin(angle) * tamRadio;
        glVertex2d(x+xo,y+yo);
    }
    glEnd();





}

///AZUL
///3. Elaborar una función en OpenGL que permite obtener el resultado siguiente :Circulo de cìrculo
///La cantidad de círculos y el porcentaje de reducción del radio serán definidos por el usuario.
void displayCirculos(float x, float y, int tamRadio/*Ini*/, int num, float reduccion)
{
    for(int i=0;i<num;i++)
    {
        displayCirculo(x,y,tamRadio);
        tamRadio -= reduccion;
        x -= reduccion;

    }


}
/// AMARILLO
///4. Elaborar una función en OpenGL que permite obtener el resultado siguiente : circulos decrecientes
///El primer círculo es el de la izquierda. La cantidad de círculos y el porcentaje de reducción del radioserán definidos por el usuario.
void displayCirculosDec(float x, float y, int tamRadio/*Ini*/, int num, float reduccion)
{
    cout<<"numCirculos : "<<num<<endl;

    for(int i=0;i<num;i++)
    {
        displayCirculo(x,y,tamRadio);
        tamRadio -= reduccion;
        x += 2*tamRadio + reduccion;

    }
}

/// CELESTE
///4. Elaborar una función en OpenGL que permite obtener el resultado siguiente : circulos decrecientes diagonal
///La cantidad de círculos, el porcentaje de reducción del radio y el Angulo serán definidos por el usuario.
void displayCirculosDiag(double xo, double yo, int tamRadio/*Ini*/, int num, float reduccion, float angulo)
{
    /*for(int i=0;i<num;i++)
    {
        displayCirculo(x,y,tamRadio);
        tamRadio -= reduccion;
        x += 2*tamRadio + reduccion;
        y += tan(angulo) * x;

    }*/

    double m = tan(angulo);
    cout<<"Pendiente : "<<m<<endl;
    double x,y,c;  //(y-yo) = m(x-xo) --> y = mx + c
    for(int i=0;i<num;i++)
    {
        c = -xo*m+yo;
        y = m*xo+c;
        x = (yo - c)/m;

        //Línea Recta
        /*glColor3d(255,0,255);
        glBegin(GL_POINTS);
        glVertex2d(x,y);
        glEnd();
        xo++; yo++;*/

        displayCirculo(x,y,tamRadio);
        xo += 1.3*tamRadio ;
        yo += 1.3*tamRadio ;
        tamRadio -= reduccion;

    }


}
//funcion llamada a cada imagen
void glPaint(void) {

    //El fondo de la escena al color initial
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
    glLoadIdentity();


    //dibuja el gizmo
    displayGizmo();

    //dibuja el cuadrado
    displayCuadrado(-20,10,5);

    //dibuja el circulo
    displayCirculo(0,10,5);

    //dibuja el circulos
    displayCirculos(20,10,5,5,1);

    //dibuja el circulos decrecientes
    displayCirculosDec(-20,-10,5,5,1);

    //dibuja el circulos decrecientes; el num Radio = num Circulos ??
    displayCirculosDiag(-40,-40,5,5,1,30);

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

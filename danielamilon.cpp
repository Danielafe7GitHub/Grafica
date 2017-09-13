#include <iostream>
#include <math.h>
#include <GL/glut.h>

#define KEY_ESC 27

using namespace std;

int contador=3;
int xini,yini,xfin,yfin;
bool moving;


//dibuja un simple gizmo
void displayGizmo()
{
    glBegin(GL_LINES);
    glColor3d(255,0,0);
    glVertex2d(0, 0);
    glVertex2d(400, 0);
    glColor3d(0, 255, 0);
    glVertex2d(0, 0);
    glVertex2d(0, 400);
    glEnd();
}

void Bresenham(int x1,
               int y1,
               int const x2,
               int const y2)
{
    int delta_x(x2 - x1);
    // if x1 == x2, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;

    int delta_y(y2 - y1);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;

    glBegin(GL_POINTS);
    glColor3d(255,0,0);
    glVertex2d(x1, y1);
    glEnd();

    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));

        while (x1 != x2)
        {
            // reduce error, while taking into account the corner case of error == 0
            if ((error > 0) || (!error && (ix > 0)))
            {
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing

            error += delta_y;
            glBegin(GL_POINTS);
            glColor3d(255,0,0);
            glVertex2d(x1, y1);
            glEnd();
            x1 += ix;


        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));

        while (y1 != y2)
        {
            // reduce error, while taking into account the corner case of error == 0
            if ((error > 0) || (!error && (iy > 0)))
            {
                error -= delta_y;
                x1 += ix;
            }
            // else do nothing

            error += delta_x;
            glBegin(GL_POINTS);
            glVertex2d(x1, y1);
            glEnd();
            y1 += iy;
        }
    }
}

void OnMouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(contador%2==0){
            xfin=x-400;
            yfin=400-y;
            cout<<"Dibujo: "<<xini<<" "<<yini<<" "<<xfin<<" "<<yfin<<endl;
        }
        else{
            xini=x-400;
            yini=400-y;
        }
        contador+=1;
        cout<<contador<<endl;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        if(moving){
            moving=false;
            contador+=1;
        }
    }
}

void OnMouseMotion(int x, int y)
{
    moving=true;
    if(contador%2==0 ){
        xfin=x-400;
        yfin=400-y;
    }
    else{
        xini=x-400;
        yini=400-y;
    }
}



void idle(){ // AGREGAR ESTA FUNCION
    glutPostRedisplay();
}

//funcion llamada a cada imagen
void glPaint(void) {

    //El fondo de la escena al color initial
    glClear(GL_COLOR_BUFFER_BIT); //CAMBIO
    glLoadIdentity();
    glOrtho(-400.0f,  400.0f,-400.0f, 400.0f, -1.0f, 1.0f);


    //dibuja el gizmo
    displayGizmo();
    if(contador%2!=0 || moving) {
        cout<<"Grafico"<<endl;
        Bresenham(xini,yini,xfin,yfin);
    }
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
    //glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
    glViewport(0, 0, width, height);
    //glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glOrtho(-400.0f,  400.0f,-400.0f, 400.0f, -1.0f, 1.0f);
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
    glutInitWindowSize(800, 800); //tamaño de la ventana
    glutInitWindowPosition(100, 100); //posicion de la ventana
    glutCreateWindow("TP2 bis OpenGL : Bresenham"); //titulo de la ventana

    init_GL(); //funcion de inicializacion de OpenGL

    glutDisplayFunc(glPaint);
    glutReshapeFunc(&window_redraw);
    // Callback del teclado
    glutKeyboardFunc(&window_key);
    glutMouseFunc(&OnMouseClick);
    glutMotionFunc(&OnMouseMotion);
    glutIdleFunc(&idle);

    glutMainLoop(); //bucle de rendering

    return 0;
}



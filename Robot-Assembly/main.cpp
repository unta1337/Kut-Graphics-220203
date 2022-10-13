#include <cstdlib>
#include <cmath>

#include "draw.hpp"
#include "util.hpp"
#include "mesh.hpp"

#define FILTER_ASE L"ASE 3D data (*.ase)\0*.ase\0All (*.*)\0*.*\0"

static Mesh obj3D;

void display()
{
    glClearColor(0.99, 0.97, 0.97, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setMaterialColor(1, 1, 1, 1);
    obj3D.draw(250, true);
    glutSwapBuffers();

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    WCHAR* fileName;

    switch (key)
    {
    case 'l':
        fileName = fileDlg(FILTER_ASE);
        if (fileName != NULL)
            obj3D.readASE(fileName);
		break;
    case 'i':
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        break;
    case 'w':
        glPolygonMode(GL_FRONT, GL_LINE);
        glPolygonMode(GL_BACK, GL_POINT);
		break;
    case 's':
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_LINE);
		break;
    case 'q':
        exit(0);
    }

    glutPostRedisplay();
}

static int prevX;
static int prevY;

void mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        prevX = x;
        prevY = y;
    }
}

void mouseMotion(GLint x, GLint y)
{
    glMatrixMode(GL_MODELVIEW);
    glRotated(x - prevX, 0, -1, 0);
    glRotated(y - prevY, -1, 0, 0);
	prevX = x;
	prevY = y;
    glutPostRedisplay();
}

void initRendering()
{
    GLfloat light_specular[] = { 0.8, 0.5, 0.8, 1.0 };
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light_position[] = { 0.f, -2.5f, 2.5f, 0.0f };

    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    GLfloat mat_specular[] = { 0.5, 1.0, 0.5, 1.0 };
    GLfloat mat_shininess[] = { 70.0 };
    GLfloat mat_color[] = { 0.5, 0.5, 0.5, 1.0 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}

int main(int argc, char* argv[]) 
{
    setlocale(LC_ALL, "KOREAN");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Geometric Transform");

    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMotion);

    initRendering();
    keyboard('l', 0, 0);

    glutMainLoop();
    return 0;
}

#include <cstdlib>
#include <cmath>

#include <glut.h>

#include "Draw.h"
#include "Util.h"

#include "Mesh.h"
#include "Robot.h"

#include "DefaultAnimation.h"
#include "RunAnimation.h"
#include "Dab.h"

#define FILTER_ASE L"ASE 3D data (*.ase)\0*.ase\0All (*.*)\0*.*\0"

static const int initialWidth = 600;
static const int initialHeight = 600;

static Mesh object;
static Robot robot(300, false);

static bool showObject = true;

extern int gTime = 0;
static int gTimeInterval = 10;
static int gTimeIntervalMS = 10;
static bool doTimeFlow = false;

static IAnimation* animations[] =
{
    new DefaultAnimation,
    new RunAnimation,
    new Dab
};
static int iAnimation = 1;

void display()
{
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    glClearColor(0.2, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setMaterialColor(1, 1, 1, 1);
    if (showObject)
		object.draw(300, true);
    else
    {
        // ÁÂ»ó´Ü, »ó´Üºä.
        glViewport(0, height / 2.0, width / 2.0, height / 2.0);
        glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(
            -1, 1, -1, 1, 0, 10
		);
		glMatrixMode(GL_MODELVIEW);
        gluLookAt(
            0, 1, 0,
            0, 0, 0,
			0, 0, 1
        );
        robot.draw();
        glPopMatrix();

        // ¿ì»ó´Ü, Frustum.
        glViewport(width / 2.0, height / 2.0, width / 2.0, height / 2.0);
        glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(
            -1, 1, -1, 1, 0, 10
		);
		glMatrixMode(GL_MODELVIEW);
        gluLookAt(
            0.1, -0.1, 0.1, 
			0, 0, 0, 
			0, 1, 0
        );
        robot.draw();
        glPopMatrix();

        // ÁÂÇÏ´Ü, Á¤¸éºä.
        glViewport(0, 0, width/ 2.0, height / 2.0);
        glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(
            -1, 1, -1, 1, 0, 10
		);
		glMatrixMode(GL_MODELVIEW);
        gluLookAt(
            0, 0, -1,
            0, 0, 0,
			0, 1, 0
        );
        robot.draw();
        glPopMatrix();

        // ¿ìÇÏ´Ü, Ãø¸éºä.
        glViewport(width / 2.0, 0, width / 2.0, height / 2.0);
        glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(
            -1, 1, -1, 1, 0, 10
		);
		glMatrixMode(GL_MODELVIEW);
        gluLookAt(
            1, 0, 0,
            0, 0, 0,
			0, 1, 0
        );
        robot.draw();
        glPopMatrix();
    }
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
            object.readASE(fileName);
        break;
    case 'k':
        showObject = !showObject;
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
    case 'r':
        doTimeFlow = !doTimeFlow;
        break;
    case 'n':
        gTime = 0;
        iAnimation = (iAnimation + 1) % (sizeof(animations) / sizeof(animations[0]));
		robot.setAnimation(animations[iAnimation]);
		break;
    case 'q':
        exit(0);
    }

    glutPostRedisplay();
}

static GLint prevX;
static GLint prevY;

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
    // glMatrixMode(GL_MODELVIEW);
    // glRotated((GLdouble)x - prevX, 0, -1, 0);
    // glRotated((GLdouble)y - prevY, -1, 0, 0);
	// prevX = x;
	// prevY = y;

    // if mouse is on right bottom
	// if (x > glutGet(GLUT_WINDOW_WIDTH) / 2.0 && y < glutGet(GLUT_WINDOW_HEIGHT) / 2.0)
	// {
    //     robot.setScale(200);
	// }
	// else
	// {
	// 	glMatrixMode(GL_MODELVIEW);
	// 	glRotated((GLdouble)x - prevX, 0, -1, 0);
	// 	glRotated((GLdouble)y - prevY, -1, 0, 0);
	// 	prevX = x;
	// 	prevY = y;
	// }

    // glutPostRedisplay();
}

void updateTime(int value)
{
    gTime += gTimeInterval * doTimeFlow;
    gTime %= 10 * 360;

    glutTimerFunc(gTimeIntervalMS, updateTime, 1);
}

void initRendering()
{
    GLfloat light_specular[] = { 0.8, 0.5, 0.8, 1.0 };
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light_position[] = { 0.f, -2.5f, 2.5f, 0.0f };

    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
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

void reshape(int width, int height)
{
    glViewport(0, 0, width / 2.0, height / 2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(
        -1 * (width / (double)initialWidth),
         1 * (width / (double)initialWidth),
        -1 * (height / (double)initialHeight),
         1 * (height / (double)initialHeight),
        10, -10
    );
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[]) 
{
    setlocale(LC_ALL, "KOREAN");

	robot.setAnimation(animations[iAnimation]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(initialWidth, initialHeight);
    glutCreateWindow("Robot Animation");

    glutDisplayFunc(display);
    // glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMotion);

    glutTimerFunc(gTimeIntervalMS, updateTime, 1);

    initRendering();
    keyboard('k', 0, 0);

    glutMainLoop();

    return 0;
}

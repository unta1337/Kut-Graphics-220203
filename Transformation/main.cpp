#include <cstdlib>
#include <cmath>

#include "draw.hpp"
#include "util.hpp"

// ���� ��ǥ��� ǥ����.
static double P[12] =
{
    0.3, 0.2, 0.1, 1,
    0.7, 0.2, 0.1, 1,
    0.5, 0.7, 0.1, 1
};
static double Q[12];
static double R[12];

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // �Ϲ����� �ﰢ�� ��� �þ��ɽ�Ű �ﰢ�� ���.
    glColor3f(1.0, 0.0, 0.0);
    drawSierpinskiGasket4dV(P);
    glColor3f(0.0, 0.0, 1.0);
    drawSierpinskiGasket4dV(Q);
    glColor3f(0.0, 1.0, 0.0);
    drawSierpinskiGasket4dV(R);
    coord();

    glFlush();
}

void keyboard(unsigned char key, int x, int y) 
{
    double m1[16], m2[16], m3[16];

    // ���ο� ��ȯ�� �����ϴ� ��쿡 ���� Q, R, S ��� �ʱ�ȭ.
    if (key != 'i')
    {
        memset(Q, 0, 12 * sizeof(double));
        memset(R, 0, 12 * sizeof(double));
    }

    if (key == 'i') 
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
    else if (key == 't') 
    {
        matTrans(m1, -1, -0.5, 0);
        matPrint(m1);
        transformTri(m1, P, Q);
    }
    else if (key == 's')
    {
        matScale(m1, 1.5, 1.2, 1.4);
        matPrint(m1);
        transformTri(m1, P, Q);
    } 
    else if (key == 'x') 
    {
        matRotateX(m1, 60);
        matPrint(m1);
        transformTri(m1, P, Q);
    } 
    else if (key == 'y') 
    {
        matRotateY(m1, 60);
        matPrint(m1);
        transformTri(m1, P, Q);
    } 
    else if (key == 'z') 
    {
        matRotateZ(m1, 60);
        matPrint(m1);
        transformTri(m1, P, Q);
    } 
    else if (key == 'Z') 
    {
        double temp[12];

        // ���� ��ȯ: ������ ȸ��.
        /*
         * ù ��ȯ���� ȸ�� ��ȯ�� �����Ѵ�.
         * ���� ��ȯ ���� ������������ �Ÿ����� ���� �����̵��Ѵ�.
         */
        matRotateZ(m1, 60);
        matPrint(m1);
        transformTri(m1, P, Q);

        double dx = Q[0] - P[0];
        double dy = Q[1] - P[1];
        double dz = Q[2] - P[2];

        memcpy(temp, Q, 12 * sizeof(double));
        matTrans(m1, -dx, -dy, -dz);
        matPrint(m1);
        transformTri(m1, temp, Q);
    } 
    else if (key == 'c') 
    {
        double temp[12];

        // ���� ��ȯ: ������ �����ϸ�.
        /*
         * ù ��ȯ���� ���� ��ȯ�� �����Ѵ�.
         * ���� ��ȯ ���� ������������ �Ÿ����� ���� �����̵��Ѵ�.
         */
        matScale(m1, 1.5, 1.2, 1.4);
        matPrint(m1);
        transformTri(m1, P, Q);

        double dx = Q[0] - P[0];
        double dy = Q[1] - P[1];
        double dz = Q[2] - P[2];

        memcpy(temp, Q, 12 * sizeof(double));
        matTrans(m1, -dx, -dy, -dz);
        matPrint(m1);
        transformTri(m1, temp, Q);
    } 
    else if (key == 'h') 
    {
        matShearX(m1, 0.5, 0);
        matPrint(m1);
        transformTri(m1, P, Q);
    } 
    else if (key == 'C')
    {
        // Ŀ���� ���� ��ȯ.

        double temp[12];

        // ���� �ٸ� ȸ�� ��ȯ�� ���ʷ� �����Ͽ� ���� ��ȯ�� ������ �� �ִ�.
        /*
         * �Ϲ������� T1, T2��� �Ϸ��� ��ȯ�� ���ʷ� ������ ���� �Ʒ� ��ȯ�� �����ϴ�.
         * 
         * T = T2 * T1
         * T * M
         * 
         * ��, ȸ���� ���� ��ȯ�� ��ȯ ��� ���� ������ ����
         * �ٸ� ��ȯ�� �� �� �����Ƿ� ���ǰ� �ʿ��ϴ�.
         * 
         * Ư�� �Ʒ��� ��� ������ ��ȯ�� X�� -> Y���� ������ ��ȯ�� �����Ѵ�. (�Ķ� �ﰢ��)
         * �ݸ鿡 �Ʒ����� ��ȯ�� X�� -> Y���� ������ ��ȯ�� �����Ѵ�. (��� �ﰢ��)
         * �� ��ȯ�� ���� ������ �ٸ����� �� ����� �ٸ��� Ȯ���� �� �ִ�.
         */
        matRotateX(m1, 60);
        matPrint(m1);
        transformTri(m1, P, Q);

        memcpy(temp, Q, 12 * sizeof(double));
        matRotateY(m1, 60);
        matPrint(m1);
        transformTri(m1, temp, Q);

        matRotateY(m1, 60);
        matPrint(m1);
        transformTri(m1, P, R);

        memcpy(temp, R, 12 * sizeof(double));
        matRotateZ(m1, 60);
        matPrint(m1);
        transformTri(m1, temp, R);
    }
    else if (key == 'q')
    {
        exit(0);
    }

    glutPostRedisplay();
}

static double PrevX, PrevY;

void mouseClick(int button, int state, int x, int y) 
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
        PrevX = x;
        PrevY = y;
    }
}

void mouseMotion(GLint x, GLint y) 
{
    glMatrixMode(GL_MODELVIEW);
    glRotated(x - PrevX, 0, 1, 0);
    glRotated(y - PrevY, 1, 0, 0);
    PrevX = x;
    PrevY = y;
    glutPostRedisplay();
}

// �޴��� Ű���� �Է��� �ϴ��� ������Ű�� ���� int -> unsigned char�� ��ȯ�Ͽ� keyboard �Լ� ȣ��.
void menuEnable(int entryID)
{
    keyboard((unsigned char)entryID, 0, 0);
}

int main(int argc, char* argv[]) 
{
    glutInit(&argc, argv);                      // GLUT �ʱ�ȭ.
    glutInitWindowSize(500, 500);               // ������ ũ��.
    glutInitWindowPosition(1, 0);               // ������ ��ġ.
    glutCreateWindow("Geometric Transform");    // ������ ����.
    glClearColor(1.0, 1.0, 1.0, 1.0);           // ���� ����.

    glutDisplayFunc(display);                   // ���÷��� �ݹ� ���.
    glutKeyboardFunc(keyboard);                 // Ű���� �ݹ� ���.
    glutMouseFunc(mouseClick);                  // ���콺 �ݹ� ���.
    glutMotionFunc(mouseMotion);                // ���콺 ��� �ݹ� ���.

    glutCreateMenu(menuEnable);                 // �޴� �ݹ� ���.
	glutAddMenuEntry("���� ��� ����", 'i');
	glutAddMenuEntry("�̵� ��ȯ", 't');
	glutAddMenuEntry("���� ��ȯ", 's');
	glutAddMenuEntry("X�� ȸ�� (Pitch, YZ)", 'x');
	glutAddMenuEntry("Y�� ȸ�� (Roll, XZ)", 'y');
	glutAddMenuEntry("Z�� ȸ�� (Yaw, XY)", 'z');
	glutAddMenuEntry("�и� ��ȯ", 'h');
	glutAddMenuEntry("���� ��ȯ: ������ Z�� ȸ�� (Yaw, XY)", 'Z');
	glutAddMenuEntry("���� ��ȯ: ������ �����ϸ�", 'c');
	glutAddMenuEntry("���� ��ȯ: Ŀ���� ���� ��ȯ (ȸ�� ��ȯ)", 'C');
	glutAddMenuEntry("����", 'q');
	glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();                             // GLUT event processing loop.
    return 0;
}

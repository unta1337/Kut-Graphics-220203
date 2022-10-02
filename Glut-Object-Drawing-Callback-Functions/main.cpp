#include <iostream>
#include <vector>
#include <functional>

#include <glut.h>

#include "draw.hpp"

// �ε����� ���� �� �Լ��� ��ȸ�� �� �ֵ��� std::vector�� std::function ���.
std::vector<std::function<void()>> funcs
{
	[]() { glutWireCube(1.0); },
	[]() { glutWireSphere(0.5, 10, 10); },
	[]() { glutWireCone(1, 1, 10, 10); },
	[]() { glutWireTorus(0.5, 1.5, 10, 10); },
	[]() { glutWireTetrahedron(); },
	[]() { glutWireDodecahedron(); },
	[]() { glutWireOctahedron(); },
	[]() { glutWireIcosahedron(); },
	[]() { glutWireTeapot(0.5); },
	[]() { drawName(); },
	[]() { drawSierpinskiGasket(); }
};

int fIndex;			// �Լ� ��ȸ�� �ε���.
int rotate = 1;		// �Լ� ��ȸ �� �� ���� �ѱ�� ����.

// ���콺 �̺�Ʈ ó���� ���� ����.
int prevX;
int prevY;
bool leftMousePressed;

// �� ���� �ֱ⸶�� ȭ���� �׸��� �Լ�.
void show()
{
	background(0);

	glColor3f(0, 1, 0);
	funcs[fIndex]();
	fIndex += rotate;
	fIndex %= funcs.size();

	glFlush();
}

// Ÿ�̸� �ݹ�� �Լ�.
void update(int value)
{
	glutPostRedisplay();
	glutTimerFunc(500, update, 1);
}

void handleKeyboardInput(unsigned char key, int x, int y)
{
	// ������ ���� ���� ���� ���ڸ� �ش� ���� ���.
	if ('1' <= key && key <= funcs.size() + '0')
	{
		fIndex = key - '0' - 1;
		return;
	}

	// ��Ÿ Ű���� �Է� ó��.
	switch (key)
	{
	case 'a':
		rotate = 1 - rotate;
		break;
	case 'i':
		fIndex = 0;
		break;
	case 'q':
		exit(0);
	}
}

// ���콺 ��ġ ���.
void printMouseInput(int button, int state, int x, int y)
{
	std::cout << "Button: " << (button == 0 ? "Left" : (button == 1 ? "Middle" : "Right")) << "\n";
	std::cout << "State: " << (state == 0 ? "Pressed" : "Released") << "\n";
	std::cout << "(x, y): (" << x << ", " << y << ")\n";
}

// ���콺 Ŭ�� �� ���� ���� ����.
void handleMouseClickInput(int button, int state, int x, int y)
{
	static int prevRotate;

	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			leftMousePressed = true;

			prevRotate = rotate;
			rotate = 0;

			prevX = x;
			prevY = y;
		}
		else
		{
			leftMousePressed = false;

			rotate = prevRotate;
		}
	}
}

// ���콺 �̵� �� ȭ�� ȸ��.
void handleMoudeMotionInput(GLint x, GLint y)
{
	if (!leftMousePressed)
		return;

	glMatrixMode(GL_MODELVIEW);

	glRotated(x - prevX, 0, 1, 0);
	glRotated(y - prevY, 1, 0, 0);

	prevX = x;
	prevY = y;

	glutPostRedisplay();
}

// �޴� �ε����� �����ϴ� ���� ���.
void handleMenu(int entryID)
{
	fIndex = entryID;

	glutPostRedisplay();
}

// ���� �缳��.
void handleReshape(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width / 300.0, width / 300.0, -height / 300.0, height / 300.0, -100, 100);

    glMatrixMode(GL_MODELVIEW);

	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);

	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

	glutDisplayFunc(show);

	glutTimerFunc(500, update, 1);

	glutKeyboardFunc(handleKeyboardInput);

	glutMouseFunc(handleMouseClickInput);
	glutMotionFunc(handleMoudeMotionInput);

	glutCreateMenu(handleMenu);
	glutAddMenuEntry("Draw Wire Cube", 0);
	glutAddMenuEntry("Draw Wire Sphere", 1);
	glutAddMenuEntry("Draw Wire Cone", 2);
	glutAddMenuEntry("Draw Wire Torus", 3);
	glutAddMenuEntry("Draw Wire Tetrahedron", 4);
	glutAddMenuEntry("Draw Wire Dodecahedron", 5);
	glutAddMenuEntry("Draw Wire Octahedron", 6);
	glutAddMenuEntry("Draw Wire Icosahedron", 7);
	glutAddMenuEntry("Draw Wire Teapot", 8);
	glutAddMenuEntry("Draw Name", 9);
	glutAddMenuEntry("Draw Sierpinski Gasket", 10);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutReshapeFunc(handleReshape);

	glutMainLoop();

	return 0;
}

#include <iostream>
#include <vector>
#include <functional>

#include <glut.h>

#include "draw.hpp"

// 인덱스를 통해 각 함수를 순회할 수 있도록 std::vector와 std::function 사용.
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

int fIndex;			// 함수 순회용 인덱스.
int rotate = 1;		// 함수 순회 시 한 번에 넘기는 개수.

// 마우스 이벤트 처리를 위한 변수.
int prevX;
int prevY;
bool leftMousePressed;

// 매 갱신 주기마다 화면을 그리는 함수.
void show()
{
	background(0);

	glColor3f(0, 1, 0);
	funcs[fIndex]();
	fIndex += rotate;
	fIndex %= funcs.size();

	glFlush();
}

// 타이머 콜백용 함수.
void update(int value)
{
	glutPostRedisplay();
	glutTimerFunc(500, update, 1);
}

void handleKeyboardInput(unsigned char key, int x, int y)
{
	// 도형의 개수 범위 내의 숫자면 해당 도형 출력.
	if ('1' <= key && key <= funcs.size() + '0')
	{
		fIndex = key - '0' - 1;
		return;
	}

	// 기타 키보드 입력 처리.
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

// 마우스 위치 출력.
void printMouseInput(int button, int state, int x, int y)
{
	std::cout << "Button: " << (button == 0 ? "Left" : (button == 1 ? "Middle" : "Right")) << "\n";
	std::cout << "State: " << (state == 0 ? "Pressed" : "Released") << "\n";
	std::cout << "(x, y): (" << x << ", " << y << ")\n";
}

// 마우스 클릭 시 관련 변수 갱신.
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

// 마우스 이동 시 화면 회전.
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

// 메뉴 인덱스에 대응하는 도형 출력.
void handleMenu(int entryID)
{
	fIndex = entryID;

	glutPostRedisplay();
}

// 비율 재설정.
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

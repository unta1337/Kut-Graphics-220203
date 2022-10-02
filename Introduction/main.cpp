#include <iostream>

#include <glut.h>

#include "utility.hpp"

void drawName()
{
	static bool showCrossLine = false;

	if (showCrossLine)
	{
		glColor3f(1, 0, 0);
		rect(-1, 0.025, 2, 0.05);
		rect(-0.025, 1, 0.05, 2);
	}

	glColor3f(1, 1, 1);

	// '沿'
	float xBegin = -0.9;
	float yBegin = 0.9;

	// 'ぁ'
	rect(xBegin, yBegin, 0.6, 0.05);
	rect(-0.1 - 0.05 - 0.1 - 0.05, yBegin, 0.05, 0.35);

	// 'び'
	rect(-0.1 - 0.05, yBegin, 0.05, 0.35);

	// 'け'
	rect(xBegin, yBegin - 0.45, 0.8, 0.05);
	rect(xBegin, yBegin - 0.8 + 0.05, 0.8, 0.05);
	rect(xBegin, yBegin - 0.45, 0.05, 0.35);
	rect(-0.1 - 0.05, yBegin - 0.45, 0.05, 0.35);

	// '失'
	xBegin = 0.1;
	yBegin = 0.9;

	// 'さ'
	rect(xBegin, yBegin, 0.05, 0.35);
	rect(xBegin, yBegin, 0.6, 0.05);
	rect(1 -0.1 - 0.05 - 0.1 - 0.05, yBegin, 0.05, 0.35);

	// 'っ'
	rect(1 -0.1 - 0.15, yBegin - 0.1, 0.1, 0.05);
	rect(1 -0.1 - 0.05, yBegin, 0.05, 0.35);

	// 'し'
	ellipse(xBegin + 0.4, yBegin - 0.625, 0.4, 0.175);
	glColor3f(0, 0, 0);
	ellipse(xBegin + 0.4, yBegin - 0.625, 0.34, 0.13);
	glColor3f(1, 1, 1);

	// '括'
	xBegin = -0.9;
	yBegin = -0.1;

	// 'い'
	rect(xBegin, yBegin, 0.05, 0.35);
	rect(xBegin, yBegin - 0.3, 0.6, 0.05);

	// 'づ'
	rect(-0.4 - 0.15, yBegin - 0.05, 0.4, 0.05);
	rect(-0.4 - 0.15, yBegin - 0.15, 0.4, 0.05);
	rect(-0.1 - 0.05, yBegin, 0.05, 0.35);

	// 'し'
	ellipse(xBegin + 0.4, yBegin - 0.625, 0.4, 0.175);
	glColor3f(0, 0, 0);
	ellipse(xBegin + 0.4, yBegin - 0.625, 0.34, 0.13);
	glColor3f(1, 1, 1);
}

void __drawSierpinskiGasket(float x1, float y1, float x2, float y2, float x3, float y3, int level, int maxLevel)
{
	if (level == maxLevel)
		return;

	glColor3f(0, 0, 0);
	tri(x1, y1, x2, y2, x3, y3);

	float newX1 = (x1 + x3) / 2;
	float newY1 = (y1 + y3) / 2;

	float newX2 = (x1 + x2) / 2;
	float newY2 = (y1 + y2) / 2;

	float newX3 = (x3 + x2) / 2;
	float newY3 = (y3 + y2) / 2;

	glColor3f(1, 1, 1);
	tri(newX1, newY1, newX2, newY2, newX3, newY3);

	__drawSierpinskiGasket(x1, y1, newX2, newY2, newX1, newY1, level + 1, maxLevel);
	__drawSierpinskiGasket(newX1, newY1, newX3, newY3, x3, y3, level + 1, maxLevel);
	__drawSierpinskiGasket(newX2, newY2, x2, y2, newX3, newY3, level + 1, maxLevel);
}

void drawSierpinskiGasket(int maxLevel = 5)
{
	__drawSierpinskiGasket(0, 1, -1, -1, 1, -1, 0, maxLevel);
}

void myDisplay()
{
	// drawName();

	glColor3f(1, 1, 1);
	rect(-1, 1, 2, 2);
	drawSierpinskiGasket();

	glFlush();
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
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glutDisplayFunc(myDisplay);
	glutMainLoop();

	return 0;
}

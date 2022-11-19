#include <cmath>

#include "Draw.h"
#include "Util.h"

#include <glut.h>

inline int ROUND(double v) { return (int)(v + 0.5); }
inline double dist(double dx, double dy) { return sqrt(dx * dx + dy * dy); }
inline void swap(int* a, int* b) { int temp = *a; *a = *b; *b = temp; }

static int winW = 500, winH = 500;
static int nGrid = 30;
static double pixelW, pixelH;
static int px, py, qx, qy;
static int mode = 0;

void draw2DGrid()
{
	glLineWidth(1);
	glBegin(GL_LINES);
	for (int i = 0; i <= nGrid; i++)
	{
		glVertex2d(i * pixelW, 0);
		glVertex2d(i * pixelW, winH);
		glVertex2d(0, i * pixelH);
		glVertex2d(winW, i * pixelH);
	}
	glEnd();
}

void drawPixel(GLint x, GLint y)
{
	int xi = x * pixelW;
	int yi = y * pixelH;
	glRectd(xi, yi, xi + pixelW, yi + pixelH);
}

void lineBasic(GLint x1, GLint y1, GLint x2, GLint y2)
{
	double m = (double)(y2 - y1) / (x2 - x1);

	// 기울기에 따라서 서로 다른 처리. (증분 기준 x or y)
	if (abs(m) < 1)
	{
		// 작은 좌표부터 큰 좌표까지.
		for (int x = (x1 < x2 ? x1 : x2); x <= (x1 > x2 ? x1 : x2); x++)
		{
			double y = m * (x - x1) + y1;
			drawPixel(x, ROUND(y));
		}
	}
	else
	{
		m = 1 / m;

		for (int y = (y1 < y2 ? y1 : y2); y <= (y1 > y2 ? y1 : y2); y++)
		{
			double x = m * (y - y1) + x1;
			drawPixel(ROUND(x), y);
		}
	}
}

void lineDDA(GLint x1, GLint y1, GLint x2, GLint y2)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int steps = max(dx, dy);

	// 증분값에 +/-가 포함되므로 기울기 고려하지 않아도 됨.
	double xInc = (double)(x2 - x1) / steps;
	double yInc = (double)(y2 - y1) / steps;

	double x = x1;
	double y = y1;

	for (int i = 0; i <= steps; i++, x += xInc, y += yInc)
		drawPixel(ROUND(x), ROUND(y));
}

void lineBresenham(GLint x1, GLint y1, GLint x2, GLint y2)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);

	// 기울기에 따라서 증분 기준 다르게 처리.
	if (dy <= dx)
	{
		int p = 2 * (dy - dx);
		int y = y1;
		
		// 기울기에 따라서 증분 변화.
		int xInc = 1;
		if (x2 < x1)
			xInc = -1;
		
		int yInc = 1;
		if (y2 < y1)
			yInc = -1;
		
		for (int x = x1; (x1 <= x2 ? x <= x2 : x >= x2); x += xInc)
		{
			if (0 >= p)
				p += 2 * dy;
			else
				p += 2 * (dy - dx), y += yInc;
			drawPixel(x, y);
		}
	}
	else
	{
		int p = 2 * (dx - dy);
		int x = x1;
		
		int xInc = 1;
		if (x2 < x1)
			xInc = -1;
		
		int yInc = 1;
		if (y2 < y1)
			yInc = -1;
		
		for (int y = y1; (y1 <= y2 ? y <= y2 : y >= y2); y += yInc)
		{
			if (0 >= p)
				p += 2 * dx;
			else
				p += 2 * (dx - dy), x += xInc;
			drawPixel(x, y);
		}
	}
}

void drawCirclePoint(GLint x, GLint y)
{
	drawPixel(x, y);
	drawPixel(-x, y);
	drawPixel(x, -y);
	drawPixel(-x, -y);

	drawPixel(y, x);
	drawPixel(-y, x);
	drawPixel(y, -x);
	drawPixel(-y, -x);
}

void circleMidPoint(int cx, int cy, GLint radius)
{
	// 중심을 기준점으로 이동.
	glPushMatrix();
	int ccx = (int)(cx / pixelW) * pixelW;
	int ccy = (int)(cy / pixelH) * pixelH;
	glTranslated(ccx, ccy, 0);

	int x = 0;
	int y = radius;
	int d = 1 - radius;

	drawCirclePoint(x, y);
	for (; y > x; x++)
	{
		if (d < 0)
			d = d + 2 * x + 3;
		else
			d = d + 2 * (x - y) + 5, y--;
		drawCirclePoint(x, y);
	}
	glPopMatrix();
}

void display()
{
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.5, 0.5);
	draw2DGrid();

	glColor3f(0, 0, 0);
	switch (mode)
	{
	case 0:
		lineBasic(px / pixelW, py / pixelH, qx / pixelW, qy / pixelH);
		break;
	case 1:
		lineDDA(px / pixelW, py / pixelH, qx / pixelW, qy / pixelH);
		break;
	case 2:
		lineBresenham(px / pixelW, py / pixelH, qx / pixelW, qy / pixelH);
		break;
	case 3:
		int radius = ROUND(dist(px / pixelW - qx / pixelW, py / pixelH - qy / pixelH));
		circleMidPoint(px, py, radius);
		break;
	}

	glColor3f(1, 0, 1);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(px, py);
	glVertex2f(qx, qy);
	glEnd();
	glFlush();
}

void mouseClick(GLint button, GLint state, GLint x, GLint y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		px = x;
		py = winH - y;
	}
}

void mouseMotion(GLint x, GLint y)
{
	qx = x;
	qy = winH - y;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'n':
		mode += 1;
		mode %= 4;
		std::cout << mode << "\n";
		break;
	case 'q':
		exit(0);
	}

	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(winW, winH);
	glutCreateWindow("Rasterization");

	pixelW = winW / nGrid;
	pixelH = winH / nGrid;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, winW, 0, winH, -1, 1);

	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}

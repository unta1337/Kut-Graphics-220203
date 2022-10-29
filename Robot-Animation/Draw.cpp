#include "Draw.h"

void background(double red, double green, double blue, double alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void background(double red, double green, double blue)
{
	background(red, green, blue, 1);
}

void background(double gray)
{
	background(gray, gray, gray);
}

void rect4dV(double* v)
{
	glBegin(GL_POLYGON);
    glVertex4dv(v);
    glVertex4dv(v + 4);
    glVertex4dv(v + 8);
    glVertex4dv(v + 12);
    glEnd();
}

void tri4dV(double* v)
{
    glBegin(GL_TRIANGLES);
    glVertex4dv(v);
    glVertex4dv(v + 4);
    glVertex4dv(v + 8);
    glEnd();
}

void __drawSierpinskiGasket4dV(double* v, int level, int maxLevel)
{
	float drawColor[4];
	glGetFloatv(GL_CURRENT_COLOR, drawColor);

	double* v1 = v;
	double* v2 = v + 4;
	double* v3 = v + 8;

	double nv1[4] = { (v1[0] + v3[0]) / 2, (v1[1] + v3[1]) / 2, (v1[2] + v3[2]) / 2, 1 };
	double nv2[4] = { (v1[0] + v2[0]) / 2, (v1[1] + v2[1]) / 2, (v1[2] + v2[2]) / 2, 1 };
	double nv3[4] = { (v3[0] + v2[0]) / 2, (v3[1] + v2[1]) / 2, (v3[2] + v2[2]) / 2, 1 };

	double nv[3][3][4] =
	{
		{
			{  v1[0],  v1[1],  v1[2],  v1[3] },
			{ nv2[0], nv2[1], nv2[2], nv2[3] },
			{ nv1[0], nv1[1], nv1[2], nv1[3] },
		},
		{
			{ nv1[0], nv1[1], nv1[2], nv1[3] },
			{ nv3[0], nv3[1], nv3[2], nv3[3] },
			{  v3[0],  v3[1],  v3[2],  v3[3] },
		},
		{
			{ nv2[0], nv2[1], nv2[2], nv2[3] },
			{  v2[0],  v2[1],  v2[2],  v2[3] },
			{ nv3[0], nv3[1], nv3[2], nv3[3] },
		}
	};

	if (level == maxLevel)
	{
		glColor4f(drawColor[0], drawColor[1], drawColor[2], drawColor[3]);
		for (int i = 0; i < 3; i++)
			tri4dV((double*)nv + 12 * i);

		return;
	}

	__drawSierpinskiGasket4dV((double*)nv, level + 1, maxLevel);
	__drawSierpinskiGasket4dV((double*)nv + 12, level + 1, maxLevel);
	__drawSierpinskiGasket4dV((double*)nv + 24, level + 1, maxLevel);
}

void drawSierpinskiGasket4dV(double* v, int maxLevel)
{
	__drawSierpinskiGasket4dV(v, 0, maxLevel);
}

void line(double x1, double y1, double z1, double x2, double y2, double z2)
{
    glBegin(GL_LINES);

    glVertex3d(x1, y1, z1);
    glVertex3d(x2, y2, z2);

    glEnd();
}

void triangle4d(double* p)
{
    glBegin(GL_TRIANGLES);

    glVertex4dv(p);
    glVertex4dv(p + 4);
    glVertex4dv(p + 8);

    glEnd();
}

void coord()
{
    glBegin(GL_LINES);

    glColor3d(1, 0, 0);
    glVertex3d(-0.1, 0, 0);
    glVertex3d(1, 0, 0);

    glColor3d(0, 1, 0);
    glVertex3d(0, -0.1, 0);
    glVertex3d(0, 1, 0);

    glColor3d(0, 0, 1);
    glVertex3d(0, 0, -0.1);
    glVertex3d(0, 0, 1);

    glEnd();
}

void drawString(const char* str)
{
	for (int i = 0; str[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
}

void drawCoord(double len)
{
	glDisable(GL_LIGHTING);

	glColor3f(1.0f, 0, 0);
	line(0, 0, 0, len, 0, 0);
	glRasterPos3f(len, 0, 0);
	drawString("x");

	glColor3f(0, 1.0f, 0);
	line(0, 0, 0, 0, len, 0);
	glRasterPos3f(0, len, 0);
	drawString("y");

	glColor3f(0, 0, 1.0f);
	line(0, 0, 0, 0, 0, -len);
	glRasterPos3f(0, 0, -len);
	drawString("z");

	glEnable(GL_LIGHTING);
}

#ifndef __DRAW_H
#define __DRAW_H

#include <glut.h>

void background(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void background(float red, float green, float blue)
{
	background(red, green, blue, 1);
}

void background(float gray)
{
	background(gray, gray, gray);
}

void rect(float x, float y, float width, float height)
{
	glBegin(GL_POLYGON);

	glVertex3f(x, y, 0);
	glVertex3f(x + width, y, 0);
	glVertex3f(x + width, y - height, 0);
	glVertex3f(x, y - height, 0);

	glEnd();
}

void tri(float x1, float y1, float x2, float y2, float x3, float y3)
{
	glBegin(GL_TRIANGLES);

	glVertex3f(x1, y1, 0);
	glVertex3f(x2, y2, 0);
	glVertex3f(x3, y3, 0);

	glEnd();
}

// Ref: https://stackoverflow.com/questions/5886628/effecient-way-to-draw-ellipse-with-opengl-or-d3d
void ellipse(float cx, float cy, float rx, float ry, int num_segments = 200) 
{ 
    float theta = 2 * 3.1415926 / float(num_segments); 
    float c = cosf(theta);
    float s = sinf(theta);
    float t;

    float x = 1;
    float y = 0; 

    glBegin(GL_POLYGON); 

    for(int ii = 0; ii < num_segments; ii++) 
    { 
        glVertex2f(x * rx + cx, y * ry + cy);

        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    } 

    glEnd(); 
}

void circle(float x, float y, float r, int num_segments = 200)
{
    ellipse(x, y, r, r, num_segments);
}

void drawName()
{
	float drawColor[4];
	glGetFloatv(GL_CURRENT_COLOR, drawColor);

	float backgroundColor[4];
	glGetFloatv(GL_COLOR_CLEAR_VALUE, backgroundColor);

	glColor4f(drawColor[0], drawColor[1], drawColor[2], drawColor[3]);

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
	glColor4f(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);
	ellipse(xBegin + 0.4, yBegin - 0.625, 0.34, 0.13);
	glColor4f(drawColor[0], drawColor[1], drawColor[2], drawColor[3]);

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
	glColor4f(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);
	ellipse(xBegin + 0.4, yBegin - 0.625, 0.34, 0.13);
	glColor4f(drawColor[0], drawColor[1], drawColor[2], drawColor[3]);
}

void __drawSierpinskiGasket(float x1, float y1, float x2, float y2, float x3, float y3, int level, int maxLevel)
{
	float drawColor[4];
	glGetFloatv(GL_CURRENT_COLOR, drawColor);

	float backgroundColor[4];
	glGetFloatv(GL_COLOR_CLEAR_VALUE, backgroundColor);

	if (level == maxLevel)
		return;

	tri(x1, y1, x2, y2, x3, y3);

	float newX1 = (x1 + x3) / 2;
	float newY1 = (y1 + y3) / 2;

	float newX2 = (x1 + x2) / 2;
	float newY2 = (y1 + y2) / 2;

	float newX3 = (x3 + x2) / 2;
	float newY3 = (y3 + y2) / 2;

	glColor4f(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);
	tri(newX1, newY1, newX2, newY2, newX3, newY3);

	glColor4f(drawColor[0], drawColor[1], drawColor[2], drawColor[3]);
	__drawSierpinskiGasket(x1, y1, newX2, newY2, newX1, newY1, level + 1, maxLevel);
	__drawSierpinskiGasket(newX1, newY1, newX3, newY3, x3, y3, level + 1, maxLevel);
	__drawSierpinskiGasket(newX2, newY2, x2, y2, newX3, newY3, level + 1, maxLevel);
}

void drawSierpinskiGasket(int maxLevel = 5)
{
	__drawSierpinskiGasket(0, 1, -1, -1, 1, -1, 0, maxLevel);
}

#endif

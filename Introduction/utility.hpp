#ifndef __SHAPE_H
#define __SHAPE_H

#include <glut.h>

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
        glVertex2f(x * rx + cx, y * ry + cy);//output vertex 

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

#endif

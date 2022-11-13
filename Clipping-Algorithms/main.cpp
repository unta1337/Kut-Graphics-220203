#include <algorithm>

#include "Draw.h"
#include "Util.h"

#include <glut.h>

static const int initialWidth = 600;
static const int initialHeight = 600;

static double unitWidth = 2.0 / 3;
static double unitHeight = 2.0 / 3;

static double sections[9][16] =
{
	{ -1.0 + 0 * unitWidth, 1.0 - 0 * unitHeight, 0, 1,
	  -1.0 + 1 * unitWidth, 1.0 - 0 * unitHeight, 0, 1,
	  -1.0 + 1 * unitWidth, 1.0 - 1 * unitHeight, 0, 1,
	  -1.0 + 0 * unitWidth, 1.0 - 1 * unitHeight, 0, 1 },
	{ -1.0 + 1 * unitWidth, 1.0 - 0 * unitHeight, 0, 1,
	  -1.0 + 2 * unitWidth, 1.0 - 0 * unitHeight, 0, 1,
	  -1.0 + 2 * unitWidth, 1.0 - 1 * unitHeight, 0, 1,
	  -1.0 + 1 * unitWidth, 1.0 - 1 * unitHeight, 0, 1 },
	{ -1.0 + 2 * unitWidth, 1.0 - 0 * unitHeight, 0, 1,
	  -1.0 + 3 * unitWidth, 1.0 - 0 * unitHeight, 0, 1,
	  -1.0 + 3 * unitWidth, 1.0 - 1 * unitHeight, 0, 1,
	  -1.0 + 2 * unitWidth, 1.0 - 1 * unitHeight, 0, 1 },

	{ -1.0 + 0 * unitWidth, 1.0 - 1 * unitHeight, 0, 1,
	  -1.0 + 1 * unitWidth, 1.0 - 1 * unitHeight, 0, 1,
	  -1.0 + 1 * unitWidth, 1.0 - 2 * unitHeight, 0, 1,
	  -1.0 + 0 * unitWidth, 1.0 - 2 * unitHeight, 0, 1 },
	{ -1.0 + 1 * unitWidth, 1.0 - 1 * unitHeight, 0, 1,
	  -1.0 + 2 * unitWidth, 1.0 - 1 * unitHeight, 0, 1,
	  -1.0 + 2 * unitWidth, 1.0 - 2 * unitHeight, 0, 1,
	  -1.0 + 1 * unitWidth, 1.0 - 2 * unitHeight, 0, 1 },
	{ -1.0 + 2 * unitWidth, 1.0 - 1 * unitHeight, 0, 1,
	  -1.0 + 3 * unitWidth, 1.0 - 1 * unitHeight, 0, 1,
	  -1.0 + 3 * unitWidth, 1.0 - 2 * unitHeight, 0, 1,
	  -1.0 + 2 * unitWidth, 1.0 - 2 * unitHeight, 0, 1 },

	{ -1.0 + 0 * unitWidth, 1.0 - 2 * unitHeight, 0, 1,
	  -1.0 + 1 * unitWidth, 1.0 - 2 * unitHeight, 0, 1,
	  -1.0 + 1 * unitWidth, 1.0 - 3 * unitHeight, 0, 1,
	  -1.0 + 0 * unitWidth, 1.0 - 3 * unitHeight, 0, 1 },
	{ -1.0 + 1 * unitWidth, 1.0 - 2 * unitHeight, 0, 1,
	  -1.0 + 2 * unitWidth, 1.0 - 2 * unitHeight, 0, 1,
	  -1.0 + 2 * unitWidth, 1.0 - 3 * unitHeight, 0, 1,
	  -1.0 + 1 * unitWidth, 1.0 - 3 * unitHeight, 0, 1 },
	{ -1.0 + 2 * unitWidth, 1.0 - 2 * unitHeight, 0, 1,
	  -1.0 + 3 * unitWidth, 1.0 - 2 * unitHeight, 0, 1,
	  -1.0 + 3 * unitWidth, 1.0 - 3 * unitHeight, 0, 1,
	  -1.0 + 2 * unitWidth, 1.0 - 3 * unitHeight, 0, 1 },
};

static double theLine[6] = { -1.2, -0.4, 0, 2.7, 0.3, 0 };
static double theLine2[6];

double xMin = -1.0 + 1 * unitWidth;
double xMax = -1.0 + 2 * unitWidth;
double yMin =  1.0 - 2 * unitHeight;
double yMax =  1.0 - 1 * unitHeight;

const int LEFT   = 0b0001;
const int RIGHT  = 0b0010;
const int BOTTOM = 0b0100;
const int TOP    = 0b1000;

int getRegion(double x, double y)
{
	int result = 0;
	result |= LEFT * (x < xMin);
	result |= RIGHT * (x > xMax);
	result |= BOTTOM * (y < yMin);
	result |= TOP * (y > yMax);

	return result;
}

bool cohenSutherlandLineClip()
{
	memcpy(theLine2, theLine, 6 * sizeof(double));

	int begin = getRegion(theLine2[0], theLine2[1]);
	int end = getRegion(theLine2[3], theLine2[4]);
	bool accept = false;

	while (true)
	{
		if (!(begin | end))
		{
			accept = true;
			break;
		}
		else if (begin & end)
		{
			break;
		}
		else
		{
			double x = 0, y = 0;

			int outcodeOut = end > begin ? end : begin;

			if (outcodeOut & TOP)
			{
				x = theLine2[0] + (theLine2[3] - theLine2[0]) * (yMax - theLine2[1]) / (theLine2[4] - theLine2[1]);
				y = yMax;
			}
			else if (outcodeOut & BOTTOM)
			{
				x = theLine2[0] + (theLine2[3] - theLine2[0]) * (yMin - theLine2[1]) / (theLine2[4] - theLine2[1]);
				y = yMin;
			}
			else if (outcodeOut & RIGHT)
			{
				y = theLine2[1] + (theLine2[4] - theLine2[1]) * (xMax - theLine2[0]) / (theLine2[3] - theLine2[0]);
				x = xMax;
			}
			else if (outcodeOut & LEFT)
			{
				y = theLine2[1] + (theLine2[4] - theLine2[1]) * (xMin - theLine2[0]) / (theLine2[3] - theLine2[0]);
				x = xMin;
			}

			if (outcodeOut == begin)
			{
				theLine2[0] = x;
				theLine2[1] = y;
				begin = getRegion(theLine2[0], theLine2[1]);
			}
			else
			{
				theLine2[3] = x;
				theLine2[4] = y;
				end = getRegion(theLine2[3], theLine2[4]);
			}
		}
	}
	return accept;
}

int clipTest(double p, double q, double* t1, double* t2)
{
	double r;
	int retVal = TRUE;

	if (p < 0.0)
	{
		r = q / p;

		if (r > *t2)
			retVal = FALSE;
		else if (r > *t1)
			*t1 = r;
	}
	else if (p > 0.0)
	{
		r = q / p;

		if (r < *t1)
			retVal = FALSE;
		else if(r < *t2)
			*t2 = r;
	}
	else if (q < 0.0)
	{
		retVal = FALSE;
	}

	return retVal;
}
  
void liangBarskyLineClip()
{
	memcpy(theLine2, theLine, 6 * sizeof(double));

	double t1 = 0.0, t2 = 1.0, dx = theLine2[3] - theLine2[0], dy;

	if (clipTest(-dx, theLine2[0] - xMin, &t1, &t2))
	{
		if (clipTest(dx, xMax - theLine2[0], &t1, &t2))
		{
			dy = theLine2[4] - theLine2[1];

			if (clipTest(-dy, theLine2[1] - yMin, &t1, &t2))
			{
				if (clipTest(dy, yMax - theLine2[1], &t1, &t2))
				{
					if (t2 < 1.0)
					{
						theLine2[3] = theLine2[0] + t2 * dx;
						theLine2[4] = theLine2[1] + t2 * dy;
					}

					if (t1 > 0.0)
					{
						theLine2[0] += t1 * dx;
						theLine2[1] += t1 * dy;
					}
				}
			}
		}
	}
}

void show()
{
	background(0);

	glColor3f(0, 1, 0);
	for (double* section : sections)
		rect4dV(section);

	glColor3f(0, 1, 1);
	line(theLine[0], theLine[1], theLine[2], theLine[3], theLine[4], theLine[5]);

	cohenSutherlandLineClip();
	// liangBarskyLineClip();

	glColor3f(1, 0, 0);
	line(theLine2[0], theLine2[1], theLine2[2], theLine2[3], theLine2[4], theLine2[5]);

	std::cout << theLine2[0] << "\n";
	std::cout << theLine2[1] << "\n";
	std::cout << theLine2[3] << "\n";
	std::cout << theLine2[4] << "\n";

	glFlush();
}

void handleKeyboardInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		exit(0);
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);

	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Clipping Algorithms");
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glutDisplayFunc(show);

	glutKeyboardFunc(handleKeyboardInput);

	glutMainLoop();

	return 0;
}

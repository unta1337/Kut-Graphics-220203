/*
 * 배경 및 도형 등 그리기 함수 모음.
 */

#ifndef __DRAW_H
#define __DRAW_H

#include <cmath>
#include <cstdio>

#include <glut.h>

void background(double red, double green, double blue, double alpha);
void background(double red, double green, double blue);
void background(double gray);
void rect4dV(double* v);
void tri4dV(double* v);
void __drawSierpinskiGasket4dV(double* v, int level, int maxLevel);
void drawSierpinskiGasket4dV(double* v, int maxLevel = 3);
void line(double x1, double y1, double z1, double x2, double y2, double z2);
void triangle4d(double* p);
void coord();
void drawString(const char* str);
void drawCoord(double len);

#endif

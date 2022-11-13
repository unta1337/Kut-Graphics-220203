/*
 * 행렬 연산 벡터 변환 등 유틸리티 모음.
 */

#ifndef __UTIL_H
#define __UTIL_H

#define _USE_MATH_DEFINES

#include <iostream>
#include <cstdio>
#include <cstring>
#include <math.h>
#include <Windows.h>

#include <glut.h>

#define sinDeg(x) sin((double)x * M_PI / 180.0)
#define cosDeg(x) cos((double)x * M_PI / 180.0)

void matSet(
	double* m,
	double m00, double m01, double m02, double m03,
	double m10, double m11, double m12, double m13,
	double m20, double m21, double m22, double m23,
	double m30, double m31, double m32, double m33
);
void matMult(double* m1, double* m2);
void matPrint(double* m);
void matIdentity(double* m);
void matTrans(double* m, double tx, double ty, double tz);
void matScale(double* m, double sx, double sy, double sz);
void matRotateX(double* m, double a);
void matRotateY(double* m, double a);
void matRotateZ(double* m, double a);
void matShearX(double* m, double dy, double dz);
void matShearY(double* m, double dx, double dz);
void matShearZ(double* m, double dx, double dy);
void transform(double* m, double* p, double* q);
void transformTri(double* m, double* p, double* q);
double matMag3dv(double* m);
double matDot3dv(double* p, double* q);
void setMaterialColor(float red, float green, float blue, float alpha);
WCHAR* fileDlg(const WCHAR* filter);

#endif
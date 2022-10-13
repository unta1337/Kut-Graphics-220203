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
)
{
    double mat[16] =
    {
        m00, m01, m02, m03,
	    m10, m11, m12, m13,
		m20, m21, m22, m23,
		m30, m31, m32, m33
    };
    memcpy(m, mat, sizeof(double) * 16);
}

void matMult(double* m1, double* m2)
{
    double n[16];
    for (int k = 0; k < 16; k++)
    {
        n[k] = 0;

        double* p = m1 + (k / 4) * 4;
        double* q = m2 + (k % 4);

        for (int i = 0; i < 4; i++)
            n[k] += p[i] * q[i * 4];
    }
    memcpy(m1, n, sizeof(double) * 16);
}

void matPrint(double* m) {
    for (int i = 0; i < 4; i++) {
        printf("\t[");
        for (int j = 0; j < 4; j++)
            printf("%6.2f ", m[i * 4 + j]);
        printf("]\n");
    }
    printf("\n");
}

void matIdentity(double* m) {
    matSet(
            m,
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    );
}

void matTrans(double* m, double tx, double ty, double tz) {
    matSet(
            m,
            1, 0, 0, tx,
            0, 1, 0, ty,
            0, 0, 1, tz,
            0, 0, 0,  1
    );
}

void matScale(double* m, double sx, double sy, double sz) {
    matSet(
            m,
            sx,  0,  0, 0,
             0, sy,  0, 0,
             0,  0, sz, 0,
             0,  0,  0, 1
    );
}

void matRotateX(double* m, double a) {
    matSet(
		m,
		1,         0,          0, 0,
		0, cosDeg(a), -sinDeg(a), 0,
		0, sinDeg(a),  cosDeg(a), 0,
		0,         0,          0, 1
    );
}

void matRotateY(double* m, double a) {
    matSet(
		m,
		cosDeg(a), 0, -sinDeg(a), 0,
				0, 1,          0, 0,
		sinDeg(a), 0,  cosDeg(a), 0,
				0, 0,          0, 1
    );
}

void matRotateZ(double* m, double a) {
    matSet(
		m,
		cosDeg(a), -sinDeg(a), 0, 0,
		sinDeg(a),  cosDeg(a), 0, 0,
				0,          0, 1, 0,
				0,          0, 0, 1
    );
}

void matShearX(double* m, double dy, double dz) {
    matSet(
		m,
		1, dy, dz, 0,
		0,  1,  0, 0,
		0,  0,  1, 0,
		0,  0,  0, 1
    );
}


void matShearY(double* m, double dx, double dz) {
    matSet(
		m,
		 1, 0,  0, 0,
		dx, 1, dz, 0,
		 0, 0,  1, 0,
		 0, 0,  0, 1
    );
}

void matShearZ(double* m, double dx, double dy) {
    matSet(
		m,
		 1,  0, 0, 0,
		 0,  1, 0, 0,
		dx, dy, 1, 0,
		 0,  0, 0, 1
    );
}

// 정점의 변환 함수 [q] = [M] [p]
void transform(double* m, double* p, double* q) {
    q[0] = q[1] = q[2] = q[3] = 0;
    for (int i = 0; i < 4; i++)
    {
        q[0] += m[i] * p[i];
        q[1] += m[i + 4] * p[i];
        q[2] += m[i + 8] * p[i];
        q[3] += m[i + 12] * p[i];
    }
}

void transformTri(double* m, double* p, double* q)
{
    transform(m, p, q);
    transform(m, p + 4, q + 4);
    transform(m, p + 8, q + 8);
}

double matMag3dv(double* m)
{
    double res = 0;
    for (int i = 0; i < 3; i++)
        res += m[i] * m[i];

    return sqrt(res);
}

double matDot3dv(double* p, double* q)
{
    double res = 0;
    for (int i = 0; i < 3; i++)
        res += p[i] * q[i];

    return res;
}

void setMaterialColor(float red, float green, float blue, float alpha)
{
	float color[4] = { red, green, blue, alpha };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
}

WCHAR* fileDlg(const WCHAR* filter)
{
    const int maxLen = 1024;
    static WCHAR fileName[maxLen] = L"";

    OPENFILENAME openFile;
    memset(&openFile, 0, sizeof(OPENFILENAME));

    openFile.lStructSize = sizeof(OPENFILENAME);
    openFile.hwndOwner = NULL;
    openFile.lpstrFilter = filter;
    openFile.nFilterIndex = 1;
    openFile.lpstrFile = fileName;
    openFile.nMaxFile = maxLen;
    openFile.lpstrTitle = L"Select a file";
    openFile.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

    bool ret = GetOpenFileName(&openFile);

    wprintf(L"%s", fileName);

    return ret ? fileName : NULL;
}

#endif
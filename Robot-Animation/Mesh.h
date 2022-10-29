#ifndef __MESH_H
#define __MESH_H

#include <iostream>
#include <cstdio>

#include <Windows.h>
#include <glut.h>

#include "Util.h"
#include "Draw.h"

class Mesh
{
	struct Vertex;
	struct Face;
	struct Normal;

	int nVtx;
	Vertex* vertex;
	int nFace;
	Face* face;
	Normal* normal;

public:
	Mesh();
	~Mesh();

	void clearASE();
	void readASE(const WCHAR* fileName);
	void draw(float scale = 1.0f, bool bCoord = false);
	void drawColor4fv(float color[4], float scale = 1.0f, bool bCoord = false);
	void setColor(float red, float green, float blue, float alpha);
};

#endif

#ifndef __MESH_H
#define __MESH_H

#include <iostream>

#include <glut.h>

#include "util.hpp"
#include "draw.hpp"

class Mesh
{
	struct Vertex
	{
		float x;
		float y;
		float z;
	};

	struct Face
	{
		int vi[3];
	};

	struct Normal
	{
		float norFace[3];
		float norV1[3];
		float norV2[3];
		float norV3[3];
	};

	int nVtx = 0;
	Vertex* vertex = nullptr;
	int nFace = 0;
	Face* face = nullptr;
	Normal* normal = nullptr;

public:
	Mesh() { }
	~Mesh() { clearASE(); }

	void clearASE()
	{
		if (nVtx != 0)
			delete[] vertex;
		if (nFace != 0)
		{
			delete[] face;
			delete[] normal;
		}

		nVtx = nFace = 0;
	}

	void readASE(const WCHAR* fileName)
	{
		FILE* fp;
		char line[256], str[40];
		float _x, _y, _z;
		int num = 0;

		if ((fp = _wfopen(fileName, L"r")) == NULL)
		{
			std::cout << "File not found.\n";
			return;
		}

		while (fgets(line, 256, fp) != NULL)
		{
			sscanf(line, "%s", str);					// MESH
			if (strcmp(str, "*MESH") == 0)
			{
				fgets(line, 256, fp);					// TIMEVALUE

				fgets(line, 256, fp);					// MESH_NUMVERTEX
				sscanf(line, "%s%d", str, &nVtx);

				fgets(line, 256, fp);					// MESH_NUMFACE
				sscanf(line, "%s%d", str, &nFace);

				vertex = new Vertex[nVtx];
				face = new Face[nFace];
				normal = new Normal[nFace];

				fgets(line, 256, fp);					// MESH_VERTEX_LIST
				sscanf(line, "%s", str);
				if (strcmp(str, "*MESH_VERTEX_LIST") == 0)
				{
					for (int i = 0; i < nVtx; i++)
					{
						fgets(line, 256, fp);			// 정점 정보 읽기.
						sscanf(line, "%s%d%f%f%f", str, &num, &_x, &_y, &_z);

						vertex[i].x = _x;
						vertex[i].y = _y;
						vertex[i].z = _z;
					}
				}

				fgets(line, 256, fp);	// 닫는 중괄호 처리.

				fgets(line, 256, fp);						// MESH_FACE_LIST
				sscanf(line, "%s", str);
				if (strcmp(str, "*MESH_FACE_LIST") == 0)
				{
					for (int i = 0; i < nFace; i++)
					{
						fgets(line, 256, fp);
						sscanf(line, "%s%s%s%d%s%d%s%d%s%d%s%d%s%d%s", str, str, str, &(face[i].vi[0]), str, &(face[i].vi[1]), str, &(face[i].vi[2]), str, &num, str, &num, str, &num, str);
					}
				}
				fgets(line, 256, fp);	// 닫는 중괄호 처리.

				fgets(line, 256, fp);					// MESH_NUMVERTEX -> 입력에서 지워야 함. (버퍼 비우기)
				sscanf(line, "%s", str);

				// MESH_NUMCVERTEX를 무시하고 MESH_NORMALS 입력.
				if (strcmp(str, "*MESH_NUMCVERTEX") == 0)
				{
					fgets(line, 256, fp);
					sscanf(line, "%s", str);
				}

				if (strcmp(str, "*MESH_NORMALS") == 0)
				{
					for (int i = 0; i < nFace; i++)
					{
						float* nF = normal[i].norFace;
						float* nV1 = normal[i].norV1;
						float* nV2 = normal[i].norV2;
						float* nV3 = normal[i].norV3;

						fgets(line, 256, fp);			// MESH_FACENORMAL
						sscanf(line, "%s%d%f%f%f", str, &num, nF, nF + 1, nF + 2);

						fgets(line, 256, fp);			// MESH_VERTEXNOUMAL
						sscanf(line, "%s%d%f%f%f", str, &num, nV1, nV1 + 1, nV1 + 2);
						fgets(line, 256, fp);
						sscanf(line, "%s%d%f%f%f", str, &num, nV2, nV2 + 1, nV2 + 2);
						fgets(line, 256, fp);
						sscanf(line, "%s%d%f%f%f", str, &num, nV3, nV3 + 1, nV3 + 2);
					}
				}

				break;
			}
		}

		wprintf(L"\"%s\" has been loaded.\n", fileName);

		fclose(fp);
	}

	void draw(float scale = 1.0f, bool bCoord = false)
	{
		glBegin(GL_TRIANGLES);

		for (int i = 0; i < nFace; i++)
		{
			Vertex* v1 = &vertex[face[i].vi[0]];
			Vertex* v2 = &vertex[face[i].vi[1]];
			Vertex* v3 = &vertex[face[i].vi[2]];

			glNormal3fv(normal[i].norV1);
			glVertex3f(v1->x / scale, v1->z / scale, v1->y / scale);
			glNormal3fv(normal[i].norV2);
			glVertex3f(v2->x / scale, v2->z / scale, v2->y / scale);
			glNormal3fv(normal[i].norV3);
			glVertex3f(v3->x / scale, v3->z / scale, v3->y / scale);
		}

		glEnd();

		if (bCoord)
			drawCoord(1);
	}

	void drawColor4fv(float color[4], float scale = 1.0f, bool bCoord = false)
	{
		setColor(color[0], color[1], color[2], color[3]);

		draw(scale, bCoord);
	}

	void setColor(float red, float green, float blue, float alpha)
	{
		float color[4] = { red, green, blue, alpha };

		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
	}
};

#endif

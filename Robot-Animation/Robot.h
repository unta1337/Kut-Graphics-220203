#ifndef __ROBOT_H
#define __ROBOT_H

#include <iostream>

#include "Mesh.h"

#include "IAnimation.h"

class Robot
{
	struct RobotParts;
	RobotParts* parts;

	struct { float head[4]; float body[4]; float arm[4]; float leg[4]; } colors =
	{
		{ 1.0f, 1.0f, 1.0f, 0.0f },
		{ 1.0f, 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 1.0f, 0.0f },
		{ 0.5f, 0.5f, 0.5f, 0.0f }
	};

	float scale;
	bool showCoord;

	IAnimation* animation;

public:
	Robot();
	Robot(float scale, bool showCoord);
	~Robot();

	void draw();
	void clear();

	void setScale(float scale);
	void setShowCoord(bool showCoord);
	void setAnimation(IAnimation* animation);
};

#endif

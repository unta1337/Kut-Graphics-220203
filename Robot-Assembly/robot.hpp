#ifndef __ROBOT_H
#define __ROBOT_H

#include <iostream>

#include "mesh.hpp"

class Robot
{
	struct RobotParts
	{
		Mesh head;
		Mesh body;
		Mesh leftArm;
		Mesh leftHand;
		Mesh rightArm;
		Mesh rightHand;
		Mesh leftLeg;
		Mesh leftFoot;
		Mesh rightLeg;
		Mesh rightFoot;

		Mesh& operator[](int index)
		{
			return *(&head + index);
		}
	};

	RobotParts parts;
	struct { float head[4]; float body[4]; float arm[4]; float leg[4]; } colors =
	{
		{ 1.0f, 1.0f, 1.0f, 0.0f },
		{ 1.0f, 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 1.0f, 0.0f },
		{ 0.5f, 0.5f, 0.5f, 0.0f }
	};

	float scale = 100;
	bool showCoord = true;

public:
	Robot()
	{
		std::cout << "Loading ASE files...\n";
		parts.head.readASE(L"head.ase");
		parts.body.readASE(L"body.ase");
		parts.leftArm.readASE(L"left_arm.ase");
		parts.leftHand.readASE(L"left_hand.ase");
		parts.rightArm.readASE(L"right_arm.ase");
		parts.rightHand.readASE(L"right_hand.ase");
		parts.leftLeg.readASE(L"left_leg.ase");
		parts.leftFoot.readASE(L"left_foot.ase");
		parts.rightLeg.readASE(L"right_leg.ase");
		parts.rightFoot.readASE(L"right_foot.ase");
	}

	Robot(float scale, bool showCoord) : Robot()
	{
		this->scale = scale;
		this->showCoord = showCoord;
	}

	void draw()
	{
		parts.body.drawColor4fv(colors.body, scale, showCoord);

		// 머리 그리기.
		glPushMatrix();
			glTranslated(0, 0.44, 0);
			parts.head.drawColor4fv(colors.head, scale, false);

			// 왼쪽 팔 그리기.
			glPushMatrix();
				glTranslated(0.17, -0.34, 0);
				parts.leftArm.drawColor4fv(colors.arm, scale, false);

				// 왼쪽 손 그리기.
				glPushMatrix();
					glTranslated(-0.037, -0.28, 0);
					parts.leftHand.drawColor4fv(colors.arm, scale, false);
				glPopMatrix();
			glPopMatrix();

			// 오른쪽 팔 그리기.
			glPushMatrix();
				glTranslated(-0.17, -0.34, 0);
				parts.rightArm.drawColor4fv(colors.arm, scale, false);

				// 오른쪽 손 그리기.
				glPushMatrix();
					glTranslated(0.037, -0.28, 0);
					parts.rightHand.drawColor4fv(colors.arm, scale, false);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();

		// 왼쪽 다리 그리기.
		glPushMatrix();
			glTranslated(0.06, -0.29, 0);
			parts.leftLeg.drawColor4fv(colors.leg, scale, false);

			// 왼쪽 발 그리기.
			glPushMatrix();
				glTranslated(-0.037, -0.31, -0.07);
				parts.leftFoot.drawColor4fv(colors.leg, scale, false);
			glPopMatrix();
		glPopMatrix();

		// 오른쪽 다리 그리기.
		glPushMatrix();
			glTranslated(-0.06, -0.29, 0);
			parts.rightLeg.drawColor4fv(colors.leg, scale, false);

			// 오른쪽 발 그리기.
			glPushMatrix();
				glTranslated(0.037, -0.31, -0.07);
				parts.rightFoot.drawColor4fv(colors.leg, scale, false);
			glPopMatrix();
		glPopMatrix();
	}

	void clear()
	{
		for (int i = 0; i < 10; i++)
			parts[i].clearASE();
	}

	void setScale(float scale)
	{
		this->scale = scale;
	}

	void setShowCoord(bool showCoord)
	{
		this->showCoord = showCoord;
	}
};

#endif

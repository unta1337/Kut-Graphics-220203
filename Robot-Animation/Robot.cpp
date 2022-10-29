#include "Robot.h"

struct Robot::RobotParts
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

Robot::Robot()
{
	parts = new RobotParts();

	scale = 100;
	showCoord = true;

	animation = nullptr;

	std::cout << "Loading ASE files...\n";
	parts->head.readASE(L"head.ase");
	parts->body.readASE(L"body.ase");
	parts->leftArm.readASE(L"left_arm.ase");
	parts->leftHand.readASE(L"left_hand.ase");
	parts->rightArm.readASE(L"right_arm.ase");
	parts->rightHand.readASE(L"right_hand.ase");
	parts->leftLeg.readASE(L"left_leg.ase");
	parts->leftFoot.readASE(L"left_foot.ase");
	parts->rightLeg.readASE(L"right_leg.ase");
	parts->rightFoot.readASE(L"right_foot.ase");
}

Robot::Robot(float scale, bool showCoord) : Robot()
{
	this->scale = scale;
	this->showCoord = showCoord;
}

Robot::~Robot()
{
	delete parts;
}

void Robot::draw()
{
	if (showCoord)
		drawCoord(1);

	// ���� �׸���.
	glPushMatrix();
		animation->animateBody();
		parts->body.drawColor4fv(colors.body, scale, false);

		// �Ӹ� �׸���.
		glPushMatrix();
			animation->animateHead();
			parts->head.drawColor4fv(colors.head, scale, false);
		glPopMatrix();

		// ���� �� �׸���.
		glPushMatrix();
			animation->animateLeftArm();
			parts->leftArm.drawColor4fv(colors.arm, scale, false);

			// ���� �� �׸���.
			glPushMatrix();
			animation->animateLeftHand();
				parts->leftHand.drawColor4fv(colors.arm, scale, false);
			glPopMatrix();
		glPopMatrix();

		// ������ �� �׸���.
		glPushMatrix();
			animation->animateRightArm();
			parts->rightArm.drawColor4fv(colors.arm, scale, false);

			// ������ �� �׸���.
			glPushMatrix();
				animation->animateRightHand();
				parts->rightHand.drawColor4fv(colors.arm, scale, false);
			glPopMatrix();
		glPopMatrix();

		// ���� �ٸ� �׸���.
		glPushMatrix();
			animation->animateLeftLeg();
			parts->leftLeg.drawColor4fv(colors.leg, scale, false);

			// ���� �� �׸���.
			glPushMatrix();
				animation->animateLeftFoot();
				parts->leftFoot.drawColor4fv(colors.leg, scale, false);
			glPopMatrix();
		glPopMatrix();

		// ������ �ٸ� �׸���.
		glPushMatrix();
			animation->animateRightLeg();
			parts->rightLeg.drawColor4fv(colors.leg, scale, false);

			// ������ �� �׸���.
			glPushMatrix();
				animation->animateRightFoot();
				parts->rightFoot.drawColor4fv(colors.leg, scale, false);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	glutPostRedisplay();
}

void Robot::clear()
{
	for (int i = 0; i < 10; i++)
		(*parts)[i].clearASE();
}

void Robot::setScale(float scale)
{
	this->scale = scale;
}

void Robot::setShowCoord(bool showCoord)
{
	this->showCoord = showCoord;
}

void Robot::setAnimation(IAnimation* animation)
{
	this->animation = animation;
}

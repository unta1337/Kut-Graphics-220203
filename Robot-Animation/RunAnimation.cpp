#include "RunAnimation.h"

RunAnimation::RunAnimation()
{
}

RunAnimation::~RunAnimation()
{
}

void RunAnimation::animateHead()
{
	DefaultAnimation::animateHead();

	glRotatef(-20 * cosDeg(gTime), 0, 1, 0);
}

void RunAnimation::animateBody()
{
	DefaultAnimation::animateBody();

	glTranslated(0.0, 0.08 * sinDeg(gTime), 0);
	glRotatef(-sinDeg(2 * gTime) - 10, 1, 0, 0);
	glRotatef(-sinDeg(gTime), 0, 1, 0);
}

void RunAnimation::animateLeftArm()
{
	DefaultAnimation::animateLeftArm();

	glRotatef(65 * cosDeg(gTime), 1, 0, 0);
}

void RunAnimation::animateLeftHand()
{
	DefaultAnimation::animateLeftHand();

	glRotatef(45 * cosDeg(gTime) + 70, 1, 0, 0);
	glRotatef(20 * sinDeg(gTime) + 20, 0, 1, 0);
}

void RunAnimation::animateRightArm()
{
	DefaultAnimation::animateRightArm();

	glRotatef(-65 * cosDeg(gTime), 1, 0, 0);
}

void RunAnimation::animateRightHand()
{
	DefaultAnimation::animateRightHand();

	glRotatef(-45 * cosDeg(gTime) + 70, 1, 0, 0);
	glRotatef(-20 * sinDeg(gTime) - 20, 0, 1, 0);
}

void RunAnimation::animateLeftLeg()
{
	DefaultAnimation::animateLeftLeg();

	glRotatef(-45 * cosDeg(gTime) + 35, 1, 0, 0);
}

void RunAnimation::animateLeftFoot()
{
	DefaultAnimation::animateLeftFoot();

	glRotatef(-50 * sinDeg(gTime) - 55, 1, 0, 0);
	glRotatef(-gTime / 20.0, 0, -1, 0);
}

void RunAnimation::animateRightLeg()
{
	DefaultAnimation::animateRightLeg();

	glRotatef(45 * cosDeg(gTime) + 35, 1, 0, 0);
}

void RunAnimation::animateRightFoot()
{
	DefaultAnimation::animateRightFoot();

	glRotatef(50 * sinDeg(gTime) - 55, 1, 0, 0);
	glRotatef(gTime / 20.0, 0, -1, 0);
}

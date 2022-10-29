#include "DefaultAnimation.h"

DefaultAnimation::DefaultAnimation()
{
}

DefaultAnimation::~DefaultAnimation()
{
}

void DefaultAnimation::animateHead()
{
	glTranslated(0, 0.45, 0);
}

void DefaultAnimation::animateBody()
{
}

void DefaultAnimation::animateLeftArm()
{
	glTranslated(0.13, 0.33, 0);
}

void DefaultAnimation::animateLeftHand()
{
	glTranslated(0.05, -0.23, 0);
}

void DefaultAnimation::animateRightArm()
{
	glTranslated(-0.13, 0.33, 0);
}

void DefaultAnimation::animateRightHand()
{
	glTranslated(-0.05, -0.23, 0);
}

void DefaultAnimation::animateLeftLeg()
{
	glTranslated(0.07, 0, 0);
}

void DefaultAnimation::animateLeftFoot()
{
	glTranslated(0, -0.28, 0);
}

void DefaultAnimation::animateRightLeg()
{
	glTranslated(-0.07, 0, 0);
}

void DefaultAnimation::animateRightFoot()
{
	glTranslated(0, -0.28, 0);
}

#include "Dab.h"

Dab::Dab()
{
}

Dab::~Dab()
{
}

void Dab::animateHead()
{
	DefaultAnimation::animateHead();

	glRotatef(-50 * abs(sinDeg(0.25 * gTime)), 1, 0, 0);
	glRotatef(50 * abs(sinDeg(0.25 * gTime)), 0, 1, 0);
}

void Dab::animateLeftArm()
{
	DefaultAnimation::animateLeftArm();

	glRotatef(120 * abs(sinDeg(0.25 * gTime)), 0, 0, 1);
	glRotatef(30 * abs(sinDeg(0.25 * gTime)), 1, 0, 0);
}

void Dab::animateRightArm()
{
	DefaultAnimation::animateRightArm();

	glRotatef(30 * abs(sinDeg(0.25 * gTime)), 1, 0, 0);
	glRotatef(-60 * abs(sinDeg(0.25 * gTime)), 0, 0, 1);
	glRotatef(20 * abs(sinDeg(0.25 * gTime)), 1, 0, 0);
}

void Dab::animateRightHand()
{
	DefaultAnimation::animateRightHand();

	glRotatef(120 * abs(sinDeg(0.25 * gTime)) , 1, 0, 0);
}

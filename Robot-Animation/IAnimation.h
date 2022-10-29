#ifndef __I_ANIMATION_H
#define __I_ANIMATION_H

#include "Util.h"

#include <glut.h>

class IAnimation
{
public:
	IAnimation();
	virtual ~IAnimation();

	virtual void animateHead() = 0;
	virtual void animateBody() = 0;
	virtual void animateLeftArm() = 0;
	virtual void animateLeftHand() = 0;
	virtual void animateRightArm() = 0;
	virtual void animateRightHand() = 0;
	virtual void animateLeftLeg() = 0;
	virtual void animateLeftFoot() = 0;
	virtual void animateRightLeg() = 0;
	virtual void animateRightFoot() = 0;
};

#endif

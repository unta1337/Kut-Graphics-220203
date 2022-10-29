#ifndef __RUN_ANIMATION_H
#define __RUN_ANIMATION_H

#include "DefaultAnimation.h"

extern int gTime;

class RunAnimation : public DefaultAnimation
{
public:
	RunAnimation();
	virtual ~RunAnimation();

	virtual void animateHead();
	virtual void animateBody();
	virtual void animateLeftArm();
	virtual void animateLeftHand();
	virtual void animateRightArm();
	virtual void animateRightHand();
	virtual void animateLeftLeg();
	virtual void animateLeftFoot();
	virtual void animateRightLeg();
	virtual void animateRightFoot();
};

#endif

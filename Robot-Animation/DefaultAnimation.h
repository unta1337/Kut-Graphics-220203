#ifndef __DEFAULT_ANIMATION
#define __DEFAULT_ANIMATION

#include "IAnimation.h"

class DefaultAnimation : public IAnimation
{
public:
	DefaultAnimation();
	virtual ~DefaultAnimation();

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

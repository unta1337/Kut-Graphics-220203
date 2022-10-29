// Ref: https://knowyourmeme.com/memes/the-dab

#ifndef __DAB_H
#define __DAB_H

#include "DefaultAnimation.h"

extern int gTime;

class Dab : public DefaultAnimation
{
public:
	Dab();
	virtual ~Dab();

	virtual void animateHead();
	virtual void animateLeftArm();
	virtual void animateRightArm();
	virtual void animateRightHand();
};

#endif

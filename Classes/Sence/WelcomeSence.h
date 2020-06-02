#ifndef _WelcomeSence_H_
#define _WelcomeSence_H_
#include "cocos2d.h"
using namespace cocos2d;
class WelcomeSence : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(WelcomeSence);
	void jumpStartSecen(float dt);
	void playTimi(float dt);
};
#endif // !_WelcomeSence_H_


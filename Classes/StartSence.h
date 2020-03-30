#ifndef __StartSence_H__
#define __StartSence_H__
#include "cocos2d.h"
using namespace cocos2d;

class StartSence : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	StartSence();
	~StartSence();

	void clickMenuSound();

	CREATE_FUNC(StartSence);
};

#endif // !__StartSence_H__




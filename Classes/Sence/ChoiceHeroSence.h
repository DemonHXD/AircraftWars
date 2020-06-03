#ifndef _ChoiceHeroSence_H_
#define _ChoiceHeroSence_H_
#include "cocos2d.h"
using namespace cocos2d;
class ChoiceHeroSence : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(ChoiceHeroSence);
};

#endif // !_ChoiceHeroSence_H_


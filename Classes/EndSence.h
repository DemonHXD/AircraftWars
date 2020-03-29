#ifndef __EndSence_H__
#define __EndSence_H__
#include "cocos2d.h"
using namespace cocos2d;
class EndSence : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(EndSence);
};

#endif // !__EndSence_H__




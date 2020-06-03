#ifndef _SelectMapSence_H_
#define _SelectMapSence_H_
#include "cocos2d.h"
using namespace cocos2d;
class SelectMapSence : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SelectMapSence);
};
#endif // !_SelectMapSence_H_




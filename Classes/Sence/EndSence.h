#ifndef __EndSence_H__
#define __EndSence_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"//UI头文件
using namespace cocos2d::ui;//UI命名空间
using namespace cocos2d;
class EndSence : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	CREATE_FUNC(EndSence);
private:
	TextAtlas* scoreText;
};

#endif // !__EndSence_H__




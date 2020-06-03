#ifndef __SettingLayer_H__
#define __SettingLayer_H__
#include "cocos2d.h"
using namespace cocos2d;
class SettingLayer : public Layer {
public:
	static SettingLayer* create();

	SettingLayer():onExit(nullptr){}

	virtual bool init() override;

	void initSoundEff();
	void initBGMusic();
	void runAct(Vec2 v1, Vec2 v2, CallFunc* callFunc = nullptr);
public:
	typedef std::function<void()> ccExitCallback;

	ccExitCallback onExit;//指向退出设置时要调用的函数
private:
	Node* root;
};
#endif



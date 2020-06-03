#ifndef __PauseLayer_H__
#define __PauseLayer_H__
#include "cocos2d.h"
using namespace cocos2d;
class GameSence;
class PauseLayer : public Layer{
public:
	PauseLayer(GameSence *gameSence);
	~PauseLayer();
	static PauseLayer* create(GameSence *gameSence);
	bool init() override;
	void runAct(Vec2 v1, Vec2 v2, CallFunc* callFunc = nullptr);
private:
	GameSence *gameSence;
	Size size;
};
#endif // !__PauseLayer_H__




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
private:
	GameSence *gameSence;
};
#endif // !__PauseLayer_H__




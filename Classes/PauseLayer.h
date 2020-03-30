#ifndef __PauseLayer_H__
#define __PauseLayer_H__
#include "cocos2d.h"
using namespace cocos2d;
class GameSenceManager;
class PauseLayer : public Layer{
public:
	PauseLayer(GameSenceManager *gameSenceManager);
	~PauseLayer();
	static PauseLayer* create(GameSenceManager *gameSenceManager);
	bool init() override;
	void clickMenuSound();
private:
	GameSenceManager *gameSenceManager;
};
#endif // !__PauseLayer_H__




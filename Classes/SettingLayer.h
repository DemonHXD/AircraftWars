#ifndef __SettingLayer_H__
#define __SettingLayer_H__
#include "cocos2d.h"
using namespace cocos2d;
class StartSence;
class SettingLayer : public Layer {
public:
	static SettingLayer* create(StartSence* startSence);

	SettingLayer(StartSence* startSence);
	~SettingLayer();

	virtual bool init() override;

	void initSoundEff();
	void initBGMusic();

private:
	StartSence* startSence;
	Sprite* openCloseSoundSp;
	Sprite* openCloseSoundEffSp;
};
#endif



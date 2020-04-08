#ifndef __SettingLayer_H__
#define __SettingLayer_H__
#include "cocos2d.h"
using namespace cocos2d;
class SettingLayer : public Layer {
public:
	static SettingLayer* create();

	SettingLayer();
	~SettingLayer();

	virtual bool init() override;

	void initSoundEff();
	void initBGMusic();
private:
	Node* root;
};
#endif



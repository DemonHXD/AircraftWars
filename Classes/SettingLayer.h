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

	//CREATE_FUNC(SettingLayer);


private:
	StartSence* startSence;
};
#endif



#ifndef __Porp_H__
#define __Porp_H__
#include "cocos2d.h"
using namespace cocos2d;
/*
	定义道具类型:
		Shield:防护罩
		WingAir：僚机
*/
enum PorpType { Shield = 1, WingAir };
class Porp : public Sprite {
public:
	static Porp* create(PorpType type);
	bool init();
	Porp(PorpType type);
	//开启僚机时显示的文字动画
	void WingAircraftTextAct();
	~Porp();
	void setLive(bool isLive) {
		this->isLive = isLive;
	}
	//道具飞行调度器
	void update(float dt);
	PorpType getType() {
		return type;
	}
private:
	//速度
	int speed;
	//飞行标志 1往右边飞  -1左边飞
	int flyFlag;
	bool isLive;
	Size size;
	PorpType type;
};

#endif // !__Porp_H__




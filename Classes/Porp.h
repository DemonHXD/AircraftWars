#ifndef __Porp_H__
#define __Porp_H__
#include "cocos2d.h"
using namespace cocos2d;

class Porp : public Sprite {
public:
	static Porp* create();
	bool init();
	Porp();
	~Porp();
	void setLive(bool isLive) {
		this->isLive = isLive;
	}
	//道具飞行调度器
	void update(float dt);
private:
	//速度
	int speed;
	//飞行标志 1往右边飞  -1左边飞
	int flyFlag;
	bool isLive;
	Size size;
};

#endif // !__Porp_H__




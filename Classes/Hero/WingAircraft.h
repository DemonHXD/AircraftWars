#ifndef __WingAircraft_H_
#define __WingAircraft_H_
#include "cocos2d.h"
#include "Bullet/Bullet.h"

using namespace cocos2d;
//僚机
class WingAircraft : public Sprite {
public :
	static WingAircraft* create();
	bool init();
	void shoot(float dt);
	//僚机飞行动画
	void flyAct();
	WingAircraft();
	~WingAircraft();
private:
	int speed;
};
#endif // !__WingAircraft_H_




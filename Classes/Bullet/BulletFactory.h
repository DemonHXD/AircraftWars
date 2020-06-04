#pragma once
#include "Bullet.h"
//#include "cocos2d.h"
class BulletFactory {
public:
	static Bullet* createBullet(BulletType bulletType, Vec2 dir);//创建子弹
};


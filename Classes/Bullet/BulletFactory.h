#pragma once
#include "Bullet.h"
class BulletFactory {
public:
	static Bullet* createBullet(BulletType bulletType);//创建子弹
};


#include "BulletFactory.h"
#include "BulletManager.h"
Bullet* BulletFactory::createBullet(BulletType bulletType) {
	//1.查找死亡池中是否存在符合条件的子弹
	Bullet* bt = BulletManager::getInstance()->findInDeath(bulletType);
	//2.如果为空，重新创建子弹 
	if (nullptr == bt) {
		bt = Bullet::create(bulletType);
		bt->retain();//引用计数 + 1
	}

	switch (bulletType) {
	case HeroBullet:
		BulletManager::getInstance()->addHeroBullet(bt);
		break;
	case EnemyBullet:
		BulletManager::getInstance()->addEnemyBullet(bt);
		break;
	case WingAircraftBullet:
		BulletManager::getInstance()->addWingAircraftBullet(bt);
		break;
	}
	return bt;
}
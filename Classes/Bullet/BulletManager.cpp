#include "BulletManager.h"
#include "Bullet.h"
//静态变量要在类外做初始化，不然会报错
BulletManager* BulletManager::pInstance = nullptr;

BulletManager::BulletManager() {

}

BulletManager::~BulletManager() {

	//对所有在生存池中和死亡池中的子弹引用计数-1
	for (auto bullet : heroLives) {
		bullet->release();
	}	
	for (auto bullet : heroDeaths) {
		bullet->release();
	}	
	
	for (auto bullet : enemyLives) {
		bullet->release();
	}	
	for (auto bullet : enemyDeaths) {
		bullet->release();
	}	
	
	for (auto bullet : wingAircraftLives) {
		bullet->release();
	}	
	for (auto bullet : wingAircraftDeaths) {
		bullet->release();
	}

	pInstance = nullptr;

	clearList();
}

void BulletManager::addHeroBullet(Bullet* bullet) {
	//将子弹添加到链表末尾
	heroLives.push_back(bullet);
	//bullet->retain();
}

//添加子弹:添加到生存池中
void BulletManager::addEnemyBullet(Bullet* bullet) {
	//将子弹添加到链表末尾
	enemyLives.push_back(bullet);
	//bullet->retain();
}

void BulletManager::addWingAircraftBullet(Bullet* bullet) {
	wingAircraftLives.push_back(bullet);
}

void BulletManager::addSkillBullet(Bullet* bullet) {
	skillLives.push_back(bullet);
}

//回收子弹，添加到死亡池中
void BulletManager::collection(Bullet* bullet, BulletType bulletType) {
	switch (bulletType) {
	case HeroBullet:
		//将英雄子弹从生存池中移除
		heroLives.remove(bullet);
		//将英雄子弹添加到死亡池中
		heroDeaths.push_back(bullet);
		break;
	case EnemyBullet:
		//将敌机子弹从生存池中移除
		enemyLives.remove(bullet);
		//将敌机子弹添加到死亡池中
		enemyDeaths.push_back(bullet);
		break;
	case WingAircraftBullet:
		//将僚机子弹从生存池中移除
		wingAircraftLives.remove(bullet);
		//将僚机子弹添加到死亡池中
		wingAircraftDeaths.push_back(bullet);
		break;
	case SkillBullet:
		skillLives.remove(bullet);
		skillDeaths.push_back(bullet);
	}
	//将子弹从父节点上移除
	bullet->removeFromParent();
}

void BulletManager::clearList() {
	heroLives.clear();
	heroDeaths.clear();

	enemyLives.clear();
	enemyDeaths.clear();

	wingAircraftLives.clear();
	wingAircraftDeaths.clear();

	skillLives.clear();
	skillDeaths.clear();
}

Bullet* BulletManager::findInDeath(BulletType bulletType) {
	Bullet* bt = nullptr;
	switch (bulletType) {
	case HeroBullet:
		//遍历英雄死亡池中的子弹
		for (Bullet* bullet : heroDeaths) {
			if (bullet->getBulletType() == bulletType) {
				bt = bullet;
				heroDeaths.remove(bt);//从死亡池中移出
				break;
			}
		}
		break;
	case EnemyBullet:
		//遍历敌机死亡池中的子弹
		for (Bullet* bullet : enemyDeaths) {
			if (bullet->getBulletType() == bulletType) {
				bt = bullet;
				enemyDeaths.remove(bt);//从死亡池中移出
				break;
			}
		}
		break;
	case WingAircraftBullet:
		//遍历僚机死亡池中的子弹
		for (Bullet* bullet : wingAircraftDeaths) {
			if (bullet->getBulletType() == bulletType) {
				bt = bullet;
				wingAircraftDeaths.remove(bt);//从死亡池中移出
				break;
			}
		}
		break;
	case SkillBullet :
		//遍历僚机死亡池中的子弹
		for (Bullet* bullet : skillDeaths) {
			if (bullet->getBulletType() == bulletType) {
				bt = bullet;
				skillDeaths.remove(bt);//从死亡池中移出
				break;
			}
		}
		break;
	}
	return bt;
}

/*
	销毁所有敌机子弹
*/
void BulletManager::destEnemyBullets() {
	for (Bullet* bullet : enemyLives) {
		bullet->setLive(false);
	}
}

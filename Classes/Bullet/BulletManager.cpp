#include "BulletManager.h"
#include "Bullet.h"
//静态变量要在类外做初始化，不然会报错
BulletManager* BulletManager::pInstance = nullptr;

BulletManager::BulletManager() {

}

BulletManager::~BulletManager() {
	pInstance = nullptr;
}

void BulletManager::addHeroBullet(Bullet* bullet) {
	//将子弹添加到链表末尾
	heroBulletList.push_back(bullet);
}

void BulletManager::addEnemyBullet(Bullet* bullet) {
	//将子弹添加到链表末尾
	enemyBulletList.push_back(bullet);
}

void BulletManager::collection(Bullet* bullet, int type) {
	if (type == 1) {
		//将子弹从链表中移除
		heroBulletList.remove(bullet);
	} else {
		//将子弹从链表中移除
		enemyBulletList.remove(bullet);
	}
	//将子弹从父节点上移除
	bullet->removeFromParent();
}

void BulletManager::clearList() {
	heroBulletList.clear();
	enemyBulletList.clear();
}


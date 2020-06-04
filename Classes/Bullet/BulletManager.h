#pragma once
#include <list>
#include "Bullet.h"
using namespace std;
//class Bullet;//声明Bullet类
//子弹管理类
//1.单例
//2.使用链表来管理子弹
//3.添加子弹到链表中
//4.回收子弹：从链表中移除该子弹
class BulletManager
{
public:
	
	void addEnemyBullet(Bullet* bullet);//参数：要添加英雄子弹的指针
	void addHeroBullet(Bullet* bullet);//参数：要添加敌机子弹的指针
	void addWingAircraftBullet(Bullet* bullet);//参数：要添加僚机子弹的指针
	void collection(Bullet* bullet, BulletType bulletType);//参数：要回收英雄子弹的指针
	Bullet* findInDeath(BulletType bulletType);//查找子弹
	static BulletManager* getInstance() {
		if (nullptr == pInstance)
		{
			pInstance = new BulletManager();
		}
		return pInstance;
	}
	~BulletManager();
	void clearList();	//清空集合
	void trackEnemy(Vec2 dir);//追踪英雄
	void destEnemyBullets();//销毁所有敌机子弹
public :
	//英雄的子弹
	list<Bullet*> heroLives;//生存池
	list<Bullet*> heroDeaths;//死亡池

	//敌机的子弹
	list<Bullet*> enemyLives;//生存池
	list<Bullet*> enemyDeaths;//死亡池

	//僚机的子弹
	list<Bullet*> wingAircraftLives;//生存池
	list<Bullet*> wingAircraftDeaths;//死亡池
private:
	static BulletManager* pInstance;
	BulletManager();

};


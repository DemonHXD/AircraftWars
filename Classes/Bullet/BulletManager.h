#pragma once
#include <list>
using namespace std;
class Bullet;//声明Bullet类
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
	void collection(Bullet* bullet, int type);//参数：要回收英雄子弹的指针
	static BulletManager* getInstance() {
		if (nullptr == pInstance)
		{
			pInstance = new BulletManager();
		}
		return pInstance;
	}
	~BulletManager();
	void clearList();	//清空集合
public :
	//英雄的子弹
	list<Bullet*> heroBulletList;
	//敌机的子弹
	list<Bullet*> enemyBulletList;
private:
	static BulletManager* pInstance;
	BulletManager();

};


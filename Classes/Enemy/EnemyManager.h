#pragma once
#include <list>
using namespace std;
//敌机管理类
//1.单例
//2.使用链表来管理敌机
//3.添加敌机到链表中
//4.回收敌机：从链表中移除该敌机
class Enemy;//声明Enemy类
class EnemyManager
{
public:
	void addEnemy(Enemy* enemy);//参数：要添加敌机的指针
	void collection(Enemy* enemy);//参数：要回收敌机的指针
	static EnemyManager* getInstance() {
		if (nullptr == pInstance)
		{
			pInstance = new EnemyManager();
		}
		return pInstance;
	}
	~EnemyManager();
	void clearList();	//清空集合
public:
	list<Enemy*> enemyList;
private:
	static EnemyManager* pInstance;
	EnemyManager();

};




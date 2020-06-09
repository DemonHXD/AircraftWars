#pragma once
#include "cocos2d.h"
using namespace cocos2d;

//定义子弹类型:枚举(整数  4个字节)
enum BulletType { HeroBullet = 1, EnemyBullet, WingAircraftBullet, SkillBullet};

class Bullet : public Sprite
{
private:
	//Vec2 heroPos;
	int atk;//攻击力
	bool isLive;//是否存活
	float speed;
	int randEnemyBullet;
	//1为英雄子弹 -1为敌机子弹 2为僚机子弹
	//int type;
	BulletType bulletType;
	Vec2 dir;//子弹的方向 上dir = (0,1) 右dir = (1,0) 斜dir = (sin30,cos30);
	//Vec2 heroDir;
public:
	//friend class BulletManager;
	Bullet(BulletType bulletType, Vec2 dir = Vec2(0, 1));//带参构造函数
	~Bullet();
	static Bullet* create(BulletType bulletType, Vec2 dir);
	void onEnter() override;
	//void onExit() override;
	bool init();
	void update(float dt) override;//自定义子弹调度器
	void bulletRun();
	//发射子弹的声音
	void shootSound();
	//void setDeroDir
	void setDir(Vec2 dir) {//设置方向
		this->dir = dir;
	}
	//Vec2 getDir() {
	//	return dir;
	//}
	void setLive(bool isLive)//设置isLive
	{
		this->isLive = isLive;
	}
	bool getLive()//获取isLive
	{
		return isLive;
	}
	void setAtk(int atk) {
		this->atk = atk;
	}
	int getAtk() {
		return atk;
	}
	int getBulletType() const {
		return bulletType;
	}
};


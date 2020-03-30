#pragma once
#include "cocos2d.h"
using namespace cocos2d;

//定义子弹类型:枚举(整数  4个字节)
enum BulletType { Missile, Rocket, OrdinaryBullet, SnallLaser, BigLaser, };

class Bullet : public Sprite
{
private:
	int atk;//攻击力
	bool isLive;//是否存活
	float speed;
	//1为英雄子弹 -1为敌机子弹 2为僚机子弹
	int type;
	BulletType bulletType;
	Vec2 dir = Vec2(0,1);//子弹的方向 上dir = (0,1) 右dir = (1,0) 斜dir = (sin30,cos30);
public:
	Bullet(int type,BulletType bulletType = OrdinaryBullet);//带参构造函数
	~Bullet();
	static Bullet* create(int type, BulletType bulletType);
	bool init();
	void update(float dt) override;
	void bulletRun();
	//发射子弹的声音
	void shootSound(int type);
	void setDir(Vec2 dir) {//设置方向
		this->dir = dir;
	}
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
};


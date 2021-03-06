﻿#pragma once
#include "cocos2d.h"
#include "Bullet/Bullet.h"
#include "WingAircraft.h"
using namespace cocos2d;

enum Plane { Type1 = 0, Type2, Type3, Type4};
class Hero : public Sprite
{
private:
	float speed;
	bool bulletFlag = true;
	int bulletCount;//子弹数量
	//初始化生命值为3
	int liveCount;
	bool isChange = false;
	int type;			//默认是小飞机
	//static Hero* instance;
	static int count;
	int blinkDefCount = 0;//计算闪烁次数
	int blinkWingAirCount = 0;//计算闪烁次数
	bool isShield;//是否拥有防御罩
	bool isWingAir;//是否拥有僚机
	bool isMove;
	bool isLocking;//是否锁定攻击
	int lockingCount;
	bool isStackEnemy;//是否自动追踪敌机攻击
	WingAircraft *leftWa = nullptr, *rightWa = nullptr;
	Sprite* defenseSP;
	int bulletAngle[4] = {0};
public:
	~Hero();
	Hero();
	static Hero* create();
	void hit();//英雄被击中
	void setStackEnemy(bool _isStackEnemy) {
		isStackEnemy = _isStackEnemy;
	}
	bool getStackEnemy() {
		return isStackEnemy;
	}
	int getLiveCount() {
		return liveCount;
	}
	void setShield(bool isOpenDefense) {
		isShield = isOpenDefense;
	}
	bool getShield() {
		return isShield;
	}	
	void setWingAir(bool isOpenWingAir) {
		isWingAir = isOpenWingAir;
	}
	bool getWingAir() {
		return isWingAir;
	}
	void setMove(bool move) {
		isMove = move;
	}
	int getBulletCount()const {
		return bulletCount;
	}
	void setLocking(bool locking) {
		isLocking = locking;
	}
	//根据飞机类型来创建英雄
	static Hero* create(const int herotype);
	void update(float dt) override;
	bool init();
	void heroAction();
	//static Hero* getInstance();
	//是否开启英雄无敌防护罩
	void isOpenDefense(bool isShield);
	//是否创建僚机
	void isCreateWingAir(bool isWingAir);
	//防护罩的调度器
	void defenseUpdate(float dt);
	void extendDefenseTime();//延长防护罩时间
	void extendWingAirTime();//延长僚机时间
	//僚机的调度器
	void WingAirUpdate(float dt);
	//英雄死亡
	void die();
	//射击方法
	void shoot(float dt);	
	void move(Vec2 dir);

	//子弹升级
	void bulletUp();

	//开启僚机
	void createWingAircraft();

	//增加生命值
	inline void incHealth() {
		liveCount++;
	}

	//更改英雄外观
	void setAppearance(int type, int exp);

	void createShotgun(float angle);

	//设置触摸是否开启
	void setTouchEnabled(bool enabled);

	//当触摸开始时，要执行的函数
	bool onTouchBegan(Touch* touch, Event* event);

	//当触摸移动时，要执行的函数
	void onTouchMoved(Touch* touch, Event* event);

	void lockingFeiDan(Vec2 enemyPos, bool &isShoot);//锁定导弹调度器

public:
	typedef std::function<void(cocos2d::Vec2)> ccHeroMovedCallback;
	ccHeroMovedCallback onHeroMoved;//当摇杆拖动时
};


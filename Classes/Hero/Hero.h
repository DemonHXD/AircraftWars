#pragma once
#include "cocos2d.h"
#include "Bullet/Bullet.h"
#include "WingAircraft.h"
using namespace cocos2d;

enum Plane { SmallPlane, MidPlane, BigPlane };
class Hero : public Sprite
{
private:
	float speed;
	//初始化生命值为3
	int liveCount;
	bool isChange = false;
	static int type;				//默认是小飞机
	//static Hero* instance;
	static int count;
	int blinkCount = 0;//计算闪烁次数
	bool isShield;//是否拥有防御罩
	bool isMove;
	WingAircraft *leftWa, *rightWa;
public:
	~Hero();
	Hero();
	static Hero* create();
	void hit();//英雄被击中
	int getLiveCount() {
		return liveCount;
	}
	void setShield(bool isOpenDefense) {
		isShield = isOpenDefense;
	}
	bool getShield() {
		return isShield;
	}
	void setMove(bool move) {
		isMove = move;
	}
	//根据飞机类型来创建英雄
	static Hero* create(const int herotype);
	void update(float dt) override;
	bool init();
	void heroAction();
	//static Hero* getInstance();
	//是否开启英雄无敌防护罩
	void isOpenDefense(bool isShield);
	//防护罩的调度器
	void defenseUpdate(float dt);
	//英雄死亡
	void die();
	//射击方法
	void shoot(float dt);		

	//开启僚机
	void createWingAircraft();

	void createShotgun(float angle, BulletType type);

	//设置触摸是否开启
	void setTouchEnabled(bool enabled);

	//当触摸开始时，要执行的函数
	bool onTouchBegan(Touch* touch, Event* event);

	//当触摸移动时，要执行的函数
	void onTouchMoved(Touch* touch, Event* event);
};


#include "WingAircraft.h"
#include "Bullet/Bullet.h"
#include "Bullet/BulletManager.h"
#include "Bullet/BulletFactory.h"
#include "Hero.h"
WingAircraft::WingAircraft():speed(30){

}

WingAircraft::~WingAircraft() {

}

WingAircraft* WingAircraft::create() {
	WingAircraft* ret = new (std::nothrow) WingAircraft();
	if (ret && ret->init()) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool WingAircraft::init() {
	if (!Sprite::initWithFile("image/hero/wingaircraft_1.png")) {
		return false;
	}

	//开启射击调度器
	schedule(schedule_selector(WingAircraft::shoot), 0.6, -1, 0);

	//开启飞行动画
	flyAct();
	return true;
}

/*
	僚机飞行动画
*/
void WingAircraft::flyAct() {
	//创建图片收集者
	Animation* animation = Animation::create();
	char fileName[40];
	for (int i = 1; i <= 2; i++) {
		sprintf_s(fileName, "image/hero/wingaircraft_%d.png", i);
		animation->addSpriteFrameWithFile(fileName);
	}
	//间隔时间
	animation->setDelayPerUnit(0.5f);
	animation->setLoops(-1);
	//开启动画
	Animate* animate = Animate::create(animation);
	this->runAction(animate);
}

/*
	 僚机射击调度器
*/
void WingAircraft::shoot(float dt) {
	//创建子弹
	Bullet* bullet = BulletFactory::createBullet(WingAircraftBullet, Vec2(0, 1));
	float h = getContentSize().height / 2;
	//设置子弹的位置:英雄的坐标 + 英雄图片高度的一半
	bullet->setPosition(getPosition() + Vec2(0, 0));
	_parent->addChild(bullet);

	//将子弹添加到管理类中
	BulletManager::getInstance()->addWingAircraftBullet(bullet);
}


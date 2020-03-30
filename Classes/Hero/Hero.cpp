#include "Hero.h"
#include "Bullet/Bullet.h"
#include "Bullet/BulletManager.h"

const float PI = 3.1415926;//圆周率
bool flag = true;
#define HERO 1
Hero::Hero() :speed(80), isShield(false), liveCount(3), isMove(true){

}
Hero::~Hero() {

}

int Hero::type= SmallPlane;

int Hero::count = 0;

//Hero* Hero::getInstance() {
//	if (!instance) {
//		instance = new(std::nothrow) Hero();
//	}
//	return instance;
//}

/*
	英雄创建
*/
Hero* Hero::create() {
	Hero* ret = new(std::nothrow) Hero();
	if (ret && ret->init()) {
		ret->autorelease();
		return ret;
	}
	delete ret;
	ret = nullptr;
	return ret;
}

Hero* Hero::create(const int herotype) {
	type = herotype;
	return create();
}

/*
	初始化
*/
bool Hero::init() {
	std::string path = "";
	switch (type) {
	case SmallPlane:
		path = "image/hero/hero0_1.png";
		break;
	case MidPlane:
		path = "image/hero/hero1_1.png";
		break;
	}
	if (!Sprite::initWithFile(path)) {
		return false;
	}
	//开启英雄飞行动画
	heroAction();

	//开启默认调度器
	//scheduleUpdate();

	//开启英雄射击自定义调度器
	schedule(schedule_selector(Hero::shoot), 0.3, -1, 0);

	//开启触摸监听
	setTouchEnabled(true);
	return true;
}

void Hero::update(float dt) {

}

/*
	主机飞行动画
*/
void Hero::heroAction() {
	//创建图片收集者
	Animation* animation = Animation::create();
	char fileName[40];
	switch (type) {
	case SmallPlane:
		for (int i = 1; i <= 6; i++) {
			//std::string path = "image/hero/" + smallPlaneName[i];
			sprintf_s(fileName, "image/hero/hero0_%d.png", i);
			animation->addSpriteFrameWithFile(fileName);
		}
		break;
	case MidPlane:
		for (int i = 1; i <= 2; i++) {
			//std::string path = "image/hero/" + midPlaneName[i];
			sprintf_s(fileName, "image/hero/hero1_%d.png", i);
			animation->addSpriteFrameWithFile(fileName);
		}
		break;
	}
	//间隔时间
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(-1);
	//开启动画
	Animate* animate = Animate::create(animation);
	animate->setTag(15);
	this->runAction(animate);
}

void Hero::setTouchEnabled(bool enabled) {
	/*监听器：
			触摸监听器(单点触摸/多点触摸)
				EventListenerTouchOneByOne			单点触摸
				EventListenerTouchAllAtOnce			多点触摸
			键盘监听器:EventListenerKeyboard
			鼠标监听器:EventListenerMouse
			加速监听器:EventListenerAcceleration
			自定义监听器:EventListenerCustom
		EventListener是所有监听器的父类
		1.创建监听器
		2.创建监听对应的阶段函数
		3.将监听器添加到分发器(分发消息)中
	*/
	//1.创建单点触摸监听器
	EventListenerTouchOneByOne* eventListener = EventListenerTouchOneByOne::create();
	//2.创建监听对于的阶段函数
	/*触摸分为四个阶段:
		触摸开始(return true表示执行后面三个阶段   return false 表示不执行后面三个阶段)
		触摸移动
		触摸结束
		触摸取消
	*/
	//绑定事件
	//CC_CALLBACK_形参的个数(类名::函数名，调用的对象)
	eventListener->onTouchBegan = CC_CALLBACK_2(Hero::onTouchBegan, this);
	eventListener->onTouchMoved = CC_CALLBACK_2(Hero::onTouchMoved, this);
	//将监听器添加到事件分发中
	//第一种方式：通过渲染优先级添加:1.监听器  2.节点  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
	
	//第二种方式：通过固定优先级:1.监听器  2.优先级(值越小，越先监听事件)
	//_eventDispatcher->addEventListenerWithFixedPriority(eventListener,1);

	//设置是否吞噬触摸：默认不吞噬(是否将触摸事件传递给下一个监听者)
	//eventListener->setSwallowTouches(false);
}

/*
	当触摸开始时，要执行的函数
*/
bool Hero::onTouchBegan(Touch* touch, Event* event) {

	if (isShield == true) {
		isMove = true;
	}

	//获取触摸点:屏幕坐标系(左上角为原点，y轴向下)
	//需要屏幕转OpenGL坐标系
	Vec2 touchPoint = touch->getLocation();

	//Rect:1.containsPoint(点) 是否包含某个点
	//	   2.intersectsRect(矩形) 判断两个矩形是否相交
	//getBoundingBox是获取原始矩形的宽高，如果对其做了缩放，获取到的矩形还是原始矩形
	bool isContain = getBoundingBox().containsPoint(touchPoint);

	//判断触摸的那个点是否在英雄的身上
	if (isContain) {
		return true;
	}
	return false;
}

/*
	当触摸移动时，要执行的函数
*/
void Hero::onTouchMoved(Touch* touch, Event* event) {
	if(isMove) {
		//获取当前移动的值
		Vec2 pos = touch->getLocation();

		//判断飞机的位置应该在(0-480)之间
		if (pos.x >= 480) {
			pos = Vec2(480, pos.y);
		} else if (pos.x <= 0) {
			pos = Vec2(0, pos.y);
		}

		//判断飞机的y轴可移动的值应该在(0-800)之间
		if (pos.y >= (800 - getContentSize().height / 2)) {
			pos = Vec2(pos.x, (800 - getContentSize().height / 2));
		} else if (pos.y <= getContentSize().height / 4) {
			pos = Vec2(pos.x, getContentSize().height / 4);
		}

		//判断是否创建了僚机
		if (leftWa != nullptr && rightWa != nullptr) {
			leftWa->setPosition(Vec2(getPosition().x - 60, getPosition().y + 30));
			rightWa->setPosition(Vec2(getPosition().x + 60, getPosition().y + 30));
		}

		setPosition(pos);
	}
	
}

/*
	设置散弹效果
*/
void Hero::createShotgun(float angle, BulletType type) {
	//创建子弹
	Bullet* bullet = Bullet::create(HERO,type);
	bullet->shootSound(1);
	float h = getContentSize().height / 2;
	//设置子弹的位置:英雄的坐标 + 英雄图片高度的一半
	bullet->setPosition(getPosition() + Vec2(0, 0));
	if (angle != 0) {
		//设置子弹旋转
		bullet->setRotation(angle);
		// 设置子弹的方向
		bullet->setDir(Vec2(sin(angle / 180 * PI), cos(angle / 180 * PI)));
	}
	//将子弹添加到层上  两个方法都行
	//getParent()->addChild(bullet);
	_parent->addChild(bullet);

	//将子弹添加到管理类中
	BulletManager::getInstance()->addHeroBullet(bullet);
}

void Hero::shoot(float dt) {
	//始终用小导弹攻击
	createShotgun(0, Rocket);
	//if (flag)
	//{
	//	
	//	float angle[7] = { -15,-10,-5,0,5,10,15 };
	//	for (int i = 0; i < 7; i++)
	//	{
	//		createShotgun(angle[i], OrdinaryBullet);
	//	}
	//}
	//else {
	//	createShotgun(0, Rocket);
	//}

	//count++;

	//if (count == 10)
	//{
	//	flag = !flag;
	//	count = 0;
	//}
}

/*
	是否开启英雄无敌防护罩
	默认不开启
	isOpen:是否开启
	time：开启时间
*/
void Hero::isOpenDefense(bool isShield) {
	this->isShield = isShield;
	if (isShield) {
		Sprite* defenseSP = Sprite::create("image/ui/trans.png");
		defenseSP->setAnchorPoint(Vec2(0, 0));
		defenseSP->setPosition(Vec2(-23, 0));
		defenseSP->setScale(0.5f);
		defenseSP->setTag(25);
		this->addChild(defenseSP);
		schedule(schedule_selector(Hero::defenseUpdate), 1, 5, 5);
	}
}

/*
	防护罩的调度器
*/
void Hero::defenseUpdate(float dt) {
	Sprite* defenseSP = (Sprite*)this->getChildByTag(25);
	Blink * blink = Blink::create(1.0f, 2);
	defenseSP->runAction(blink);
	blinkCount++;
	if (blinkCount == 5) {
		defenseSP->removeFromParent();
		defenseSP = nullptr;
		blinkCount = 0;
		this->isShield = false;
		unschedule(schedule_selector(Hero::defenseUpdate));
		//return;
	}
}

/*
	英雄被击中
*/
void Hero::hit() {
	liveCount--;
	//分发敌机死亡的消息
	_eventDispatcher->dispatchCustomEvent("onHeroDeath", this);
	if (liveCount != 0) {
		isMove = false;
		//设置英雄初始位置
		Size size = Director::getInstance()->getVisibleSize();
		this->setPosition(Vec2(size.width / 2, this->getContentSize().height / 2));
		//判断是否创建了僚机
		if (leftWa != nullptr && rightWa != nullptr) {
			leftWa->setPosition(Vec2(getPosition().x - 60, getPosition().y + 30));
			rightWa->setPosition(Vec2(getPosition().x + 60, getPosition().y + 30));
		}
		//开启防护罩
		isOpenDefense(true);
	}
}

/*
	英雄死亡
*/
void Hero::die() {
	stopActionByTag(15);
	//创建图片收集者
	Animation* ani = Animation::create();
	char filename[50];
	for (int i = 1; i <= 6; i++) {
		sprintf_s(filename, "image/blast/blast_2_%d.png", i);
		ani->addSpriteFrameWithFile(filename);
	}
	//间隔时间
	ani->setDelayPerUnit(0.2f);
	//开启动画
	Animate* animate = Animate::create(ani);

	CallFunc* callFuncAct = CallFunc::create([this]() {
		this->removeFromParent();
	});

	//创建序列动作
	Sequence* seqAct = Sequence::create(animate, callFuncAct, nullptr);

	this->runAction(seqAct);
}

/*
	开启僚机
*/
void Hero::createWingAircraft() {
	//创建左僚机
	leftWa = WingAircraft::create();
	leftWa->setPosition(Vec2(getPosition().x - 60, getPosition().y + 30));
	leftWa->setScale(0.7f);
	_parent->addChild(leftWa, 5);

	//创建右僚机
	rightWa = WingAircraft::create();
	rightWa->setPosition(Vec2(getPosition().x + 60, getPosition().y + 30));
	rightWa->setScale(0.7f);
	_parent->addChild(rightWa, 5);

	schedule(schedule_selector(Hero::WingAirUpdate), 1, 5, 15);
}

/*
	僚机的调度器
	僚机开启时间为30s
	最后五秒会闪烁消失
*/
void Hero::WingAirUpdate(float dt) {
	Blink* blink1 = Blink::create(1.0f, 2);
	Blink* blink2 = Blink::create(1.0f, 2);
	//if (leftWa != nullptr && rightWa != nullptr) {
	//	leftWa->runAction(blink);
	//	rightWa->runAction(blink);
	//}
	leftWa->runAction(blink1);
	rightWa->runAction(blink2);
	blinkCount++;
	//count++;
	if (blinkCount == 5) {
		leftWa->removeFromParent();
		rightWa->removeFromParent();
		leftWa = nullptr;
		rightWa = nullptr;
		blinkCount = 0;
		unschedule(schedule_selector(Hero::WingAirUpdate));
	}
}
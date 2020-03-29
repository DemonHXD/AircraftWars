#include "Porp.h"
#include "PorpManager.h"

Porp::Porp():flyFlag(1), speed(45), isLive(true){
	size = Director::getInstance()->getVisibleSize();
}

Porp::~Porp() {

}

Porp* Porp::create() {
	Porp* ret = new(std::nothrow) Porp();
	if (ret && ret->init()) {
		ret->autorelease();
		return ret;
	}
	delete ret;
	ret = nullptr;
	return nullptr;
}

bool Porp::init() {
	if (!Sprite::initWithFile("image/ui/prop.png")) {
		return false;
	}
	//使用默认调度器使道具飞行
	scheduleUpdate();
	return true;
}

/*
	道具飞行调度器
*/
void Porp::update(float dt) {
	if (!isLive) {
		PorpManager::getInstance()->collection(this);
		return;
	}
	float porp_x = getPositionX();
	float porp_y = getPositionY();
	Vec2 pos;
	if (flyFlag == 1 && porp_x < size.width - getContentSize().width / 2) {
		pos = Vec2(porp_x + speed * dt, porp_y - speed * dt);
	}else if (flyFlag == 1 && porp_x >= size.width - getContentSize().width / 2) {
		pos = Vec2(size.width - getContentSize().width / 2, porp_y - speed * dt);
		flyFlag = -1;
	}	
	
	if (flyFlag == -1 && porp_x > getContentSize().width / 2) {
		pos = Vec2(porp_x - speed * dt, porp_y - speed * dt);
		
	}else if (flyFlag == -1 && porp_x <=getContentSize().width / 2) {
		pos = Vec2(getContentSize().width / 2, porp_y - speed * dt);
		flyFlag = 1;
	}
	setPosition(pos);
}


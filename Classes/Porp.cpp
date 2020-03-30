#include "Porp.h"
#include "PorpManager.h"

Porp::Porp(PorpType type):flyFlag(1), speed(45), isLive(true), type(type){
	size = Director::getInstance()->getVisibleSize();
}

Porp::~Porp() {

}

Porp* Porp::create(PorpType type) {
	Porp* ret = new(std::nothrow) Porp(type);
	if (ret && ret->init()) {
		ret->autorelease();
		return ret;
	}
	delete ret;
	ret = nullptr;
	return nullptr;
}

bool Porp::init() {
	char filename[40];
	sprintf_s(filename, "image/ui/prop_%d.png", type);
	if (!Sprite::initWithFile(filename)) {
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

/*
	开启僚机时显示的文字动画
*/
void Porp::WingAircraftTextAct() {
	Size size = Director::getInstance()->getVisibleSize();
	Sprite* textSp = Sprite::create("image/ui/WingAircraftText.png");
	textSp->setPosition(Vec2(size.width / 2, size.height / 2));
	_parent->addChild(textSp);
	FadeIn* textIn = FadeIn::create(1);
	FadeOut* textOut = FadeOut::create(3.0f);
	ScaleTo* textScale = ScaleTo::create(2, 2, 2);
	//创建序列动作
	Sequence* seqAct = Sequence::create(textIn, textScale, textOut, nullptr);
	textSp->runAction(seqAct);
}


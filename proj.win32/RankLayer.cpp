#include "RankLayer.h"
#include "ui/CocosGUI.h"
#include "AudioUtil.h"
using namespace cocos2d::ui;
RankLayer::RankLayer(Layer *sence):sence(sence){

}

RankLayer::~RankLayer() {

}

RankLayer* RankLayer::create(Layer *sence) {
	RankLayer *ret = new (std::nothrow)RankLayer(sence);
	if (ret && ret->init()) {
		ret->autorelease();
		return ret;
	} else {
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool RankLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	//设置吞噬触摸
	EventListenerTouchOneByOne* eventListener = EventListenerTouchOneByOne::create();
	eventListener->onTouchBegan = [this](Touch *touch, Event *event) {
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
	//设置吞噬触摸
	eventListener->setSwallowTouches(true);
	Size size = Director::getInstance()->getVisibleSize();

	//排行榜背景精灵
	Sprite* rankSp = Sprite::create("image/ui/rankSp.png");
	rankSp->setPosition(Vec2(size.width / 2 , size.height / 2));
	rankSp->setScale(0.7f);
	this->addChild(rankSp, 5);

	//创建继续游戏按钮
	Button* resumeBtn = Button::create("image/ui/continueGame_normal.png", "image/ui/continueGame_pressed.png");
	resumeBtn->setPosition(Vec2(size.width / 2, size.height / 2 - 120));
	resumeBtn->setScale(0.7f);
	this->addChild(resumeBtn, 5);
	resumeBtn->addClickEventListener([this, eventListener](Ref*) {
		eventListener->setSwallowTouches(false);
		AudioUtil::getInstence()->buttonClickSound();
		//移出暂停层
		removeAllChildren();
		//恢复背景音乐
		AudioUtil::getInstence()->audioResume();
		//游戏继续
		Director::getInstance()->resume();
	});

	//返回主菜单
	Button* backMenuBtn = Button::create("image/ui/backMenu_normal.png", "image/ui/backMenu_pressed.png");
	backMenuBtn->setPosition(Vec2(size.width / 2, size.height / 2 - 120));
	backMenuBtn->setScale(0.7f);
	this->addChild(backMenuBtn, 5);

	//if () {

	//}
	return true;
}
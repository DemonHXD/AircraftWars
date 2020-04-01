#include "PauseLayer.h"
#include "GameSenceManager.h"
#include "ui/CocosGUI.h"
#include "StartSence.h"
#include "EndSence.h"
#include "cocos2d.h"
#include "AudioUtil.h"
using namespace cocos2d;
using namespace cocos2d::ui;//UI命名空间

PauseLayer::PauseLayer(GameSenceManager *gameSenceManager):gameSenceManager(gameSenceManager){

}
PauseLayer::~PauseLayer() {

}

PauseLayer* PauseLayer::create(GameSenceManager *gameSenceManager) {
	PauseLayer *ret = new (std::nothrow)PauseLayer(gameSenceManager);
	if (ret && ret->init()) {
		ret->autorelease();
		return ret;
	} else {
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}
bool PauseLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	//创建触摸监听器，吞噬触摸
	//1.创建单点触摸监听器
	EventListenerTouchOneByOne* eventListener = EventListenerTouchOneByOne::create();
	eventListener->onTouchBegan = [this](Touch *touch, Event *event) {
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
	//设置吞噬触摸
	eventListener->setSwallowTouches(true);

	Size size = Director::getInstance()->getVisibleSize();
	//暂停层的初始化：创建继续游戏按钮/重新开始洗按钮/结束游戏按钮
	//创建背景
	Sprite* bg = Sprite::create("image/ui/pauseBG.png");
	bg->setPosition(Vec2(size.width / 2,size.height / 2 + 10));
	addChild(bg,5);
	//_parent
	//创建继续游戏按钮
	Button* resumeBtn = Button::create("image/ui/continueGame_normal.png", "image/ui/continueGame_pressed.png");
	resumeBtn->setPosition(Vec2(size.width / 2, size.height / 2 + 80));
	resumeBtn->setScale(0.7f);
	this->addChild(resumeBtn, 5);
	//获取父节点的暂停按钮
	Button* pauseBtn = (Button*)gameSenceManager->getChildByTag(2);
	//获取父节点的背景音乐ID
	int bgmID = gameSenceManager->getBgmID();
	//获取父节点的英雄
	resumeBtn->addClickEventListener([this, pauseBtn, eventListener, bgmID](Ref*) {
		eventListener->setSwallowTouches(false);
		AudioUtil::getInstence()->buttonClickSound();
		//移出暂停层
		removeAllChildren();
		//恢复背景音乐
		AudioUtil::getInstence()->audioResume();
		//显示暂停按钮
		pauseBtn->setVisible(true);
		//游戏继续
		Director::getInstance()->resume();
	});

	//创建重新开始游戏按钮
	Button* repateBtn = Button::create("image/ui/rePlay_normal.png", "image/ui/rePlay_pressed.png");
	repateBtn->setPosition(Vec2(size.width / 2, size.height / 2 + 20));
	repateBtn->setScale(0.7f);
	this->addChild(repateBtn, 5);
	repateBtn->addClickEventListener([this](Ref*) {
		AudioUtil::getInstence()->buttonClickSound();
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(GameSenceManager::createScene());
	});

	//创建结束游戏按钮
	Button* finishBtn = Button::create("image/ui/finishGame_normal.png", "image/ui/finishGame_pressed.png.png");
	finishBtn->setPosition(Vec2(size.width / 2, size.height / 2 - 40));
	finishBtn->setScale(0.7f);
	this->addChild(finishBtn, 5);
	finishBtn->addClickEventListener([this](Ref*) {
		AudioUtil::getInstence()->buttonClickSound();
		Director::getInstance()->resume();
		//切换场景(当前场景被销毁，新场景被创建)
		Director::getInstance()->replaceScene(EndSence::createScene());
	});

	//创建回到主界面按钮
	Button* backMenuBtn = Button::create("image/ui/backMenu_normal.png", "image/ui/backMenu_pressed.png");
	backMenuBtn->setPosition(Vec2(size.width / 2, size.height / 2 - 100));
	backMenuBtn->setScale(0.7f);
	this->addChild(backMenuBtn, 5);
	backMenuBtn->addClickEventListener([this](Ref*) {
		AudioUtil::getInstence()->buttonClickSound();
		Director::getInstance()->resume();
		//切换场景(当前场景被销毁，新场景被创建)
		Director::getInstance()->replaceScene(StartSence::createScene());
	});
	return true;
}
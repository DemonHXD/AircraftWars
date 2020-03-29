#include "SettingLayer.h"
#include "StartSence.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
SettingLayer* SettingLayer::create(StartSence* startSence) {
	SettingLayer *ret = new (std::nothrow)SettingLayer(startSence);
	if (ret && ret->init()) {
		ret->autorelease();
		return ret;
	} else {
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

SettingLayer::SettingLayer(StartSence* startSence):startSence(startSence) {

}
SettingLayer::~SettingLayer() {

}

bool SettingLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	Size size = Director::getInstance()->getVisibleSize();

	//背景
	Sprite* bgSp = Sprite::create("image/ui/setting_bg.png");
	bgSp->setPosition(Vec2(size.width / 2, size.height / 2 + 80));
	this->addChild(bgSp, 0);

	//关闭按钮
	Button* closeBtn = Button::create("image/ui/close_normal.png", "image/ui/close_pressed.png");
	closeBtn->setPosition(Vec2(size.width / 2 + bgSp->getContentSize().width / 2 - 20
		, size.height / 2 + bgSp->getContentSize().height / 2 + 10));
	this->addChild(closeBtn, 1);
	Button* startBtn = (Button*)startSence->getChildByTag(1);
	Button* settingBtn = (Button*)startSence->getChildByTag(2);
	Button* helpBtn = (Button*)startSence->getChildByTag(3);
	Button* aboutBtn = (Button*)startSence->getChildByTag(4);
	closeBtn->addClickEventListener([this, startBtn, settingBtn, helpBtn, aboutBtn](Ref*) {
		//移出暂停层
		removeAllChildren();

		//显示开始游戏按钮
		startBtn->setVisible(true);

		//显示设置按钮
		settingBtn->setVisible(true);

		//显示帮助按钮
		helpBtn->setVisible(true);

		//显示关于我们按钮
		aboutBtn->setVisible(true);
	});

	//开启或关闭声音精灵
	Sprite* openCloseSoundSp = Sprite::create("image/ui/open_close_sound.png");
	openCloseSoundSp->setPosition(Vec2(size.width / 2 - 60,size.height / 2 + 80));
	//openCloseSoundSp->setScale(0.7f);
	this->addChild(openCloseSoundSp, 1);

	//开启或关闭音效精灵
	Sprite* openCloseSoundEffSp = Sprite::create("image/ui/open_close_sound_eff.png");
	openCloseSoundEffSp->setPosition(Vec2(size.width / 2 - 60,size.height / 2));
	//openCloseSoundEffSp->setScale(0.7f);
	this->addChild(openCloseSoundEffSp, 1);

	//声音按钮
	Button* soundBtn = Button::create("image/ui/soundOn.png");
	soundBtn->setPosition(Vec2(size.width / 2 + openCloseSoundSp->getContentSize().width - 90, 
		size.height / 2 + 80));
	this->addChild(soundBtn, 1);

	//音效按钮
	Button* soundEffBtn = Button::create("image/ui/musicOn.png");
	soundEffBtn->setPosition(Vec2(size.width / 2 + openCloseSoundEffSp->getContentSize().width - 90,
		size.height / 2));
	this->addChild(soundEffBtn, 1);
	return true;
}
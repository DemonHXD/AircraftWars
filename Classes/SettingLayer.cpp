#include "SettingLayer.h"
#include "StartSence.h"
#include "ui/CocosGUI.h"
#include "AudioUtil.h"
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
		AudioUtil::getInstence()->buttonClickSound();
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
	openCloseSoundSp = Sprite::create("image/ui/open_close_sound.png");
	openCloseSoundSp->setPosition(Vec2(size.width / 2 - 60, size.height / 2 + 80));
	this->addChild(openCloseSoundSp, 1);

	//开启或关闭音效精灵
	openCloseSoundEffSp = Sprite::create("image/ui/open_close_sound_eff.png");
	openCloseSoundEffSp->setPosition(Vec2(size.width / 2 - 60, size.height / 2));
	this->addChild(openCloseSoundEffSp, 1);

	initSoundEff();
	initBGMusic();

	return true;
}

/*
	初始化音效
*/
void SettingLayer::initSoundEff() {
	Size size = Director::getInstance()->getVisibleSize();
	//获取本地的状态信息
	bool effState = UserDefault::getInstance()->getBoolForKey("effSound");
	//音效开按钮
	Button* soundEffOpenBtn = Button::create("image/ui/musicOn.png");
	soundEffOpenBtn->setPosition(Vec2(size.width / 2 + openCloseSoundEffSp->getContentSize().width - 90,
		size.height / 2));
	this->addChild(soundEffOpenBtn, 1);

	//音效关按钮
	Button* soundEffCloseBtn = Button::create("image/ui/musicOff.png");
	soundEffCloseBtn->setPosition(Vec2(size.width / 2 + openCloseSoundEffSp->getContentSize().width - 90,
		size.height / 2));
	this->addChild(soundEffCloseBtn, 1);
	//默认是开启音效
	if (effState) {
		soundEffOpenBtn->setVisible(true);
		soundEffCloseBtn->setVisible(false);
	} else {
		soundEffOpenBtn->setVisible(false);
		soundEffCloseBtn->setVisible(true);
	}

	//关闭音效按钮事件
	soundEffOpenBtn->addClickEventListener([this, soundEffOpenBtn, soundEffCloseBtn](Ref*) {
		AudioUtil::getInstence()->buttonClickSound();
		//隐藏开始音效按钮
		soundEffOpenBtn->setVisible(false);
		//显示关闭音效按钮
		soundEffCloseBtn->setVisible(true);
		//关闭所有音效
		AudioUtil::getInstence()->setEffAudioState(false);
		//保存音效关信息到本地
		UserDefault::getInstance()->setBoolForKey("effSound", false);
	});

	//开启音效按钮事件
	soundEffCloseBtn->addClickEventListener([this, soundEffCloseBtn, soundEffOpenBtn](Ref*) {
		AudioUtil::getInstence()->buttonClickSound();
		//显示开始音效按钮
		soundEffOpenBtn->setVisible(true);
		//隐藏关闭音效按钮
		soundEffCloseBtn->setVisible(false);
		//开启所有音效
		AudioUtil::getInstence()->setEffAudioState(true);
		//保存音效开信息到本地
		UserDefault::getInstance()->setBoolForKey("effSound", true);
	});
}

/*
	初始化背景音乐
*/
void SettingLayer::initBGMusic() {
	Size size = Director::getInstance()->getVisibleSize();
	//获取本地的状态信息
	bool bgmState = UserDefault::getInstance()->getBoolForKey("bgmSound");
	//背景音乐开按钮
	Button* soundOpenBtn = Button::create("image/ui/soundOn.png");
	soundOpenBtn->setPosition(Vec2(size.width / 2 + openCloseSoundSp->getContentSize().width - 90,
		size.height / 2 + 80));
	this->addChild(soundOpenBtn, 1);
	
	//背景音乐关按钮
	Button* soundCloseBtn = Button::create("image/ui/soundOff.png");
	soundCloseBtn->setPosition(Vec2(size.width / 2 + openCloseSoundSp->getContentSize().width - 90,
		size.height / 2 + 80));
	soundCloseBtn->setVisible(false);
	this->addChild(soundCloseBtn, 1);

	if (bgmState) {
		soundOpenBtn->setVisible(true);
		soundCloseBtn->setVisible(false);
	} else {
		soundOpenBtn->setVisible(false);
		soundCloseBtn->setVisible(true);
	}

	//关闭背景音乐事件
	soundOpenBtn->addClickEventListener([this, soundOpenBtn, soundCloseBtn](Ref*) {
		AudioUtil::getInstence()->buttonClickSound();
		//隐藏开始背景音乐按钮
		soundOpenBtn->setVisible(false);
		//显示关闭背景音乐按钮
		soundCloseBtn->setVisible(true);
		//关闭背景音乐
		AudioUtil::getInstence()->setBgmAudioState(false);
		//保存背景音乐关信息到本地
		UserDefault::getInstance()->setBoolForKey("bgmSound", false);
	});

	//开启背景音乐事件
	soundCloseBtn->addClickEventListener([this, soundCloseBtn, soundOpenBtn](Ref*) {
		AudioUtil::getInstence()->buttonClickSound();
		//显示开始背景音乐按钮
		soundOpenBtn->setVisible(true);
		//隐藏关闭背景音乐按钮
		soundCloseBtn->setVisible(false);
		//开启背景音乐
		AudioUtil::getInstence()->setBgmAudioState(true);
		//保存背景音乐开信息到本地
		UserDefault::getInstance()->setBoolForKey("bgmSound", true);
	});
}
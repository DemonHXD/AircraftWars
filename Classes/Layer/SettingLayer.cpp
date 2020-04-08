#include "SettingLayer.h"
#include "Sence/StartSence.h"
#include "ui/CocosGUI.h"
#include "Utils/AudioUtil.h"
#include "cocostudio/CocoStudio.h"
using namespace cocos2d::ui;
SettingLayer* SettingLayer::create() {
	SettingLayer *ret = new (std::nothrow)SettingLayer();
	if (ret && ret->init()) {
		ret->autorelease();
		return ret;
	} else {
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

SettingLayer::SettingLayer() {

}
SettingLayer::~SettingLayer() {
}

bool SettingLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	//加载cocostudio文件
	root = CSLoader::createNode("scenes/start/layers/SettingLayer.csb");
	this->addChild(root);

	//关闭按钮
	Button* closeMenuBtn = (Button*)root->getChildByTag(28);
	closeMenuBtn->addClickEventListener([this](Ref*) {
		AudioUtil::getInstence()->buttonClickSound();
		//移出暂停层
		removeAllChildren();
	});

	initSoundEff();
	initBGMusic();

	return true;
}

/*
	初始化音效
*/
void SettingLayer::initSoundEff() {
	//获取本地的状态信息
	bool effState = UserDefault::getInstance()->getBoolForKey("effSound");
	//音效开按钮
	Button* soundEffOpenBtn = (Button*)root->getChildByTag(26);
	
	//音效关按钮
	Button* soundEffCloseBtn = (Button*)root->getChildByTag(27);

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
		//关闭所有音效
		AudioUtil::getInstence()->setEffAudioState(false);
		AudioUtil::getInstence()->buttonClickSound();
		//隐藏开始音效按钮
		soundEffOpenBtn->setVisible(false);
		//显示关闭音效按钮
		soundEffCloseBtn->setVisible(true);
		//保存音效关信息到本地
		UserDefault::getInstance()->setBoolForKey("effSound", false);
	});

	//开启音效按钮事件
	soundEffCloseBtn->addClickEventListener([this, soundEffCloseBtn, soundEffOpenBtn](Ref*) {
		//开启所有音效
		AudioUtil::getInstence()->setEffAudioState(true);
		AudioUtil::getInstence()->buttonClickSound();
		//显示开始音效按钮
		soundEffOpenBtn->setVisible(true);
		//隐藏关闭音效按钮
		soundEffCloseBtn->setVisible(false);
		//保存音效开信息到本地
		UserDefault::getInstance()->setBoolForKey("effSound", true);
	});
}

/*
	初始化背景音乐
*/
void SettingLayer::initBGMusic() {
	//获取本地的状态信息
	bool bgmState = UserDefault::getInstance()->getBoolForKey("bgmSound");
	//背景音乐开按钮
	Button* soundOpenBtn = (Button*)root->getChildByTag(23);
	
	//背景音乐关按钮
	Button* soundCloseBtn = (Button*)root->getChildByTag(25);

	if (bgmState) {
		soundOpenBtn->setVisible(true);
		soundCloseBtn->setVisible(false);
	} else {
		soundOpenBtn->setVisible(false);
		soundCloseBtn->setVisible(true);
	}

	//关闭背景音乐事件
	soundOpenBtn->addClickEventListener([this, soundOpenBtn, soundCloseBtn](Ref*) {
		//关闭背景音乐
		AudioUtil::getInstence()->setBgmAudioState(false);
		AudioUtil::getInstence()->buttonClickSound();
		//隐藏开始背景音乐按钮
		soundOpenBtn->setVisible(false);
		//显示关闭背景音乐按钮
		soundCloseBtn->setVisible(true);
		//保存背景音乐关信息到本地
		UserDefault::getInstance()->setBoolForKey("bgmSound", false);
	});

	//开启背景音乐事件
	soundCloseBtn->addClickEventListener([this, soundCloseBtn, soundOpenBtn](Ref*) {
		//开启背景音乐
		AudioUtil::getInstence()->setBgmAudioState(true);
		AudioUtil::getInstence()->buttonClickSound();
		//显示开始背景音乐按钮
		soundOpenBtn->setVisible(true);
		//隐藏关闭背景音乐按钮
		soundCloseBtn->setVisible(false);
		//保存背景音乐开信息到本地
		UserDefault::getInstance()->setBoolForKey("bgmSound", true);
	});
}
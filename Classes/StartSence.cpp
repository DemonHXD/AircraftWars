#include "StartSence.h"
#include "GameSenceManager.h"
#include "SettingLayer.h"
#include "RankLayer.h"
#include "AudioUtil.h"
#include "ui/CocosGUI.h"//UI头文件
using namespace cocos2d::ui;//UI命名空间
USING_NS_CC;

Scene* StartSence::createScene() {
	auto scene = Scene::create();
	auto layer = StartSence::create();
	scene->addChild(layer);
	return scene;
}
StartSence::StartSence() {

}

StartSence::~StartSence() {
	//AudioEngine::end();
}

bool StartSence::init() {
	if (!Layer::init()) {
		return false;
	}
	//给当前类设置个tag
	this->setTag(101);
	Size size = Director::getInstance()->getVisibleSize();

	//创建背景
	Sprite* bg = Sprite::create("image/ui/start_bg.png");
	bg->setAnchorPoint(Vec2(0, 0));
	this->addChild(bg, 0);

	//开始游戏按钮
	Button* startGameBtn = Button::create("image/ui/startGame.png");
	startGameBtn->setPosition(Vec2(size.width / 2, size.height / 2 + 90));
	this->addChild(startGameBtn, 1);
	startGameBtn->setTag(1);
	startGameBtn->addClickEventListener([this](Ref*) {
		AudioUtil::getInstence()->buttonClickSound();
		//创建一个新场景
		Scene* GameSence = GameSenceManager::createScene();
		//设置一个界面切换的动作，0.5秒的跳动动作
		auto reSence = TransitionJumpZoom::create(0.5f, GameSence);
		
		Director::getInstance()->replaceScene(reSence);
	});

	//游戏设置按钮
	Button* settingBtn = Button::create("image/ui/setting.png");
	settingBtn->setPosition(Vec2(size.width / 2, size.height / 2 - 80));
	settingBtn->setScale(0.7f);
	settingBtn->setTag(2);
	this->addChild(settingBtn, 1);
	

	//游戏帮助按钮
	Button* helpBtn = Button::create("image/ui/help.png");
	helpBtn->setPosition(Vec2(size.width / 2, size.height / 2 - 140));
	helpBtn->setTag(3);
	helpBtn->setScale(0.7f);
	this->addChild(helpBtn, 1);

	//关于游戏按钮
	Button* aboutBtn = Button::create("image/ui/about.png");
	aboutBtn->setPosition(Vec2(size.width / 2, size.height / 2 - 200));
	aboutBtn->setTag(4);
	aboutBtn->setScale(0.7f);
	this->addChild(aboutBtn, 1);

	settingBtn->addClickEventListener([this, startGameBtn, settingBtn, helpBtn, aboutBtn](Ref*) {
		AudioUtil::getInstence()->buttonClickSound();
		//创建设置界面
		SettingLayer* settingLayer = SettingLayer::create(this);
		this->addChild(settingLayer);

		//隐藏开始游戏按钮
		startGameBtn->setVisible(false);

		//隐藏设置按钮
		settingBtn->setVisible(false);

		//隐藏帮助按钮
		helpBtn->setVisible(false);

		//隐藏关于我们按钮
		aboutBtn->setVisible(false);
	});

	//创建排行榜按钮
	Button* rankBtn = Button::create("image/ui/rank_normal.png", "image/ui/rank_pressed.png");
	rankBtn->setPosition(Vec2(size.width - 40, size.height - 70));
	rankBtn->setScale(0.7f);
	this->addChild(rankBtn, 10);
	rankBtn->addClickEventListener([this, startGameBtn, settingBtn, helpBtn, aboutBtn](Ref*) {
		AudioUtil::getInstence()->buttonClickSound();
		//创建设置界面
		RankLayer* rankLayer = RankLayer::create(this);
		this->addChild(rankLayer);

		//隐藏开始游戏按钮
		startGameBtn->setVisible(false);

		//隐藏设置按钮
		settingBtn->setVisible(false);

		//隐藏帮助按钮
		helpBtn->setVisible(false);

		//隐藏关于我们按钮
		aboutBtn->setVisible(false);
	});
	return true;
}

#include "StartSence.h"
#include "Sence/GameSence.h"
#include "Layer/SettingLayer.h"
#include "Layer/RankLayer.h"
#include "Utils/AudioUtil.h"
#include "cocostudio/CocoStudio.h"
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
	
	//加载cocostudio文件
	root = CSLoader::createNode("scenes/start/layers/StartLayer.csb");
	this->addChild(root);
	
	//给当前类设置个tag
	this->setTag(101);

	//开始游戏按钮
	Button* startGameBtn = dynamic_cast<Button*>(root->getChildByName("startGameBtn"));
	startGameBtn->addClickEventListener([this](Ref*) {
		AudioUtil::getInstence()->buttonClickSound();

		//健谈账号密码是否正确
		//TextField* TextField_Account = dynamic_cast<TextField*>(root->getChildByName("TextField_Account"));
		//TextField* TextField_password = dynamic_cast<TextField*>(root->getChildByName("TextField_password"));
		//std::string account = TextField_Account->getString();
		//std::string password = TextField_password->getString();

		//创建一个新场景
		Scene* GameSence = GameSence::createScene();
		//设置一个界面切换的动作，0.5秒的跳动动作
		auto reSence = TransitionJumpZoom::create(0.5f, GameSence);
		
		Director::getInstance()->replaceScene(reSence);
	});

	//游戏设置按钮
	Button* settingBtn = dynamic_cast<Button*>(root->getChildByName("settingBtn"));

	//游戏帮助按钮
	Button* helpBtn = dynamic_cast<Button*>(root->getChildByName("helpBtn"));

	//关于游戏按钮
	Button* aboutBtn = dynamic_cast<Button*>(root->getChildByName("aboutBtn"));

	//排行榜按钮
	Button* rankBtn = dynamic_cast<Button*>(root->getChildByName("rankBtn"));

	settingBtn->addClickEventListener([this, startGameBtn, settingBtn, helpBtn, aboutBtn](Ref*) {
		AudioUtil::getInstence()->buttonClickSound();
		//创建设置层
		SettingLayer* settingLayer = SettingLayer::create();
		this->addChild(settingLayer);

	});

	rankBtn->addClickEventListener([this](Ref*) {
		AudioUtil::getInstence()->buttonClickSound();
		//创建排行榜层
		RankLayer* rankLayer = RankLayer::create(this);
		this->addChild(rankLayer);
	});

	

	return true;
}

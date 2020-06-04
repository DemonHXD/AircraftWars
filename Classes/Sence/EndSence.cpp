#include "EndSence.h"
#include "GameSence.h"
#include "StartSence.h"
#include "cocostudio/CocoStudio.h"
#include "Utils/AudioUtil.h"
Scene* EndSence::createScene() {
	auto scene = Scene::create();
	auto layer = EndSence::create();
	scene->addChild(layer);
	return scene;
}

bool EndSence::init() {
	if (!Layer::init()) {
		return false;
	}
	//加载cocostudio文件
	Node* root = CSLoader::createNode("scenes/end/layers/EndLayer.csb");
	this->addChild(root);

	//返回菜单按钮
	Button* backStartGame = dynamic_cast<Button*>(root->getChildByName("backMenuBtn"));
	backStartGame->addClickEventListener([this](Ref*){
		AudioUtil::getInstence()->buttonClickSound();
		//创建一个新场景
		Scene* StartSence = StartSence::createScene();

		//设置一个界面切换的动作，0.5秒的跳动动作
		auto reSence = TransitionJumpZoom::create(0.5f, StartSence);
		Director::getInstance()->replaceScene(reSence);
		//播放背景音乐
		AudioUtil::getInstence()->playStartBgm();
	});

	//分数数字
	scoreText = dynamic_cast<TextAtlas*>(root->getChildByName("scoreNumberText"));

	//开启监听
	_eventDispatcher->addCustomEventListener("finalScoreDeath", [this](EventCustom* event) {
		GameSence* gameSence = (GameSence*)event->getUserData();
		scoreText->setString(std::to_string(gameSence->getScore()));
	});

	return true;
}

void EndSence::onEnter() {
	Layer::onEnter();
	
}

void EndSence::onExit() {
	Layer::onExit();
	//移出自定义监听器
	_eventDispatcher->removeCustomEventListeners("finalScoreDeath");
}
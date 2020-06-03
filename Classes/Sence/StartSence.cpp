#include "StartSence.h"
#include "Sence/GameSence.h"
#include "Sence/SelectMapSence.h"
#include "Layer/SettingLayer.h"
#include "Layer/RankLayer.h"
#include "Utils/AudioUtil.h"
#include <vector>
#include "cocostudio/CocoStudio.h"
#include "Ui/ChoiceItem.h"
#include "ui/CocosGUI.h"//UI头文件
#include "ChoiceHeroSence.h"
using namespace cocos2d::ui;//UI命名空间
using namespace cocostudio::timeline;
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
	
	////加载cocostudio文件
	//root = CSLoader::createNode("scenes/start/layers/choiceLayer.csb");
	//this->addChild(root);
	//

	////获取ScrollView子节点
	//ScrollView* scrollView = dynamic_cast<ScrollView*>(root->getChildByName("ScrollView"));
	////设置滚动区域的innerSize
	//scrollView->setInnerContainerSize(Size(400 * 8, 800));
	//std::vector<ChoiceItem*> items;
	////添加子控件，子控件必须作为scrollView的子节点
	//for (int i = 0; i < 8; i++) {
	//	ChoiceItem* item = ChoiceItem::create(i + 1);
	//	item->setPosition(Vec2(i * 400, 0));
	//	scrollView->addChild(item);
	//	items.push_back(item);
	//	//默认选中第一个
	//	if (i == 0) {
	//		item->setSelected(true);
	//	}
	//}

	//for each (ChoiceItem* item in items) {
	//	//给item添加监听事件
	//	item->addClickEventListener([item, items](Ref*) {
	//		for each (ChoiceItem* temp in items) {
	//			temp->setSelected(false);
	//		}
	//		//设置被点击选项选中
	//		item->setSelected(true);
	//	});
	//}

	//加载cocostudio文件
	root = CSLoader::createNode("scenes/start/layers/StartLayer.csb");
	this->addChild(root);
	
	//Node* startGame = root->getChildByName("startGame");
	
	//创建时间线动作 参数:动画节点的路径
	//ActionTimeline* action = CSLoader::createTimeline("scenes/start/ani/StartGame.csb");
	////指定播放哪些帧之间的动作 1.起始帧 2.结束帧(默认为最后一帧) 3.动作是否循环
	////action->gotoFrameAndPlay(0, 20, true);
	////播放某个动作 参数：1.动作的名字 2.是否循环
	//action->play("blink", true);
	////指定节点播放动作
	//startGame->runAction(action);

	//设置动作播放完的回调 1.动画的名字 2.回调函数(无返回值，无参的函数)
	//action->setAnimationEndCallFunc("fly", [hero]() {
	//	//log("Action::end");
	//	hero->removeFromParent();
	//});

	//设置某一帧的回调
	//1.先在cocostudio中设置帧事件(1.勾选开始记录动画(必须) 2.选中某一帧属性面板添加帧事件)
	//action->setFrameEventCallFunc([](Frame* frame) {
	//	EventFrame* event = dynamic_cast<EventFrame*>(frame);
	//	//判断当前帧事件的名字
	//	if (event->getEvent() == "Attack") {
	//		log("Attack");
	//	}
	//});

	//给当前类设置个tag
	this->setTag(101);

	//开始游戏按钮
	Button* startGameBtn = dynamic_cast<Button*>(root->getChildByName("startGameBtn"));
	startGameBtn->addClickEventListener([this](Ref*) {
		AudioUtil::getInstence()->buttonClickSound();

		//检查账号密码是否正确
		//TextField* TextField_Account = dynamic_cast<TextField*>(root->getChildByName("TextField_Account"));
		//TextField* TextField_password = dynamic_cast<TextField*>(root->getChildByName("TextField_password"));
		//std::string account = TextField_Account->getString();
		//std::string password = TextField_password->getString();

		//恢复背景音乐
		//AudioUtil::getInstence()->audioResume();

		//创建一个新场景
		Scene* selectMapSence = SelectMapSence::createScene();
		//设置一个界面切换的动作，0.5秒的跳动动作
		//auto reSence = TransitionJumpZoom::create(0.5f, GameSence);
		
		Director::getInstance()->replaceScene(selectMapSence);
	});

	//游戏设置按钮
	Button* settingBtn = dynamic_cast<Button*>(root->getChildByName("settingBtn"));

	//游戏帮助按钮
	Button* helpBtn = dynamic_cast<Button*>(root->getChildByName("choiceHeroBtn"));

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

	helpBtn->addClickEventListener([this](Ref*) {
		AudioUtil::getInstence()->buttonClickSound();
		//创建一个新场景
		Scene* choiceHeroSence = ChoiceHeroSence::createScene();
		//设置一个界面切换的动作，0.5秒的跳动动作
		//auto reSence = TransitionJumpZoom::create(0.5f, GameSence);

		Director::getInstance()->replaceScene(choiceHeroSence);
	});
	return true;
}

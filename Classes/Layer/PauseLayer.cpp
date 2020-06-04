#include "PauseLayer.h"
#include "Sence/GameSence.h"
#include "ui/CocosGUI.h"
#include "Sence/StartSence.h"
#include "Sence/EndSence.h"
#include "cocos2d.h"
#include "Utils/AudioUtil.h"
#include "cocostudio/CocoStudio.h"
using namespace cocos2d;
using namespace cocos2d::ui;//UI命名空间

PauseLayer::PauseLayer(GameSence *gameSence):gameSence(gameSence){

}
PauseLayer::~PauseLayer() {

}

PauseLayer* PauseLayer::create(GameSence *gameSence) {
	PauseLayer *ret = new (std::nothrow)PauseLayer(gameSence);
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
	size = Director::getInstance()->getVisibleSize();
	//创建触摸监听器，吞噬触摸
	//1.创建单点触摸监听器
	EventListenerTouchOneByOne* eventListener = EventListenerTouchOneByOne::create();
	eventListener->onTouchBegan = [this](Touch *touch, Event *event) {
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
	//设置吞噬触摸
	eventListener->setSwallowTouches(true);

	//加载cocostudio文件
	Node* root = CSLoader::createNode("scenes/game/layers/PauseLayer.csb");
	this->addChild(root);

	//创建游戏按钮
	Button* resumeBtn = dynamic_cast<Button*>(root->getChildByName("resumeBtn"));

	resumeBtn->addClickEventListener([this, eventListener](Ref*) {
		eventListener->setSwallowTouches(false);
		AudioUtil::getInstence()->buttonClickSound();
		//移出暂停层
		//removeAllChildren();
		Director::getInstance()->resume();//游戏继续
		AudioUtil::getInstence()->audioResume();//恢复背景音乐
		runAct(Vec2(0, 0), Vec2(0, size.width), CallFunc::create([this]() {
			removeAllChildren();//移出暂停层
		})
		);
	});

	//重新开始游戏按钮
	Button* repateBtn = dynamic_cast<Button*>(root->getChildByName("repateBtn"));
	repateBtn->addClickEventListener([this](Ref*) {
		AudioUtil::getInstence()->buttonClickSound();
		UserDefault::getInstance()->setIntegerForKey("score", gameSence->getScore());
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(GameSence::createScene());
	});

	//结束游戏按钮
	Button* finishBtn = dynamic_cast<Button*>(root->getChildByName("finishBtn"));
	finishBtn->addClickEventListener([this](Ref*) {
		AudioUtil::getInstence()->buttonClickSound();
		AudioUtil::getInstence()->audioPause();
		int maxScore = UserDefault::getInstance()->getIntegerForKey("score", 0);
		if (maxScore < gameSence->getScore()) {
			UserDefault::getInstance()->setIntegerForKey("score", gameSence->getScore());
		}
		Director::getInstance()->resume();
		//切换场景(当前场景被销毁，新场景被创建)
		Scene* endScene = EndSence::createScene();
		auto reSence = TransitionFade::create(0.5f, endScene);
		Director::getInstance()->replaceScene(reSence);
	});

	//回到主界面按钮
	Button* backMenuBtn = dynamic_cast<Button*>(root->getChildByName("backMuneBtn"));
	backMenuBtn->addClickEventListener([this](Ref*) {
		AudioUtil::getInstence()->buttonClickSound();
		UserDefault::getInstance()->setIntegerForKey("score", gameSence->getScore());
		Director::getInstance()->resume();
		//切换场景(当前场景被销毁，新场景被创建)
		Scene* startScene = StartSence::createScene();
		auto reSence = TransitionFade::create(0.5f, startScene);
		Director::getInstance()->replaceScene(reSence);
	});

	return true;
}

void PauseLayer::runAct(Vec2 v1, Vec2 v2, CallFunc* callFunc) {
	MoveBy* mb = MoveBy::create(0, v1);
	MoveTo* mt = MoveTo::create(0.3f, v2);
	Sequence* seqAct = Sequence::create(mb, mt, callFunc, nullptr);
	this->runAction(seqAct);
}
#include "RankLayer.h"
#include "Utils/AudioUtil.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
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
	//加载cocostudio文件
	Node* root = CSLoader::createNode("scenes/start/layers/RankLayer.csb");
	this->addChild(root);

	EventListenerTouchOneByOne* eventListener = EventListenerTouchOneByOne::create();
	eventListener->onTouchBegan = [this](Touch *touch, Event *event) {
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
	//设置吞噬触摸
	eventListener->setSwallowTouches(true);
	size = Director::getInstance()->getVisibleSize();

	//关闭按钮
	Button* closeMenuBtn = dynamic_cast<Button*>(root->getChildByName("closeBtn"));

	//背景
	Sprite* bgSp = dynamic_cast<Sprite*>(root->getChildByName("bg"));

	if (sence->getTag() == 100) {
		bgSp->setVisible(false);
		//是游戏场景类
		closeMenuBtn->addClickEventListener([this, eventListener](Ref*) {
			eventListener->setSwallowTouches(false);
			AudioUtil::getInstence()->buttonClickSound();
			//移出暂停层
			removeAllChildren();
			//恢复背景音乐
			AudioUtil::getInstence()->audioResume();
			//游戏继续
			Director::getInstance()->resume();
		});
	} else if(sence->getTag() == 101) {
		//开始场景类
		closeMenuBtn->addClickEventListener([this, eventListener](Ref*) {
			eventListener->setSwallowTouches(false);
			AudioUtil::getInstence()->buttonClickSound();
			//移出排行榜层
			removeAllChildren();
		});
	}

	//分数文本
	TextAtlas *scoreText_1 = dynamic_cast<TextAtlas*>(root->getChildByName("ScoreNumberText_1"));
	TextAtlas *scoreText_2 = dynamic_cast<TextAtlas*>(root->getChildByName("ScoreNumberText_2"));
	TextAtlas *scoreText_3 = dynamic_cast<TextAtlas*>(root->getChildByName("ScoreNumberText_3"));
	int score = UserDefault::getInstance()->getIntegerForKey("score");
	scoreText_1->setString(std::to_string(score));
	scoreText_2->setString("0");
	scoreText_3->setString("0");
	return true;
}
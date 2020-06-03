#include "RankLayer.h"
#include "Utils/AudioUtil.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
using namespace cocos2d::ui;
RankLayer::RankLayer(){

}

RankLayer::~RankLayer() {

}

RankLayer* RankLayer::create() {
	RankLayer *ret = new (std::nothrow)RankLayer();
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
		//开始场景类
		closeMenuBtn->addClickEventListener([this, eventListener](Ref*) {
			if (onExit != nullptr) {
				onExit();
			}

			eventListener->setSwallowTouches(false);
			AudioUtil::getInstence()->buttonClickSound();
			Director::getInstance()->resume();//游戏继续

			runAct(Vec2(0, 0),Vec2(0, size.width),CallFunc::create([this]() {
				removeAllChildren();//移出排行版层
			})
			);
		});

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

void RankLayer::runAct(Vec2 v1, Vec2 v2, CallFunc* callFunc) {
	MoveBy* mb = MoveBy::create(0, v1);
	MoveTo* mt = MoveTo::create(0.3f, v2);
	//auto callFunc = CallFunc::create([this]() {
	//	removeAllChildren();//移出排行版层
	//});
	Sequence* seqAct = Sequence::create(mb, mt, callFunc, nullptr);
	this->runAction(seqAct);
}
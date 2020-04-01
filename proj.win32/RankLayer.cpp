#include "RankLayer.h"
#include "AudioUtil.h"
#include "ui/CocosGUI.h"
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
	
	//设置吞噬触摸
	EventListenerTouchOneByOne* eventListener = EventListenerTouchOneByOne::create();
	eventListener->onTouchBegan = [this](Touch *touch, Event *event) {
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
	//设置吞噬触摸
	eventListener->setSwallowTouches(true);
	size = Director::getInstance()->getVisibleSize();

	//排行榜背景精灵
	Sprite* rankSp = Sprite::create("image/ui/rankSp.png");
	rankSp->setPosition(Vec2(size.width / 2 , size.height / 2));
	rankSp->setScale(0.7f);
	this->addChild(rankSp, 5);

	//创建继续游戏按钮
	Button* resumeBtn = Button::create("image/ui/continueGame_normal.png", "image/ui/continueGame_pressed.png");
	resumeBtn->setPosition(Vec2(size.width / 2, size.height / 2 - 120));
	resumeBtn->setScale(0.7f);
	this->addChild(resumeBtn, 5);

	//返回主菜单
	Button* backMenuBtn = Button::create("image/ui/backMenu_normal.png", "image/ui/backMenu_pressed.png");
	backMenuBtn->setPosition(Vec2(size.width / 2, size.height / 2 - 120));
	backMenuBtn->setScale(0.7f);
	this->addChild(backMenuBtn, 5);

	if (sence->getTag() == 100) {
		//是游戏场景类
		resumeBtn->setVisible(true);
		backMenuBtn->setVisible(false);
		resumeBtn->addClickEventListener([this, eventListener](Ref*) {
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
		resumeBtn->setVisible(false);
		backMenuBtn->setVisible(true);
		Button* startBtn = (Button*)sence->getChildByTag(1);
		Button* settingBtn = (Button*)sence->getChildByTag(2);
		Button* helpBtn = (Button*)sence->getChildByTag(3);
		Button* aboutBtn = (Button*)sence->getChildByTag(4);
		backMenuBtn->addClickEventListener([this, startBtn, settingBtn, helpBtn, aboutBtn](Ref*) {
			AudioUtil::getInstence()->buttonClickSound();
			//移出排行榜层
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
	}

	//创建分数文本:1.显示的内容 2.图片的路径 3.字符宽度 4.字符高度 5.第一个字符
	TextAtlas *scoreText = TextAtlas::create("0", "image/ui/zz-num-g.png", 36, 32, "0");
	scoreText->setPosition(Vec2(size.width / 2, size.height / 2 + 67));
	scoreText->setScale(0.8f);
	this->addChild(scoreText, 5);
	int score = UserDefault::getInstance()->getIntegerForKey("score");
	scoreText->setString(std::to_string(score));
	return true;
}
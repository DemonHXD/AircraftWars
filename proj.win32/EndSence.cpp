#include "EndSence.h"
#include "GameSenceManager.h"
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
	Size size = Director::getInstance()->getVisibleSize();

	//创建背景
	Sprite* bgSp = Sprite::create("image/ui/finish_bg.png");
	bgSp->setAnchorPoint(Vec2(0, 0));
	this->addChild(bgSp, 0);

	//创建游戏结束精灵
	Sprite* gameOverSp = Sprite::create("image/ui/game_over.png");
	gameOverSp->setPosition(Vec2(size.width / 2, size.height / 2 + 200));
	this->addChild(gameOverSp, 1);

	//最终得分精灵
	Sprite* finalScoreSp = Sprite::create("image/ui/final_score.png");
	finalScoreSp->setPosition(Vec2(size.width / 2 - 100, size.height / 2 + 100));
	this->addChild(finalScoreSp, 1);

	scoreText = TextAtlas::create("0", "image/ui/zz-num-g.png", 36, 32, "0");
	scoreText->setPosition(Vec2(size.width / 2 + 100, size.height / 2 + 100));
	scoreText->setScale(0.8f);
	this->addChild(scoreText, 5);

	//开启监听
	_eventDispatcher->addCustomEventListener("finalScoreDeath", [this](EventCustom* event) {
		GameSenceManager* gameSence = (GameSenceManager*)event->getUserData();
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
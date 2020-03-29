#include "EndSence.h"
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
	return true;
}
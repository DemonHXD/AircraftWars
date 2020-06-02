#include "WelcomeSence.h"
#include "StartSence.h"
#include "cocostudio/CocoStudio.h"
#include "Utils/AudioUtil.h"
//using namespace cocos2d::ui;//UI命名空间
using namespace cocostudio::timeline;
Scene* WelcomeSence::createScene() {
	auto scene = Scene::create();
	auto layer = WelcomeSence::create();
	scene->addChild(layer);
	return scene;
}

bool WelcomeSence::init() {
	if (!Layer::init()) {
		return false;
	}
	Node* root = CSLoader::createNode("scenes/welcome/layers/WelcomeLayer.csb");
	this->addChild(root);

	Sprite* bg = dynamic_cast<Sprite*>(root->getChildByName("bgSp"));

	//开启单次调度器
	scheduleOnce(schedule_selector(WelcomeSence::jumpStartSecen), 2.5f);

	//0.3秒后播放timi提示音
	scheduleOnce(schedule_selector(WelcomeSence::playTimi), 0.3f);

	FadeIn* textIn = FadeIn::create(1.0f);
	FadeOut* textOut = FadeOut::create(2.0f);
	//创建序列动作
	Sequence* seqAct = Sequence::create(textIn, textOut, nullptr);
	bg->runAction(seqAct);
	return true;
}

void WelcomeSence::jumpStartSecen(float dt) {
	Scene* scene = StartSence::createScene();
	auto reSence = TransitionFade::create(0.8f, scene);
	Director::getInstance()->replaceScene(reSence);
}

void WelcomeSence::playTimi(float dt) {
	//播放timi提示音
	AudioUtil::getInstence()->playTimi();
}
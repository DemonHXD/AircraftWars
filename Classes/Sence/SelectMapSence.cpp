#include "SelectMapSence.h"
#include "cocostudio/CocoStudio.h"
#include "GameSence.h"
#include <vector>
#include "ui/CocosGUI.h"//UI头文件
#include "StartSence.h"
#include "ui/SelectMapItem.h"
#include "Utils/AudioUtil.h"
using namespace cocostudio::timeline;
using namespace cocos2d::ui;//UI命名空间
Scene* SelectMapSence::createScene() {
	auto scene = Scene::create();
	auto layer = SelectMapSence::create();
	scene->addChild(layer);
	return scene;
}

bool SelectMapSence::init() {
	if (!Layer::init()) {
		return false;
	}
	Node* root = CSLoader::createNode("scenes/selectMap/layers/SelectMapLayer.csb");
	this->addChild(root);

	//返回按钮
	Button* backBtn = dynamic_cast<Button*>(root->getChildByName("backBtn"));
	backBtn->addClickEventListener([](Ref*) {
		AudioUtil::getInstence()->buttonClickSound();
		Scene* startSence = StartSence::createScene();
		auto reSence = TransitionSlideInR::create(0.5f, startSence);
		Director::getInstance()->replaceScene(reSence);
	});

	//获取ScrollView子节点
	ScrollView* scrollView = dynamic_cast<ScrollView*>(root->getChildByName("ScrollView"));

	//设置滚动区域的innerSize
	scrollView->setInnerContainerSize(Size(400 * 6, 600));
	std::vector<SelectMapItem*> items;
	//添加子控件，子控件必须作为scrollView的子节点
	for (int i = 0; i < 6; i++) {
		SelectMapItem* item = SelectMapItem::create(i + 1);
		item->setPosition(Vec2(i * 400, 0));
		scrollView->addChild(item);
		items.push_back(item);
		//根据本地选择
		if (i == 0) {
			item->setSelected(true);
		}
	}

	for each (SelectMapItem* item in items) {
		//给item添加监听事件
		item->addClickEventListener([item, items](Ref*) {
			AudioUtil::getInstence()->buttonClickSound();
			for (SelectMapItem* temp : items) {
				temp->setSelected(false);
			}
			//设置被点击选项选中
			item->setSelected(true);
		});
	}

	Button* startGameBtn = dynamic_cast<Button*>(root->getChildByName("startGameBtn"));
	startGameBtn->addClickEventListener([](Ref*) {
		AudioUtil::getInstence()->buttonClickSound();
		//关闭开始场景背景音乐
		AudioUtil::getInstence()->stopStartBgm();
		

		//恢复背景音乐
		//AudioUtil::getInstence()->audioResume();

		//创建一个新场景
		Scene* gameSence = GameSence::createScene();
		//设置一个界面切换的动作，0.5秒的跳动动作
		auto reSence = TransitionFade::create(0.5f, gameSence);
		Director::getInstance()->replaceScene(reSence);
		//开启游戏场景BGM
		AudioUtil::getInstence()->playGameBgm();
	});
	return true;
}
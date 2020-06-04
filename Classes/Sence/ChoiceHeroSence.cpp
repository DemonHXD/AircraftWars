#include "ChoiceHeroSence.h"
#include "cocostudio/CocoStudio.h"
#include "Ui/ChoiceHeroItem.h"
#include <vector>
#include "ui/CocosGUI.h"//UI头文件
#include "StartSence.h"
#include "Utils/AudioUtil.h"
using namespace cocostudio::timeline;
using namespace cocos2d::ui;//UI命名空间
Scene* ChoiceHeroSence::createScene() {
	auto scene = Scene::create();
	auto layer = ChoiceHeroSence::create();
	scene->addChild(layer);
	return scene;
}

bool ChoiceHeroSence::init() {
	if (!Layer::init()) {
		return false;
	}
	Node* root = CSLoader::createNode("scenes/buyHero/layers/BuyHeroLayer.csb");
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

	int selectHero = UserDefault::getInstance()->getIntegerForKey("heroType", 0);

	//设置滚动区域的innerSize
	scrollView->setInnerContainerSize(Size(400 * 5, 500));
	std::vector<ChoiceHeroItem*> items;
	//添加子控件，子控件必须作为scrollView的子节点
	for (int i = 0; i < 5; i++) {
		ChoiceHeroItem* item = ChoiceHeroItem::create(i);
		item->setPosition(Vec2(i * 400, 0));
		scrollView->addChild(item);
		items.push_back(item);
		//根据本地选择
		if (i == selectHero) {
			item->setSelected(true);
		}
	}

	for each (ChoiceHeroItem* item in items) {
		//给item添加监听事件
		item->addClickEventListener([item, items](Ref*) {
			AudioUtil::getInstence()->buttonClickSound();
			for(ChoiceHeroItem* temp : items) {
				temp->setSelected(false);
			}
			//设置被点击选项选中
			item->setSelected(true);
		});
	}
	return true;
}



#include "ChoiceItem.h"
#include "iostream"
#include "cocostudio/CocoStudio.h"
using namespace cocos2d;
using namespace cocos2d::ui;
ChoiceItem::ChoiceItem() {

}

ChoiceItem::~ChoiceItem() {

}

ChoiceItem* ChoiceItem::create(int index) {
	ChoiceItem* ret = new (std::nothrow) ChoiceItem();
	if (ret && ret->init(index)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool ChoiceItem::init(int index) {
	if (!Widget::init()) {
		return false;
	}
	//加载csb文件
	Node* root = CSLoader::createNode("scenes/start/item/ChoiceItem.csb");
	this->addChild(root);

	//获取人物头像图片
	Sprite* Image_player = dynamic_cast<Sprite*>(root->getChildByName("Image_player"));

	//获取yes图片
	Image_yes = dynamic_cast<Sprite*>(root->getChildByName("Image_yes"));
	Image_yes->setVisible(false);

	//根据值改变图片 参数:图片路径
	char filename[40];
	sprintf_s(filename, "Characters/%d/Fly/1.png", index);
	Image_player->setTexture(filename);

	//开启飞行动画
	runAction(Image_player, index);

	//获取背景按钮，设置吞噬触摸为false
	Button_bg = dynamic_cast<Button*>(root->getChildByName("Button_bg"));
	Button_bg->setSwallowTouches(false);
	return true;
}

void ChoiceItem::setSelected(bool isSelect) {
	Image_yes->setVisible(isSelect);
}

void ChoiceItem::addClickEventListener(const ccWidgetClickCallback& callback) {
	Button_bg->addClickEventListener(callback);
}

/*
	飞行动画
*/
void ChoiceItem::runAction(Sprite* Image_player,int index) {
	//创建图片收集者
	Animation* animation = Animation::create();
	char fileName[40];
	for (int i = 1; i <= 4; i++) {
		sprintf_s(fileName, "Characters/%d/Fly/%d.png", index, i);
		animation->addSpriteFrameWithFile(fileName);
	}
	//间隔时间
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(-1);
	//开启动画
	Animate* animate = Animate::create(animation);
	Image_player->runAction(animate);
}
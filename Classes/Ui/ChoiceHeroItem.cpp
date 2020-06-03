#include "ChoiceHeroItem.h"
#include "iostream"
#include "cocostudio/CocoStudio.h"
using namespace cocos2d;
using namespace cocos2d::ui;
ChoiceHeroItem::ChoiceHeroItem() {

}

ChoiceHeroItem::~ChoiceHeroItem() {

}

ChoiceHeroItem* ChoiceHeroItem::create(int index) {
	ChoiceHeroItem* ret = new (std::nothrow) ChoiceHeroItem();
	if (ret && ret->init(index)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool ChoiceHeroItem::init(int index) {
	if (!Widget::init()) {
		return false;
	}
	//加载csb文件
	Node* root = CSLoader::createNode("scenes/buyHero/layers/HeroChoiceItem.csb");
	this->addChild(root);

	//获取人物头像图片
	Sprite* Image_player = dynamic_cast<Sprite*>(root->getChildByName("Image_player"));

	//获取yes图片
	Image_yes = dynamic_cast<Sprite*>(root->getChildByName("Image_yes"));
	Image_yes->setVisible(false);

	//获取文字
	Text* text = dynamic_cast<Text*>(root->getChildByName("text"));

	heroType = index;

	switch (index) {
	case 0:
		text->setText("yellow aircraft");
		break;	
	case 1:
		text->setText("blue aircraft");
		break;	
	case 2:
		text->setText("red aircraft");
		break;	
	case 3:
		text->setText("pink aircraft");
		break;
	}

	//根据值改变图片 参数:图片路径
	char filename[80];
	sprintf_s(filename, "scenes/buyHero/image/hero_%d_1.png", index);
	Image_player->setTexture(filename);

	//获取背景按钮，设置吞噬触摸为false
	Button_bg = dynamic_cast<Button*>(root->getChildByName("Button_bg"));
	Button_bg->setSwallowTouches(false);
	return true;
}

void ChoiceHeroItem::setSelected(bool isSelect) {
	Image_yes->setVisible(isSelect);
	UserDefault::getInstance()->setIntegerForKey("heroType", heroType);
}

void ChoiceHeroItem::addClickEventListener(const ccWidgetClickCallback& callback) {
	Button_bg->addClickEventListener(callback);
}

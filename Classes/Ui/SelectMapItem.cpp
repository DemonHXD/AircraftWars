#include "SelectMapItem.h"
#include "iostream"
#include "cocostudio/CocoStudio.h"
using namespace cocos2d;
using namespace cocos2d::ui;
SelectMapItem::SelectMapItem() {

}

SelectMapItem::~SelectMapItem() {

}

SelectMapItem* SelectMapItem::create(int index) {
	SelectMapItem* ret = new (std::nothrow) SelectMapItem();
	if (ret && ret->init(index)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool SelectMapItem::init(int index) {
	if (!Widget::init()) {
		return false;
	}
	//加载csb文件
	Node* root = CSLoader::createNode("scenes/selectMap/items/SelectMapItem.csb");
	this->addChild(root);

	//获取人物头像图片
	Sprite* Image_player = dynamic_cast<Sprite*>(root->getChildByName("Image_player"));

	//获取yes图片
	Image_yes = dynamic_cast<Sprite*>(root->getChildByName("Image_yes"));
	Image_yes->setVisible(false);

	mapType = index;

	//根据值改变图片 参数:图片路径
	char filename[80];
	sprintf_s(filename, "scenes/selectMap/image/bg%d.jpg", index);
	Image_player->setTexture(filename);

	//获取背景按钮，设置吞噬触摸为false
	Button_bg = dynamic_cast<Button*>(root->getChildByName("Button_bg"));
	Button_bg->setSwallowTouches(false);
	return true;
}

void SelectMapItem::setSelected(bool isSelect) {
	Image_yes->setVisible(isSelect);
	UserDefault::getInstance()->setIntegerForKey("mapType", mapType);
}

void SelectMapItem::addClickEventListener(const ccWidgetClickCallback& callback) {
	Button_bg->addClickEventListener(callback);
}

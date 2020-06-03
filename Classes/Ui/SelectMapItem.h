#ifndef _SelectMapItem_H_
#define _SelectMapItem_H_
#include "ui/CocosGUI.h"
#include "cocos2d.h"
//using namespace cocos2d::ui;
//角色选项类：
class SelectMapItem : public cocos2d::ui::Widget {
public:
	SelectMapItem();
	~SelectMapItem();
	static SelectMapItem* create(int index);
	bool init(int index);
	void setSelected(bool isSelect);//设置是否选中
	void addClickEventListener(const ccWidgetClickCallback& callback);
private:
	cocos2d::Sprite* Image_yes;//选中图片
	cocos2d::ui::Button* Button_bg;//背景按钮
	int mapType;
};
#endif // !_SelectMapItem_H_




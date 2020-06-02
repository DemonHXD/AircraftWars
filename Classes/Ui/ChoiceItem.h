#ifndef __ChoiceItem_H_
#define __ChoiceItem_H_
#include "ui/CocosGUI.h"
#include "cocos2d.h"
//using namespace cocos2d::ui;
//角色选项类：
class ChoiceItem : public cocos2d::ui::Widget{
public:
	ChoiceItem();
	~ChoiceItem();
	static ChoiceItem* create(int index);
	bool init(int index);
	void runAction(cocos2d::Sprite* Image_player, int index);
	void setSelected(bool isSelect);//设置是否选中
	void addClickEventListener(const ccWidgetClickCallback& callback);
private:
	cocos2d::Sprite* Image_yes;//选中图片
	cocos2d::ui::Button* Button_bg;//背景按钮
};

#endif // !__ChoiceItem_H_




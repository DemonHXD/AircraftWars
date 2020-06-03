#ifndef __ChoiceHeroItem_H_
#define __ChoiceHeroItem_H_
#include "ui/CocosGUI.h"
#include "cocos2d.h"
//using namespace cocos2d::ui;
//角色选项类：
class ChoiceHeroItem : public cocos2d::ui::Widget {
public:
	ChoiceHeroItem();
	~ChoiceHeroItem();
	static ChoiceHeroItem* create(int index);
	bool init(int index);
	void setSelected(bool isSelect);//设置是否选中
	void addClickEventListener(const ccWidgetClickCallback& callback);
private:
	cocos2d::Sprite* Image_yes;//选中图片
	cocos2d::ui::Button* Button_bg;//背景按钮
	int heroType;
};

#endif // !__ChoiceHeroItem_H_




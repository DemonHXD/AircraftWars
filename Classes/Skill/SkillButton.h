#ifndef _SkillButton_H_
#define _SkillButton_H_
#include "Ui/CocosGUI.h"

/*
	技能按钮类:继承于按钮类

	观察者模式(一对多的关系)：底层实质就是函数指针
		1.监听器(观察者)
		2.回调函数
*/
class SkillButton :public cocos2d::ui::Button{
public:
	SkillButton(float coldTime):
		coldTime(coldTime), 
		isCold(false), 
		onColdBegan(nullptr),
		onColdEnded(nullptr)
	{
	
	}
	//~SkillButton();
	static SkillButton* create(
		float coldTime,
		const std::string& normalImage,
		const std::string& selectedImage = "",
		const std::string& disableImage = "",
		TextureResType texType = TextureResType::LOCAL);

	bool init(
		const std::string& normalImage,
		const std::string& selectedImage = "",
		const std::string& disableImage = "",
		TextureResType texType = TextureResType::LOCAL);

public:
	//function<返回值类型(形参表)> 变量名
	typedef std::function<void()> ccColdBeganCallback;
	typedef std::function<void()> ccColdEndedCallback;

	ccColdBeganCallback onColdBegan;//指向当冷却开始时要调用的函数
	ccColdEndedCallback onColdEnded;//指向当冷却结束时要调用的函数

private:
	float coldTime;//技能冷却时间
	bool isCold;//技能是否正在冷却
};

#endif // !_SkillButton_H_




#include "SkillButton.h"
#include "cocos2d.h"
using namespace cocos2d::ui;
using namespace cocos2d;
SkillButton* SkillButton::create(
	float coldTime,
	const std::string& normalImage,
	const std::string& selectedImage,
	const std::string& disableImage,
	TextureResType texType) {
	SkillButton* ret = new(std::nothrow) SkillButton(coldTime);
	if (ret && ret->init(normalImage, selectedImage, disableImage, texType)) {
		ret->autorelease();
	} else {
		delete ret;
		ret = nullptr;
	}
	return ret;
}

bool SkillButton::init(
	const std::string& normalImage,
	const std::string& selectedImage,
	const std::string& disableImage,
	TextureResType texType) {
	if (!Button::init(normalImage, selectedImage, disableImage, texType)) {
		return false;
	}
	/*EventListenerTouchOneByOne*/
	//创建遮罩精灵:灰色
	Sprite* sp = Sprite::create(normalImage);
	//sp->setAnchorPoint(Vec2(0, 0));
	sp->setColor(Color3B::GRAY);

	//ProgressTimer:进度计数器(0 - 100)
	ProgressTimer* progressTimer = ProgressTimer::create(sp);
	progressTimer->setAnchorPoint(Vec2::ZERO);//设置锚点
	//progressTimer->setPercentage(80);//设置百分比
	progressTimer->setReverseDirection(true);//翻转旋转方向
	this->addChild(progressTimer);

	//给当前按钮添加点击监听事件
	this->addClickEventListener([this, progressTimer](Ref*) {
		//判断是否在技能冷却
		if (!isCold) {
			//调用冷却开始的函数
			if (onColdBegan != nullptr) {
				onColdBegan();//函数指针(实参表)
			}
			isCold = true;
			setTouchEnabled(false);//设置关闭触摸
			//1.时间 2.开始的百分比 3.结束的百分比
			auto progressFromTo = ProgressFromTo::create(coldTime, 100, 0);

			auto callFunc = CallFunc::create([this]() {
				//调用冷却结束的函数
				if (onColdEnded != nullptr) {
					onColdEnded();//函数指针(实参表)
				}
				isCold = false;//关闭技能冷却
				setTouchEnabled(true);//开启触摸
			});
			auto seqAct = Sequence::create(progressFromTo, callFunc, nullptr);
			progressTimer->runAction(seqAct);
		}
	});
	return true;
}
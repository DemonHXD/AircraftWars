#ifndef _JoyStick_H_
#define _JoyStick_H_
#include "Ui/CocosGUI.h"
#include "cocos2d.h"

class JoyStick : public cocos2d::ui::Widget{
public:
	JoyStick():
		onJoyStickBegan(nullptr), 
		onJoyStickMoved(nullptr) , 
		onJoyStickEnded(nullptr),
		isTouch(false),
		touchAxis(cocos2d::Vec2(0, 0))
	{
	
	}

	//1.背景图片 2.遥感图片
	static JoyStick* create(
		const std::string& bgImage,
		const std::string& stickImage
	);
	bool init(
		const std::string& bgImage,
		const std::string& stickImage
	);
	//当遥感被拖动时调用
	void onJoyStickTouch(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

	//默认调度器
	void update(float dt) override;
public:
	typedef std::function<void()> ccJoyStickBeganCallback;
	typedef std::function<void(cocos2d::Vec2)> ccJoyStickMovedCallback;
	typedef std::function<void()> ccJoyStickEndedCallback;

	ccJoyStickBeganCallback onJoyStickBegan;//当摇杆开始拖动时
	ccJoyStickMovedCallback onJoyStickMoved;//当摇杆拖动时
	ccJoyStickEndedCallback onJoyStickEnded;//当摇杆结束拖动时
private:
	cocos2d::ui::ImageView* stickIv;
	//cocos2d::ui::ImageView* bgIv;
	float redius;//半径
	cocos2d::Vec2 originPos;//摇杆起始坐标
	bool isTouch;//是否触摸
	cocos2d::Vec2 touchAxis;//触摸方向
};

#endif // !_JoyStick_H_




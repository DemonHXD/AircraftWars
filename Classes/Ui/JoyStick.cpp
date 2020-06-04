#include "JoyStick.h"

using namespace cocos2d;
using namespace cocos2d::ui;
JoyStick* JoyStick::create(const std::string& bgImage,const std::string& stickImage) {
	JoyStick* ret = new(std::nothrow)JoyStick();
	if (ret && ret->init(bgImage, stickImage)) {
		ret->autorelease();
	} else {
		delete ret;
		ret = nullptr;
	}
	return ret;
}

bool JoyStick::init(const std::string& bgImage,const std::string& stickImage) {
	if (!Widget::init()) {
		return false;
	}
	
	//创建背景图片 ImageView可以直接添加触摸/监听事件
	ImageView* bgIv = ImageView::create(bgImage);
	this->addChild(bgIv);

	//创建遥感图片 可拖动
	stickIv = ImageView::create(stickImage);
	stickIv->setTouchEnabled(true);//必须先开启触摸:setTouchEnabled
	this->addChild(stickIv);

	//半径 因为还要考虑到如果图片进行了缩放，那么还得乘上缩放比例
	redius = bgIv->getContentSize().width / 2 * bgIv->getScale();
	//初始坐标
	originPos = stickIv->getPosition();

	//给stick添加触摸监听事件
	stickIv->addTouchEventListener(CC_CALLBACK_2(JoyStick::onJoyStickTouch, this));
	//开启调度器
	scheduleUpdate();
	return true;
}

void JoyStick::update(float dt) {
	if (isTouch && onJoyStickMoved != nullptr) {
		onJoyStickMoved(touchAxis);
	}
}

void JoyStick::onJoyStickTouch(Ref* pSender, Widget::TouchEventType type) {
	//判断触摸阶段
	Vec2 touchPoint = Vec2::ZERO;
	Vec2 pos;
	Vec2 offset;
	MoveTo* mt = MoveTo::create(0.5f, originPos);;
	switch (type) {
	case Widget::TouchEventType::BEGAN://触摸开始
		isTouch = true;
		if (onJoyStickBegan != nullptr) {
			onJoyStickBegan();
		}
		//关闭移动动作
		stickIv->stopAction(mt);
		//获取触摸点的坐标Began
		touchPoint = stickIv->getTouchBeganPosition();
		//转换坐标系:将touchPoint从世界转到JoyStick坐标系下
		pos = this->convertToNodeSpaceAR(touchPoint);
		//stickIv用触摸点坐标赋值
		stickIv->setPosition(pos);
		break;
	case Widget::TouchEventType::MOVED://触摸移动
		
		//获取触摸点的坐标Move
		touchPoint = stickIv->getTouchMovePosition();
		//转换坐标系:将touchPoint从世界转到JoyStick坐标系下
		pos = this->convertToNodeSpaceAR(touchPoint);
		//将摇杆限制在半径内
		offset = pos - originPos;
		if (offset.getLength() > redius) {
			offset = offset.getNormalized() * redius;//getNormalized:单位向量 长度为1的向量
			pos = offset + originPos;
		}
		touchAxis = offset.getNormalized();
		//stickIv用触摸点坐标赋值
		stickIv->setPosition(pos);
		if (onJoyStickMoved != nullptr) {
			onJoyStickMoved(touchAxis);
		}
		break;
	default://触摸结束/取消
		isTouch = false;
		if (onJoyStickEnded != nullptr) {
			onJoyStickEnded();
		}
		//遥感回到原点
		stickIv->runAction(mt);
		break;
	}
}


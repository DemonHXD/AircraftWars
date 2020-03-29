#include "Bg.h"

Bg::Bg():speed(100) {
}

Bg::~Bg() {

}

Bg* Bg::create() {
	//1.申请Bg的内存
	Bg* ret = new(std::nothrow) Bg();
	//2.判断ret不等于空且初始化成功
	if (ret && ret->init()) {
		//3.加入自动释放池
		ret->autorelease();
		return ret;
	}

	delete ret;
	ret = nullptr;
	return ret;
}

bool Bg::init() {
	//调用父类Sprite的initWithFile方法
	if (!Sprite::initWithFile("image/bg/bg1.jpg")) {
		return false;
	}
	//初始化逻辑
	//设置自己的锚点
	setAnchorPoint(Vec2(0, 0));
	scheduleUpdate();
	return true;
}

void Bg::update(float dt) {
	// 背景向下滚动
	float y = getPositionY();
	y = y - speed * dt;
	//当前背景的y<=图片的高度时
	float h = getContentSize().height;

	if (y <= -h) {
		//为了避免有缝隙的产生，我们需要对y轴进行一个判断
		y = y + h * 2;
	}
	setPositionY(y);
}

#include "test.h"
test::test():speed(20){

}

test::~test() {

}

test* test::create(std::string filename, Vec2 v, std::string tag) {
	test* ret = new(std::nothrow) test();
	ret->tag = tag;
	if (ret && ret->init(filename,v))
	{
		ret->autorelease();
		return ret;
	}
	delete ret;
	ret = nullptr;
	return nullptr;
}
bool test::init(std::string filename, Vec2 v) {
	if (!Sprite::initWithFile(filename))
	{
		return false;
	}
	setPosition(v);
	scheduleUpdate();
	return true;
}

void test::circleMove(float pointX, float pointY) {
	//// ÏÈ¼ÆËã»¡¶È
	if (tag == "yueqiu")
	{
		
		this->circleRadius = 50;
	}else{
		this->circleRadius = 130;
	}
	float x = this->circleRadius * std::cos(pointX / this->circleRadius) + pointX;
	float y = this->circleRadius * std::sin(pointY / this->circleRadius) + pointY;
	setPosition(Vec2(x, y));
}

void test::update(float dt) {
	float r = getRotation();

	if (tag == "diqiu" || tag == "yueqiu")
	{
		circleMove(getPositionX(), getPositionY());
	}
	setRotation(r + speed * dt);
	
}
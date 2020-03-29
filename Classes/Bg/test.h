#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class test : public Sprite
{
private:
	float speed;
	std::string tag;
	float radian = 0;
	float circleRadius;
public:
	test();
	~test();
	static test* create(std::string filename, Vec2 v,std::string tag);
	bool init(std::string filename, Vec2 v);
	void update(float dt) override;
	void circleMove(float pointX, float pointY);
};


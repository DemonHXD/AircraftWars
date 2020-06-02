#pragma once
#include "cocos2d.h"//引用头文件
//引用命名空间
using namespace cocos2d;
//背景是可移动的精灵
class Bg : public Sprite
{
private:
	float speed;
public:
	static Bg* create();//创建方法
	bool init() override;//初始化的方法
	void update(float dt);
	Bg();
	~Bg();
};


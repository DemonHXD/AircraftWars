#ifndef __RankLayer_H__
#define __RankLayer_H__
#include "cocos2d.h"
using namespace cocos2d;

class RankLayer : public Layer{
public:
	RankLayer();
	~RankLayer();
	static RankLayer* create();
	bool init() override;
	void runAct(Vec2 v1, Vec2 v2, CallFunc* callFunc = nullptr);
public:
	typedef std::function<void()> ccExitCallback;

	ccExitCallback onExit;//指向退出设置时要调用的函数
private:
	
	Size size;
};
#endif // !__RankLayer_H__




#ifndef __RankLayer_H__
#define __RankLayer_H__
#include "cocos2d.h"
using namespace cocos2d;
class RankLayer : public Layer{
public:
	RankLayer(Layer *sence);
	~RankLayer();
	static RankLayer* create(Layer *sence);
	bool init() override;
private:
	Layer *sence;
};
#endif // !__RankLayer_H__




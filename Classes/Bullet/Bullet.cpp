#include "Bullet.h"
#include "BulletManager.h"

Bullet::Bullet(int type, BulletType bulletType)
	:speed(200), 
	bulletType(bulletType),
	type(type),
	isLive(true),
	//atk(20 + rand() % 11)//伤害值:20-30:20 + (0-10) 
	atk(10)//伤害值:20-30:20 + (0-10) 
{
}

Bullet::~Bullet() {

}

Bullet* Bullet::create(int type, BulletType bulletType) {
	Bullet* ret = new(std::nothrow) Bullet(type, bulletType);
	if (ret && ret->init()) {
		ret->autorelease();
		//直接使用静态容器，在创建成功一个子弹后便添加进去
		//bulletList.push_back(ret);
		//开启子弹的调度器
		//ret->
		return ret;
	}
	delete ret;
	ret = nullptr;
	return ret;
}

bool Bullet::init() {
	//根据不同的类型使用不同的路径
	char filename[40];
	sprintf_s(filename, "image/bullet_effect/bullet_%d_1.png", bulletType);//输出到字符数组中：1.数组的首地址  

	if (!Sprite::initWithFile(filename)) {
		return false;
	}
	bulletRun();
	//设置子弹的锚点
	setAnchorPoint(Vec2(0.5, 0));

	scheduleUpdate();
	return true;
}

/*
	子弹动画
*/
void Bullet::bulletRun() {
	//创建图片收集者
	Animation* animation = Animation::create();
	if (bulletType == Missile || bulletType == Rocket) {
		for (int i = 1; i <= 2; i++) {
			char filename[40];
			sprintf(filename, "image/bullet_effect/bullet_%d_%d.png", bulletType, i);
			log("%s", filename);
			animation->addSpriteFrameWithFileName(filename);
		}
	} else if (bulletType == OrdinaryBullet) {
		char filename[40];
		sprintf(filename, "image/bullet_effect/bullet_%d_%d.png", bulletType, 1);
		animation->addSpriteFrameWithFileName(filename);
	}
	//间隔时间
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(-1);
	//开启动画
	Animate* animate = Animate::create(animation);
	this->runAction(animate);
}

void Bullet::update(float dt) {

	//如果是死亡状态,则回收自身
	if (!isLive) {
		BulletManager::getInstance()->collection(this, type);
		return;
	}

	Vec2 pos = getPosition();//获取原先的坐标
	setPosition(pos + dir * speed * dt);
	float h = Director::getInstance()->getVisibleSize().height;
	float w = Director::getInstance()->getVisibleSize().width;
	float y = getPositionY();
	float x = getPositionX();
	//当超出屏幕时 
	if (y >= h + 20 || x <= -20 || x >= w + 20) {
		//removeFromParent();//从父节点上移除

		//将当前子弹从管理类中移除
		BulletManager::getInstance()->collection(this, type);
	}
}
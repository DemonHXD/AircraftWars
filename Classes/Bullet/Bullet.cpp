#include "Bullet.h"
#include "BulletManager.h"
#include "Enemy/EnemyManager.h"
#include "Enemy/Enemy.h"
#include "Utils/AudioUtil.h"
#include "Hero/Hero.h"
Bullet::Bullet(BulletType bulletType, Vec2 dir)
	:speed(200),
	bulletType(bulletType),
	isLive(true),
	dir(dir),
	//atk(20 + rand() % 11)//伤害值:20-30:20 + (0-10) 
	atk(10)//伤害值:20-30:20 + (0-10) 
{
}

Bullet::~Bullet() {

}

Bullet* Bullet::create(BulletType bulletType, Vec2 dir) {
	Bullet* ret = new(std::nothrow) Bullet(bulletType, dir);
	if (ret && ret->init()) {
		ret->autorelease();
		return ret;
	}
	delete ret;
	ret = nullptr;
	return ret;
}

void Bullet::onEnter() {
	Sprite::onEnter();

	//开启调度器
	scheduleUpdate();
	//schedule(schedule_selector(Bullet::bulletUpdate), 1.5f, -1, 0);

	bulletRun();

	Hero* hero = (Hero*)_parent->getChildByTag(50);
	if (bulletType == EnemyBullet) {
		Vec2 newDir = hero->getPosition() - getPosition();
		newDir = newDir.getNormalized();
		setDir(newDir);
	} else if (bulletType == SkillBullet) {
		Enemy* enemy =  EnemyManager::getInstance()->enemyList.front();
		Vec2 newDir = enemy->getPosition() - getPosition();
		newDir = newDir.getNormalized();
		setDir(newDir);
	}

	isLive = true;
}

bool Bullet::init() {
	//根据不同的类型使用不同的路径
	char filename[80];

	switch (bulletType) {
	case HeroBullet:
		setScale(0.3f);
		sprintf_s(filename, "image/bullet_effect/hero/bullet_0_%d.png", 2);
		break;
	case EnemyBullet:
		randEnemyBullet = rand() % 2;
		sprintf_s(filename, "image/bullet_effect/enemy/bullet_%d_%d.png", randEnemyBullet, 1);
		break;
	case WingAircraftBullet:
		sprintf_s(filename, "image/bullet_effect/wingAircraft/bullet_0_%d.png", 1);
		break;
	case SkillBullet:
		sprintf_s(filename, "image/bullet_effect/skill/feidan.png");
		break;
	}

	if (!Sprite::initWithFile(filename)) {
		return false;
	}
	bulletRun();
	//设置子弹的锚点
	setAnchorPoint(Vec2(0.5, 0));
	return true;
}

/*
	子弹动画
*/
void Bullet::bulletRun() {
	char filename[80];
	//创建图片收集者
	Animation* animation = Animation::create();
	if (bulletType == HeroBullet) {
		for (int i = 2; i <= 4; i++) {
			sprintf(filename, "image/bullet_effect/hero/bullet_0_%d.png", i);
			animation->addSpriteFrameWithFileName(filename);
		}
	} else if (bulletType == EnemyBullet) {
		for (size_t i = 1; i <= 2; i++) {
			sprintf(filename, "image/bullet_effect/enemy/bullet_%d_%d.png", randEnemyBullet, i);
			animation->addSpriteFrameWithFileName(filename);
		}
	} else if (bulletType == WingAircraftBullet) {
		for (size_t i = 1; i <= 2; i++) {
			sprintf(filename, "image/bullet_effect/wingAircraft/bullet_0_%d.png", i);
			animation->addSpriteFrameWithFileName(filename);
		}
	}
	//间隔时间
	animation->setDelayPerUnit(0.3f);
	animation->setLoops(-1);
	//开启动画
	Animate* animate = Animate::create(animation);
	this->runAction(animate);
}

void Bullet::update(float dt) {

	//如果是死亡状态,则回收自身
	if (!isLive) {
		BulletManager::getInstance()->collection(this, bulletType);
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
		//将当前子弹从管理类中移除
		BulletManager::getInstance()->collection(this, bulletType);
	}
}

/*
	发射子弹的声音
*/
void Bullet::shootSound() {
	//int bulletEff;
	switch (bulletType) {
	case HeroBullet:
		AudioUtil::getInstence()->enemyShootSound();
		break;
	case EnemyBullet:
		AudioUtil::getInstence()->heroShoottSound();
		break;
	case WingAircraftBullet:
		AudioUtil::getInstence()->wingAirShoot();
		break;
	}
	//switch (type) {
	//case -1:
	//	AudioUtil::getInstence()->enemyShootSound();
	//	break;	
	//case 1:
	//	AudioUtil::getInstence()->heroShoottSound();
	//	break;	
	//case 2:
	//	AudioUtil::getInstence()->wingAirShoot();
	//	break;
	//}
}
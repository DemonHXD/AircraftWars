#include "Enemy.h"
#include "EnemyManager.h"
#include "Bullet/Bullet.h"
#include "Bullet/BulletManager.h"
#include "bullet/BulletFactory.h"
#include "Prop/propManager.h"
#include "Prop/prop.h"
#include "Utils/AudioUtil.h"
#include "AudioEngine.h"
using namespace experimental;
#define ENEMY -1
const float PI = 3.1415926;//圆周率
Enemy::Enemy(Vec2 heroPos, EnemyType type):
	enemyType(type), 
	speed(150),
	isLive(true), 
	heroPos(heroPos), 
	onEnemyMoved(nullptr),
	isSkillBullet(false)
{
	if (type <= Boss1) {
		//根据不同类型的敌机设置不同的血量
		score = totalHp = hp = (type + 1) * 10;
	} else {
		score = totalHp = hp = 5000;
	}
	
}

Enemy::~Enemy() {

}

Enemy* Enemy::create(EnemyType type, Vec2 heroPos) {
	Enemy* ret = new(std::nothrow) Enemy(heroPos, type);
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	delete ret;
	ret = nullptr;
	return nullptr;
}

bool Enemy::init() {
	//根据不同的类型使用不同的路径
	char filename[40];
	if (enemyType >= Boss1)
	{
		sprintf(filename, "image/enemy/boss%d_0.png", enemyType);//输出到字符数组中：
	}
	else {
		sprintf(filename, "image/enemy/enemy%d.png", enemyType);//输出到字符数组中：
	}
	
	if (!Sprite::initWithFile(filename))
	{
		return false;
	}

	size = Director::getInstance()->getVisibleSize();
	//开启敌机飞行的调度器
	scheduleUpdate();

	createEnemyBlood();

	//开启敌机射击的调度器
	schedule(schedule_selector(Enemy::shoot), 1, -1, 1);
	
	schedule(schedule_selector(Enemy::moveUpdate), 0.5, -1, 0);

	

	//createProp

	//开启敌机飞行的动画
	if (enemyType == Boss2) {
		enemyAction();
		schedule(schedule_selector(Enemy::fastShootUpdate), 5, -1, 5);
		schedule(schedule_selector(Enemy::createProp), 5, -1, 5);
		//schedule(schedule_selector(Enemy::dispersedShootUpdate), 0.3, -1, 8);
	}
	return true;
}

void Enemy::moveUpdate(float dt) {
	if (onEnemyMoved != nullptr) {
		onEnemyMoved(getPosition(), isSkillBullet);
	}
}

void Enemy::update(float dt) {

	if (!isLive) {
		return;
	}

	float y = getPositionY();
	y = y - dt * speed;
	setPositionY(y);

	if (enemyType == Boss2) {
		if (y <= size.height / 4 * 3) {
			unscheduleUpdate();
		}
	}else if (y <= size.height / 2 + 100) {
		unscheduleUpdate();
	}
	


	//当超出屏幕时
	if (y < -40)
	{
		//将敌机从敌机管理器中移除
		EnemyManager::getInstance()->collection(this);
	}
}

void Enemy::createShoot(float angle) {
	//创建子弹
	Bullet* bullet = BulletFactory::createBullet(EnemyBullet, Vec2(1, 0));
	bullet->setPosition(getPositionX(), getPositionY() - 100);
	if (angle != 0) {
		//设置子弹旋转
		bullet->setRotation(angle);
		// 设置子弹的方向
		bullet->setDir(Vec2(sin(angle / 180 * PI), cos(angle / 180 * PI)));
	}
	_parent->addChild(bullet);

	//将子弹添加到管理类中, 
	BulletManager::getInstance()->addEnemyBullet(bullet);
}

void Enemy::createProp(float dt) {
	Prop* prop = Prop::create((PropType)(rand() % 4 + 1));
	prop->setPosition(Vec2(getPosition()));
	_parent->addChild(prop, 10);
	PropManager::getInstance()->addPorp(prop);
}

void Enemy::fastShootUpdate(float dt) {
	for (int i = 1; i <= 8; i++) {
		Vec2 newDir = heroPos - Vec2(getPositionX(), getPositionY() - 50);
		newDir = newDir.getNormalized();
		Bullet* bullet = BulletFactory::createBullet(EnemyBullet, newDir);
		bullet->shootSound();
		bullet->setPosition(getPositionX() + getContentSize().width / 2 - 30 * i, getPositionY() - 100);
		_parent->addChild(bullet);
		BulletManager::getInstance()->addEnemyBullet(bullet);
	}
}

/*
	敌机飞行动画
*/
void Enemy::enemyAction() {
	//创建图片收集者
	Animation* animation = Animation::create();
	for (int i = 0; i <= 4; i++) {
		char filename[40];
		sprintf(filename, "image/enemy/boss%d_%d.png", enemyType, i);
		//log("%s", filename);
		animation->addSpriteFrameWithFileName(filename);
	}
	//间隔时间
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(-1);
	//开启动画
	Animate* animate = Animate::create(animation);
	this->runAction(animate);
}

/*
	敌机死亡
*/
void Enemy::die(){

	//分发敌机死亡的消息
	_eventDispatcher->dispatchCustomEvent("onEnemyDeath", this);

	//播放敌机死亡音效
	AudioUtil::getInstence()->enemyDesyEff();
	//int blastEff = AudioEngine::play2d("sound/enemyBlast.mp3", true);
	

	isLive = false;
	//播放死亡动画的时候需要关闭子弹调度器
	unschedule(schedule_selector(Enemy::shoot));
	if (enemyType >= Boss1) {
		unschedule(schedule_selector(Enemy::createProp));
		unschedule(schedule_selector(Enemy::fastShootUpdate));
	}
	
	//创建图片收集者
	Animation* ani = Animation::create();
	char filename[50];
	for (int i = 1; i <= 6; i++) {
		sprintf_s(filename, "image/blast/blast_2_%d.png", i);
		ani->addSpriteFrameWithFile(filename);
	}
	//间隔时间
	ani->setDelayPerUnit(0.2f);
	//开启动画
	Animate* animate = Animate::create(ani);

	CallFunc* callFuncAct = CallFunc::create([this]() {
		EnemyManager::getInstance()->collection(this);
		//关闭爆炸音效
		//AudioEngine::stop(blastEff);
	});

	//创建序列动作
	Sequence* seqAct = Sequence::create(animate, callFuncAct, nullptr);

	this->runAction(seqAct);
}

/*
	射击调度器
*/
void Enemy::shoot(float dt) {
	float y = getPositionY();
	y = y + 30 * dt;
	//创建子弹
	//Bullet* bullet = Bullet::create(ENEMY, Missile);
	Vec2 newDir = heroPos - Vec2(getPositionX(), getPositionY() - 50);
	newDir = newDir.getNormalized();
	Bullet* bullet = BulletFactory::createBullet(EnemyBullet, newDir);
	bullet->shootSound();
	//设置子弹的位置:敌机的坐标 + 敌机图片高度的一半
	bullet->setPosition(Vec2(getPositionX(), getPositionY() - 50));
	//设置子弹的方向
	//bullet->setRotation(180);

	//bullet->setDir(newDir);
	_parent->addChild(bullet);
	//将子弹添加到管理类中
	BulletManager::getInstance()->addEnemyBullet(bullet);
}

/*
	创建敌机血条
*/
void Enemy::createEnemyBlood() {
	auto size = getContentSize();
	auto sprite = Sprite::create("image/ui/bar.png");   //创建进度框
	sprite->setPosition(Point(size.width / 2, size.height + 5)); //设置框的位置
	sprite->setTag(9);
	this->addChild(sprite);            //加到默认图层里面去

	auto sprBlood = Sprite::create("image/ui/blood.png");  //创建血条
	ProgressTimer * progress = ProgressTimer::create(sprBlood); //创建progress对象
	progress->setType(ProgressTimer::Type::BAR);        //类型：条状
	progress->setPosition(Point(size.width / 2, size.height + 5));

	//从右到左减少血量
	progress->setMidpoint(Point(0, 0.5));     //如果是从左到右的话，改成(1,0.5)即可
	progress->setBarChangeRate(Point(1, 0));
	progress->setTag(10);       //做一个标记
	this->addChild(progress);
	schedule(schedule_selector(Enemy::scheduleBlood), 0.1f);  //刷新函数，每隔0.1秒
}

/*
	血条检测调度器
*/
void Enemy::scheduleBlood(float dt) {
	auto bar = (Sprite*)this->getChildByTag(9);
	auto progress = (ProgressTimer *)this->getChildByTag(10);
	progress->setPercentage(( (float)hp / totalHp) * 100);  //这里是百分制显示
	if (progress->getPercentage() <= 0) {
		bar->setVisible(false);
		progress->setVisible(false);
		unschedule(schedule_selector(Enemy::scheduleBlood));
	}
}
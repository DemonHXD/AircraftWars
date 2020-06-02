#include "Enemy.h"
#include "EnemyManager.h"
#include "Bullet/Bullet.h"
#include "Bullet/BulletManager.h"
#include "bullet/BulletFactory.h"
#include "Utils/AudioUtil.h"
#include "AudioEngine.h"
using namespace experimental;
#define ENEMY -1
Enemy::Enemy(EnemyType type):enemyType(type), speed(30),isLive(true) {
	//根据不同类型的敌机设置不同的血量
	score = totalHp = hp = (type + 1) * 10;
}

Enemy::~Enemy() {

}

Enemy* Enemy::create(EnemyType type) {
	Enemy* ret = new(std::nothrow) Enemy(type);
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
		sprintf(filename, "image/enemy/enemy%d_0.png", enemyType);//输出到字符数组中：
	}
	
	if (!Sprite::initWithFile(filename))
	{
		return false;
	}
	//开启敌机飞行的调度器
	scheduleUpdate();

	createEnemyBlood();

	//开启敌机射击的调度器
	schedule(schedule_selector(Enemy::shoot), 1, -1, 1);

	//开启敌机飞行的动画
	//enemyAction();
	return true;
}

void Enemy::update(float dt) {

	if (!isLive) {
		return;
	}

	float y = getPositionY();
	y = y - dt * speed;
	setPositionY(y);

	//当超出屏幕时
	if (y < -40)
	{
		//removeFromParent();//从父节点上移除
		//将敌机从敌机管理器中移除
		EnemyManager::getInstance()->collection(this);
	}
}

/*
	敌机飞行动画
*/
void Enemy::enemyAction() {
	//创建图片收集者
	Animation* animation = Animation::create();
	if (enemyType == Enemy1 || enemyType == Enemy2)
	{
		for (int i = 0; i < 5; i++)
		{
			char filename[40];
			sprintf(filename, "image/enemy/boss%d_%d.png", enemyType, i);
			log("%s", filename);
			animation->addSpriteFrameWithFileName(filename);
		}
	}
	else if (enemyType == Enemy3 || enemyType == Enemy4)
	{
		for (int i = 0; i < 4; i++)
		{
			char filename[40];
			sprintf(filename, "image/enemy/boss%d_%d.png", enemyType, i);
			log("%s", filename);
			animation->addSpriteFrameWithFileName(filename);
		}
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
	Bullet* bullet = BulletFactory::createBullet(EnemyBullet);
	bullet->shootSound();
	//设置子弹的位置:敌机的坐标 + 敌机图片高度的一半
	bullet->setPosition(Vec2(getPositionX(), getPositionY() + 20));
	//设置子弹的方向
	bullet->setRotation(180);
	bullet->setDir(Vec2(0, -1));
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
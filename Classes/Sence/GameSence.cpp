#include "GameSence.h"
#include "Bg/Bg.h"//引用头文件
#include "Hero/Hero.h"
#include "Bg/test.h"
#include "Enemy/Enemy.h"
#include "Enemy/EnemyManager.h"
#include "Bullet/BulletManager.h"
#include "Prop/PorpManager.h"
#include "Prop/Porp.h"
#include "Utils/AudioUtil.h"
#include "Layer/PauseLayer.h"
#include "Layer/RankLayer.h"
#include "StartSence.h"
#include "Hero/WingAircraft.h"
#include "cocostudio/CocoStudio.h"

#define HERO 50

USING_NS_CC;
/*
	1.导演:Director(单例模式)
		Director::getInstance();
	2.场景:Scene
		开始场景/加载场景/游戏场景/结束场景等；
	3.层:Layer
		游戏场景:攻击层/暂停层等;

Director extends Ref:
Scene extends Node extends Ref:
Layer extends Node extends Ref:
Cocos2d-x中的每一个元素都是以节点的形式存在:
*/

/*
调度器:处理随时间变化的过程；
例如：背景滚动/发射子弹/检测碰撞等
1.默认调度器:每一帧调用update函数(默认1秒60帧)
	实现默认调度器：
		第一步：开启默认调度器(所有继承于Node的类都可以开启调度器)
			scheduleUpdate();//Node
		第二步：重写Node的update方法;
2.自定义调度器:每隔多少s调用1次某个函数
	第一步：开启自定义调度器
		schedule();
		参数一：填要调用的函数：schedule_selector(类名::函数名)
		参数二：间隔时间
		参数三：重复次数,如果要一直重复，则填CC_REPEAT_FOREVER或者-1
		参数四：第一次调用前的等待时间
	第二步：写一个方法，返回值为void，形参为float类型；
3.单次调度器:延时调用某个函数（单次）
	第一步：开启单次调度器
		scheduleOnce();
			参数一：填要调用的函数：schedule_selector(类名::函数名)
			参数二：延时的时间
	第二步：写一个方法，返回值为void，形参为float类型；

关闭调度器:
unschedule():关闭自定义调度器
	参数：要取消调用的函数:schedle_selector(类名::函数名)
unscheduleUpdate:关闭默认调度器
unscheduleAllCallbacks:关闭所有调度器
*/

/*
作业:
1.实现背景滚动
2.实现英雄从屏幕的左边移动到右边，翻转，移动到最左端，来回移动；

选做 3.太阳系系统：太阳/地球/月球

作业:
1.散弹
选做：散弹与普通发射进行切换

作业：
1.完成敌机的创建和管理
2.选做:创建敌机的概率(0:50%  1:35%  2:15%)
*/

/*
	回顾:
	1.背景滚动
	2.主机移动（触摸监听）
	3.主机发射子弹（调度器）
	4.创建敌机（自定义调度器）
	5.子弹与敌机的碰撞检测（链表的遍历）
	6.声音

	帧动画：一帧一帧播放
	1.创建Animation:
		Animation* ani = Animation::create()
	2.添加所有的精灵帧
	for(int i = 0; i < 张数; i++)
	{
		ani->addSpriteFrameWithFile(图片路径);
	}
	3.设置播放帧动画的属性:
		1.设置间隔时间:ani->setDelayPerUnit(间隔时间)
		2.设置循环次数:ani->setLoops(循环次数);
		3.设置是否回到原始帧:ani->setRestoreOriginalFrame(true/flase);
	4.创建Animate:
		Animate* animate = Animate::create(ani);
	5.播放动作:
		节点->runAction(animate)

回调动作：CallFunc
1.写一个函数，无返回值且无参
2.CallFunc* callFunc = CallFunc::Create(CC_CALLBACK_0(类名::函数名,调用的对象));

序列动作:Sequence(动作按照前后顺序一一执行)
	必须以空结尾
	Sequence* seqAct = Sequence::create(动作1,动作2,...，nullptr)

1.所有的动作的基类:Action(类名::create)
2.执行动作:节点->runAction(Action*);
3.
	Action(动作):
		FiniteTimeAction:有限时间动作
			ActionInstant:即时动作
			ActionInterval:持续动作
4.即时动作:指能够立刻完成的动作，这类动作都会在下一帧完成,,例如设置位置/设置旋转/隐藏/显示/回调动作等
5.持续动作:指不能够立刻完成的动作，例如移动/旋转/动画/序列等
	1.属性变化动作:通过属性值的逐渐变化，来实现一个动画效果。例如MoveTo/MoveBy/RotateTo/RotateBy/ScaleTo/ScaleBy/JumpTo/JumpBy等
		（To代表最终指，By表示向量变量值）
	2.视觉特效动作:
		例如FadeIn(淡入)/FadeOut(淡出)/TintTo(颜色变化)/TintBy/Blink(闪烁)/Animate;
	3.其他动作:DelayTime(延时)/Repeat(重复)/RepeatForever(一直重复)
	4.复合动作(必须以nullptr结尾):
		1.序列动作Sequence:动作按照顺序有序执行
		2.组合动作Spawn:动作同时执行
6.clone:克隆相同的动作;
	reverse:将动作翻转执行
7.停止动作：
	1.节点->stopAction(Action *);//停止某一个动作
	2.节点->stopActionByTag();//通过标签停止动作
	3.节点->stopAllActions();//通知所有动作

作业：实现不同敌机的不同运动路线；
*/

/*
	1.加载plist文件
		SpriteFrameCache::getInSence()->addSpriteFrameWithFile("xxx.plist","xxx.png")
	2.
*/

/*
已讲内容：
	1.调度器
	2.监听器
	3.动作
	4.声音
	5.UI系统:User Interface(用户界面)
		UI控件:按钮、文本、输入框、滚动条、滑动条、血条等
		1.头文件和命名空间
			#include "ui/CocosGUI.h"//UI头文件
			using namespace cocos2d::ui;//UI命名空间
		2.Button按钮:
			1.按钮的创建:Button* button = Button::create();
				参数:1.正常状态下的图片路径
					 2.点击状态下图片路径(可缺省，默认为放大处理)
					 3.禁用状态下的图片路径(可缺省，默认为变灰色)
					 4.图片类型   
						本地图片(默认)   Widget::TextureResType::LOCAL
						plist图片		 Widget::TextureResType::PLIST
			2.给按钮添加点击/触摸事件(区域:控件大小):
				添加点击事件:addClickEventListener(按下抬起的过程)
				添加触摸事件:addTouchEventListener(触摸开始/触摸移动/触摸结束/触摸取消)
			3.设置属性:
				1.设置是否禁用:setEnabled(true/false);
				2.设置是否吞噬触摸:setSwallowTouchs();

导演：Director::getInstance()
	1.暂停:pause();//只暂停与时间有关的内容(例如:调度器/动作等)
	2.恢复:resume();//只恢复与时间有关的内容
	3.结束:end();
*/

/*
	作业：
		1.实现加分
		2.实现开始游戏场景/结束游戏场景/进行场景之间的转换
*/

/*
	构造函数 - 析构函数 - init
	节点::create():构造(new) -- init(初始化) -- 析构函数

	新场景创建create:新场景构造 -- 新场景init -- 旧场景析构

	onEnter:当进入舞台/场景时调用(addChild)
	注意:在使用onEnter前必须先显示调用父类的onEnter;
	onExit:当退出舞台/场景的时调用(remove)
	注意:在使用onExit前必须先显示调用父类的onExit;
*/


Scene* GameSence::createScene() {
	auto scene = Scene::create();
	auto layer = GameSence::create();
	scene->addChild(layer);
	return scene;
}


GameSence::GameSence() {

}

GameSence::~GameSence() {
}

bool GameSence::init() {
	if (!Layer::init()) {
		return false;
	}

	//加载cocostudio文件
	root = CSLoader::createNode("scenes/game/layers/GameLayer.csb");
	root->setLocalZOrder(5);
	this->addChild(root);

	//给当前类设置个tag
	this->setTag(100);
	//获取窗口矩形大小(Size:width和height)
	size = Director::getInstance()->getVisibleSize();

	//给管理类的指针赋值
	bulletManager = BulletManager::getInstance();
	enemyManager = EnemyManager::getInstance();
	porpManager = PorpManager::getInstance();

	

	//创建背景
	for (int i = 0; i < 2; i++) {
		Bg* bg = Bg::create();
		float h = bg->getContentSize().height;
		bg->setPositionY(i * h);
		this->addChild(bg, -1);
	}

	//创建英雄
	Hero* hero = Hero::create(MidPlane);
	hero->setPosition(Vec2(size.width / 2, hero->getContentSize().height / 2));
	hero->setTag(HERO);
	this->addChild(hero, 2);

	//获取分数文本
	scoreText = dynamic_cast<TextAtlas*>(root->getChildByName("ScoreNumberText"));

	createUi();

	//开启创建道具调度器
	schedule(schedule_selector(GameSence::createPropSchedule), 25, -1, 0);

	//开启默认调度器
	scheduleUpdate();

	//开启创建敌机的调度器
	schedule(schedule_selector(GameSence::createEnemy), 3, -1, 1);

	//创建血条
	//LoadingBar* hpBar = LoadingBar::create("image/ui/blood.png");//1.图片路径  2.LOCAL/PLIST
	////设置百分比 
	//hpBar->setPosition(Vec2(size.width / 2, size.height / 2));
	//hpBar->setPercent(80);
	//this->addChild(hpBar);
	return true;
}

/*
	刷新分数
*/
void GameSence::addScore(int add_score) {
	//分数累加
	score += add_score;
	//修改文本的内容:设置文本的内容setString
	scoreText->setString(std::to_string(score));
}

void GameSence::onEnter() {
	//显示调用父类的onEnter
	Layer::onEnter();

	//开启背景音乐
	AudioUtil::getInstence()->gameBGMSound();
	//bgmID = AudioEngine::play2d("sound/game_music.mp3", true);
	//AudioEngine::setVolume(bgmID, 0.3);

	//自定义事件监听器
	//监听敌机死亡的消息 - 加分
	//1.添加自定义事件监听器
	_eventDispatcher->addCustomEventListener("onEnemyDeath", [this](EventCustom* event) {
		//void* userData = event->getUserData();//传递的数据:Enemy*
		//将void*转换为Enemy*
		Enemy* userData = (Enemy*)event->getUserData();
		//加分逻辑
		this->addScore(userData->getScore());
	});//1.消息的名字 2.CC_CALLBACK_1或者lambda

	//2.在对应的位置分发消息
	//_eventDispatcher->dispatchCustomEvent("onEnemyDeath");1.消息的名字 2.数据(void *)
	//resumeSchedulerAndActions();

	//创建英雄死亡的自定义监听
	_eventDispatcher->addCustomEventListener("onHeroDeath", [this](EventCustom* event) {
		Hero* userData = (Hero*)event->getUserData();
		//设置英雄的生命值 
		heroLiveCount->setString(std::to_string(userData->getLiveCount()));
		if (userData->getLiveCount() == 0) {
			userData->die();
			UserDefault::getInstance()->setIntegerForKey("score", score);
		}
	});
}

void GameSence::onExit() {
	//显示调用父类的onExit
	Layer::onExit();
	BulletManager::getInstance()->clearList();
	EnemyManager::getInstance()->clearList();
	PorpManager::getInstance()->clearList();

	//关闭声音
	//AudioEngine::stopAll();

	//移出自定义监听器
	_eventDispatcher->removeCustomEventListeners("onEnemyDeath");
	_eventDispatcher->removeCustomEventListeners("onHeroDeath");

	//发送分数给结束场景
	_eventDispatcher->dispatchCustomEvent("finalScoreDeath", this);
}

/*
	生产道具的自定义调度器
*/
void GameSence::createPropSchedule(float dt) {
	Porp* porp = Porp::create((PorpType)(rand() % 2 + 1));
	porp->setPosition(Vec2(rand() % (int)size.width, size.height + 40));
	this->addChild(porp, 10);
	PorpManager::getInstance()->addPorp(porp);
}

/*
	创建UI
*/
void GameSence::createUi() {

	//获取血量文本
	heroLiveCount = dynamic_cast<TextAtlas*>(root->getChildByName("heroHpText"));

	//暂停按钮
	Button* pauseBtn = dynamic_cast<Button*>(root->getChildByName("pauseBtn"));
	pauseBtn->setTag(100);

	//给暂停按钮添加点击事件
	pauseBtn->addClickEventListener([this, pauseBtn](Ref*){
		//背景音乐暂停
		AudioUtil::getInstence()->audioPause();
		AudioUtil::getInstence()->buttonClickSound();
		//游戏暂停
		Director::getInstance()->pause();
		//创建暂停界面
		PauseLayer* pauseLayer = PauseLayer::create(this);
		this->addChild(pauseLayer, 10);
	});

	//创建排行榜按钮
	Button* rankBtn = dynamic_cast<Button*>(root->getChildByName("rankBtn"));
	rankBtn->setTag(3);
	rankBtn->addClickEventListener([this](Ref*) {
		//背景音乐暂停
		AudioUtil::getInstence()->audioPause();
		AudioUtil::getInstence()->buttonClickSound();
		//游戏暂停
		Director::getInstance()->pause();
		//创建排行榜界面
		RankLayer* rankLayer = RankLayer::create(this);
		this->addChild(rankLayer, 10);
	});
}

/*
	自定义生产敌机的调度器
*/
void GameSence::createEnemy(float dt) {
	float x;
	x = rand() % (int)size.width;
	//创建敌机
	Enemy* enemy = Enemy::create((EnemyType)(rand() % 7));
	enemy->setPosition(Vec2(x, size.height + 50));
	this->addChild(enemy, 2);
	// 将创建的敌机添加到敌机管理类中
	EnemyManager::getInstance()->addEnemy(enemy);
}



void GameSence::update(float dt) {
	
	//检测子弹与敌机的碰撞
	collisionBulletAndEenmy();
	//检测英雄与敌机的碰撞
	//检测英雄与道具的碰撞
	collisionHeroAndProp();
	//检测英雄与敌机子弹的碰撞
	collisionHeroAndEenmyBullet();
}

/*
	英雄子弹与敌机碰撞检测
*/
void GameSence::collisionBulletAndEenmy() {
	//范围for:特点:不能在遍历的过程中删除和添加;
	//容器:(具有begin和end迭代器,且迭代器实现++)
	//for (元素类型 变量名 : 数组 / 容器名);
	for (Bullet* bullet : bulletManager->heroBulletList) {
		for (Enemy* enemy : enemyManager->enemyList) {
			//如果enemy为死亡状态
			if (!enemy->getLive()) {
				continue;
			}
			bool isCrash = bullet->getBoundingBox().intersectsRect(enemy->getBoundingBox());
			if (isCrash) {
				bullet->setLive(false);//设置子弹死亡
				enemy->hurt(bullet->getAtk());//设置敌机受伤
				break;
			}
		}
	}
}

/*
	英雄与道具碰撞检测
*/
void GameSence::collisionHeroAndProp() {
	Hero* hero = (Hero*)this->getChildByTag(HERO);
	for (Porp* porp : porpManager->porpList) {
		bool isCrash = hero->getBoundingBox().intersectsRect(porp->getBoundingBox());
		if (isCrash) {
			switch (porp->getType()) {
			case PorpType::Shield:
				//捡到防护罩道具后加一个防护罩
				hero->isOpenDefense(true);
				break;
			case PorpType::WingAir:
				//开启僚机文字动画
				porp->WingAircraftTextAct();
				//英雄开启僚机
				hero->createWingAircraft();
				break;
			}
			porp->setLive(false);//设置道具死亡
		}
	}
}

/*
	判断英雄与敌机子弹的碰撞
*/
void GameSence::collisionHeroAndEenmyBullet() {
	Hero* hero = (Hero*)this->getChildByTag(HERO);
	for (Bullet* bullet : bulletManager->enemyBulletList) {
		bool isCrash = bullet->getBoundingBox().intersectsRect(hero->getBoundingBox());
		if (isCrash) {
			bullet->setLive(false);//设置子弹死亡
			if (!hero->getShield()) {//如果没有防护罩
				//if (hero->getLiveCount() == 0) {
				//	//进入游戏结束场景
				//} else {
					//英雄死亡一次
					hero->hit();
				////}
			}
		}
	}
}

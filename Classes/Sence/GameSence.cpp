#include "GameSence.h"
#include "Bg/Bg.h"//引用头文件
#include "Hero/Hero.h"
#include "Bg/test.h"
#include "Enemy/Enemy.h"
#include "Enemy/EnemyManager.h"
#include "Bullet/BulletManager.h"
#include "Prop/propManager.h"
#include "Prop/prop.h"
#include "Utils/AudioUtil.h"
#include "Layer/PauseLayer.h"
#include "Layer/RankLayer.h"
#include "StartSence.h"
#include "Hero/WingAircraft.h"
#include "cocostudio/CocoStudio.h"
#include "Skill/SkillButton.h"
#include "Ui/JoyStick.h"

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

/*
	1.cocos2d内存管理机制:引用计数(Ref类)  面试必考题！！！
		Sprite - Node - Ref
		Layer - Node - Ref
		Scene - Node -Ref
		Director - Ref
	2.retain:引用计数+1
	  release:引用计数-1(当引用计数为0时，释放内存)
	  autoRelease:加入到自动释放池(这一帧绘制结束后所有在自动释放池里面的计数全部减1)
	  retain和releae/autoRelease必须搭配使用，否则会出现内存泄漏
	3.create:引用计数为1
		addChild():引用计数+1(调用retain())
		remove():当前节点被移出 引用计数-1(调用release())
	4.例子1：
		auto sp = Sprite::create("");//1
		这一帧结束后引用计数为？//0
		this->addChild(sp)；//报错，内存已经被释放 child != nullptr
	  例子2：
		auto sp = Sprite::create();//1
		this->addChild(sp);//2
		这一帧结束后引用计数为？//1
	  例子3：
		auto sp = Sprite::create();//1
		sp-retain();//2
		这一帧结束后引用计数为？//1
		this->addChild(sp);//2
		sp->release();//1
	  例子4:
	    auto sp= Sprite::create("");//1
		node1->addChild(sp);//2
		sp->retain();//3
		sp->removeFromParent();//2
		这一帧结束后？//1
		node2->addChild(sp);//2
		sp->release();
	  例子5:
	    auto sp = Sprite::create("");//1
		auto sp1 = Sprite::create("");//1
		sp->addChild(sp1);//sp 1/sp1 2
		sp->retain();//sp 2
		this->addChild(sp);//sp 3
		sp->removeChild(sp1);//sp 3/sp1 2
		this->removeChild(sp);//sp 2

	内存优化机制：对象池技术
		子弹工厂:BulletFactory(简单工厂)
		子弹管理:BulletManager(单例)
			成员:生存池、死亡池
			方法:1.添加子弹到生存池中，
				 2.回收子弹：从生存池到死亡池
				 3.查找死亡池中符合条件的子弹

	作业：
		1.敌机的对象池
		2.道具/技能等
*/

/*
	1.什么情况下使用虚析构？
		当父类的指针指向子类的对象释放内存时，为了调用子类的析构函数
	2.为什么要使用常引用？
		防止调用拷贝构造函数，提高效率。
		保护数据成员不被修改
	3.重载/隐藏/覆盖:
		1.函数重载：函数名相同，形参表不同(个数，类型，顺序不同)
		2.隐藏：子类与父类具有相同函数时，子类的函数会隐藏父类的函数
		3.覆盖(override)：子类重写父类的虚函数
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
	propManager = PropManager::getInstance();

	

	//创建背景
	for (int i = 0; i < 2; i++) {
		Bg* bg = Bg::create();
		float h = bg->getContentSize().height;
		bg->setPositionY(i * h);
		this->addChild(bg, -1);
	}

	//创建英雄
	hero = Hero::create();
	//hero->onHeroMoved = CC_CALLBACK_1(BulletManager::trackHero, BulletManager::getInstance());

	hero->setPosition(Vec2(size.width / 2, hero->getContentSize().height / 2));
	hero->setTag(HERO);
	this->addChild(hero, 2);

	//获取分数文本
	scoreText = dynamic_cast<TextAtlas*>(root->getChildByName("ScoreNumberText"));

	createUi();

	//开启创建道具调度器
	//schedule(schedule_selector(GameSence::createPropSchedule), 20, -1, 0);

	//开启默认调度器
	scheduleUpdate();

	//开启创建敌机的调度器
	schedule(schedule_selector(GameSence::createEnemy), 2, -1, 0);

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
	//AudioUtil::getInstence()->play();
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
		//消灭一个敌机，有五分之一的几率掉落道具
		if (rand() % 5 == 0) {
			Prop* prop = Prop::create((PropType)(rand()% 4 + 1));
			//prop->setPosition(Vec2(rand() % (int)size.width, size.height + 40));
			prop->setPosition(Vec2(userData->getPosition()));
			this->addChild(prop, 10);
			PropManager::getInstance()->addPorp(prop);
		}
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
			//关闭调度器
			unscheduleUpdate();
			userData->die();
			int maxScore = UserDefault::getInstance()->getIntegerForKey("score", 0);
			if (maxScore < score) {
				UserDefault::getInstance()->setIntegerForKey("score", score);
			}
		}
	});
}

void GameSence::onExit() {
	//显示调用父类的onExit
	Layer::onExit();
	BulletManager::getInstance()->clearList();
	EnemyManager::getInstance()->clearList();
	PropManager::getInstance()->clearList();

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
	srand(time(0));
	Prop* prop = Prop::create((PropType)(4));
	prop->setPosition(Vec2(rand() % (int)size.width, size.height + 40));
	this->addChild(prop, 10);
	PropManager::getInstance()->addPorp(prop);
}

/*
	创建UI
*/
void GameSence::createUi() {

	//获取血量文本
	heroLiveCount = dynamic_cast<TextAtlas*>(root->getChildByName("heroHpText"));

	//暂停按钮
	Button* pauseBtn = dynamic_cast<Button*>(root->getChildByName("pauseBtn"));
	//Sprite* bg_Mask = dynamic_cast<Sprite*>(root->getChildByName("bg_Mask"));
	pauseBtn->setTag(100);

	//给暂停按钮添加点击事件
	pauseBtn->addClickEventListener([this, pauseBtn](Ref*){
		AudioUtil::getInstence()->buttonClickSound();//背景音乐暂停
		PauseLayer* pauseLayer = PauseLayer::create(this);//创建暂停界面
		pauseLayer->runAct(Vec2(0, size.width), Vec2(0, 0), CallFunc::create([this]() {
			//背景音乐暂停
			//AudioUtil::getInstence()->audioPause();
			//游戏暂停
			Director::getInstance()->pause();
		}));
		this->addChild(pauseLayer, 10);
	});

	//创建排行榜按钮
	Button* rankBtn = dynamic_cast<Button*>(root->getChildByName("rankBtn"));
	//rankBtn->setTag(3);
	rankBtn->addClickEventListener([this](Ref*) {
		AudioUtil::getInstence()->buttonClickSound();
		//创建排行榜界面
		RankLayer* rankLayer = RankLayer::create();
		rankLayer->runAct(Vec2(0, size.width), Vec2(0, 0), CallFunc::create([this]() {
			//游戏暂停
			Director::getInstance()->pause();
		}));
		this->addChild(rankLayer, 10);
	});

	//创建技能按钮
	SkillButton* skill = SkillButton::create(5, "scenes/game/image/skill_1.png");
	//设置技能不可以
	//skill->setEnabled(false);
	skill->onColdBegan = [this]() { 
		bulletManager->destEnemyBullets();
		enemyManager->destEnemys();
	};
	//skill->onColdEnded = [this]() {  };

	skill->setScale(0.5, 0.5);
	skill->setPosition(Vec2(size.width - 100, 40));
	this->addChild(skill);

	//JoyStick* stick = JoyStick::create("scenes/game/image/JoyStick_Bg.png", "scenes/game/image/JoyStick.png");
	//Hero* hero = (Hero*)this->getChildByTag(HERO);
	//stick->onJoyStickMoved = CC_CALLBACK_1(Hero::move, hero);
	//stick->setPosition(Vec2(size.width - 100, 200));
	//this->addChild(stick);
}

/*
	自定义生产敌机的调度器
*/
void GameSence::createEnemy(float dt) {
	/*Hero* hero = (Hero*)this->getChildByTag(HERO);*/
	float x;
	x = rand() % (int)size.width;
	//Vec2 newDir = pos - bullet->getPosition();
	//newDir = newDir.getNormalized();
	//创建敌机
	Enemy* enemy = Enemy::create((EnemyType)(rand() % 7), hero->getPosition());

	//if (hero->getStackEnemy()) {
	//	enemy->onEnemyMoved = CC_CALLBACK_1(BulletManager::trackEnemy, BulletManager::getInstance());
	//} else {
	//	enemy->onEnemyMoved = nullptr;
	//}
	
	enemy->setPosition(Vec2(x, size.height + 50));
	this->addChild(enemy, 2);
	// 将创建的敌机添加到敌机管理类中
	EnemyManager::getInstance()->addEnemy(enemy);
}


/*
	默认调度器
*/
void GameSence::update(float dt) {
	
	//检测子弹与敌机的碰撞
	collisionBulletAndEenmy();
	//检测英雄与敌机的碰撞
	//检测英雄与道具的碰撞
	collisionHeroAndProp();
	//检测英雄与敌机子弹的碰撞
	collisionHeroAndEenmyBullet();
	//检测僚机子弹与敌机碰撞
	collisionWingAircraftAndEenmyBullet();

}

/*
	英雄子弹与敌机碰撞检测
*/
void GameSence::collisionBulletAndEenmy() {
	//范围for:特点:不能在遍历的过程中删除和添加;
	//容器:(具有begin和end迭代器,且迭代器实现++)
	//for (元素类型 变量名 : 数组 / 容器名);
	for (Bullet* bullet : bulletManager->heroLives) {
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
	//Hero* hero = (Hero*)this->getChildByTag(HERO);
	for (Prop* prop : propManager->porpList) {
		bool isCrash = hero->getBoundingBox().intersectsRect(prop->getBoundingBox());
		if (isCrash) {
			switch (prop->getType()) {
			case PropType::Shield:
				//捡到防护罩道具后加一个防护罩
				if (!hero->getShield()) {//没有防护罩的时候才添加一个
					hero->isOpenDefense(true);
				} else {
					hero->extendDefenseTime();//延长防护罩时间
				}
				break;
			case PropType::WingAir:
				//英雄开启僚机
				hero->createWingAircraft();
				break;
			case PropType::ChangeBullet:
				//英雄更改攻击方式
				hero->bulletUp();
				break;
			case PropType::Health:
				//英雄生命值+1
				hero->incHealth();
				heroLiveCount->setString(std::to_string(hero->getLiveCount()));
				break;
			}
			prop->propTextAct();
			prop->setLive(false);//设置道具死亡
		}
	}
}

/*
	判断英雄与敌机子弹的碰撞
*/
void GameSence::collisionHeroAndEenmyBullet() {
	//Hero* hero = (Hero*)this->getChildByTag(HERO);
	for (Bullet* bullet : bulletManager->enemyLives) {
		bool isCrash = bullet->getBoundingBox().intersectsRect(hero->getBoundingBox());
		if (isCrash) {
			bullet->setLive(false);//设置子弹死亡
			if (!hero->getShield()) {//如果没有防护罩
					hero->hit();
			}
		}
	}
}

/*
	检测僚机子弹与敌机碰撞
*/
void GameSence::collisionWingAircraftAndEenmyBullet() {
	for (Bullet* bullet : bulletManager->wingAircraftLives) {
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




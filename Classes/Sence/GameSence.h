#ifndef __GameSenceManager_SCENE_H__
#define __GameSenceManager_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"//UI头文件
using namespace cocos2d::ui;//UI命名空间
using namespace cocos2d;
class ShowNumberNode;
class BulletManager;
class EnemyManager;
class PropManager;
class Hero;
class GameSence : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	GameSence();
	~GameSence();



	//创建英雄UI
	void createUi();

	// implement the "static create()" method manually
	CREATE_FUNC(GameSence);

	//调度的方法
	void createEnemy(float dt);//dt:从上一次调用到这一次调用的时间

	void onEnter() override;

	void onExit() override;

	//重写update方法
	void update(float dt) override;

	//判断子弹与敌机的碰撞
	void collisionBulletAndEenmy();

	//创建道具调度器
	void createPropSchedule(float dt);

	//判断英雄与敌机子弹的碰撞
	void collisionHeroAndEenmyBullet();

	//检测英雄与道具的碰撞
	void collisionHeroAndProp();

	//检测僚机子弹与敌机碰撞
	void collisionWingAircraftAndEenmy();

	//检测技能子弹与敌机碰撞
	void collisionSkillBulletAndEenmy();

	void addScore(int add_score);

	int getScore() {
		return score;
	}

private:
	BulletManager* bulletManager;//指向子弹管理类单例的指针
	EnemyManager* enemyManager;//指向敌机管理类单例的指针
	PropManager* propManager;//指向道具管理类的单例指针
	int score = 0;
	TextAtlas* scoreText;
	TextAtlas* heroLiveCount;
	Size size;
	Node* root;
	Hero* hero;
};

#endif // __GameSenceManager_SCENE_H__

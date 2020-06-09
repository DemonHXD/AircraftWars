#pragma once
#include "cocos2d.h"
using namespace cocos2d;
enum EnemyType {
	Enemy1, Enemy2, Enemy3, Enemy4, Enemy5, Enemy6, Enemy7,
	Boss1, Boss2,Boss3, Boss4
};

class Enemy : public Sprite
{
public:
	Enemy(Vec2 heroPos, EnemyType type = Enemy1);
	~Enemy();
	static Enemy* create(EnemyType type, Vec2 heroPos);
	bool init();
	void update(float dt) override;
	void moveUpdate(float dt);
	//敌机动画
	void enemyAction();
	//敌机设计的调度器
	void shoot(float dt);
	//敌机死亡动画
	void die();
	//创建敌机血条
	void createEnemyBlood();
	//血条检测调度器
	void scheduleBlood(float dt);
	void fastShootUpdate(float dt);//快速射击
	void createProp(float dt);//创建道具
	void createShoot(float angle);

	void setLive(bool isLive)//设置isLive
	{
		this->isLive = isLive;
	}
	bool getLive()//获取isLive
	{
		return isLive;
	}
	void setHp(int hp) {
		this->hp = hp;
	}
	int getHp() {
		return hp;
	}
	int getScore() const {
		return score;
	}
	int getEnemyType()const{
		return enemyType;
	}
	void hurt(int atk)//受伤
	{
		hp -= atk;
		if (hp <= 0)//当血量<=0时,hp=0
		{
			hp = 0;
			die();
			//isLive = false;
			//unscheduleUpdate();
		}
	}
public:
	typedef std::function<void(cocos2d::Vec2, bool &)> ccEnemyMovedCallback;
	ccEnemyMovedCallback onEnemyMoved;
private:
	int hp;//血量
	int totalHp;//总血量
	bool isLive;//是否生存
	int score;//提供的分数
	//敌机类型
	EnemyType enemyType;
	//敌机移动速度
	float speed;
	Vec2 heroPos;
	bool isSkillBullet;
	Size size;
};


#include "EnemyManager.h"
#include "Enemy.h"
EnemyManager::EnemyManager() {

}

EnemyManager::~EnemyManager() {
	pInstance = nullptr;
}

EnemyManager* EnemyManager::pInstance = nullptr;

void EnemyManager::addEnemy(Enemy* enemy) {
	enemyList.push_back(enemy);
}

void EnemyManager::collection(Enemy* enemy) {
	enemyList.remove(enemy);
	enemy->removeFromParent();
}

void EnemyManager::clearList() {
	enemyList.clear();
}
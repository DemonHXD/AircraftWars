#include "PropManager.h"
#include "Prop.h"
PropManager::PropManager() {

}

PropManager::~PropManager() {
	pInstance = nullptr;
}

PropManager* PropManager::pInstance = nullptr;

void PropManager::addPorp(Prop* Prop) {
	porpList.push_back(Prop);
}

void PropManager::collection(Prop* Prop) {
	porpList.remove(Prop);
	Prop->removeFromParent();
}

void PropManager::clearList() {
	porpList.clear();
}
#include "PorpManager.h"
#include "Porp.h"
PorpManager::PorpManager() {

}

PorpManager::~PorpManager() {
	pInstance = nullptr;
}

PorpManager* PorpManager::pInstance = nullptr;

void PorpManager::addPorp(Porp* porp) {
	porpList.push_back(porp);
}

void PorpManager::collection(Porp* porp) {
	porpList.remove(porp);
	porp->removeFromParent();
}

void PorpManager::clearList() {
	porpList.clear();
}
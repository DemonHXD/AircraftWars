#ifndef __PorpManager_H__
#define __PorpManager_H__
#include <list>
using namespace std;
class Porp;
class PorpManager {
public:
	void addPorp(Porp* porp);
	void collection(Porp* porp);
	static PorpManager* getInstance() {
		if (nullptr == pInstance) {
			pInstance = new PorpManager();
		}
		return pInstance;
	}
	~PorpManager();
	void clearList();
public:
	list<Porp*> porpList;
private:
	static PorpManager* pInstance;
	PorpManager();

};
#endif // !__PorpManager_H__
#ifndef __PorpManager_H__
#define __PorpManager_H__
#include <list>
using namespace std;
class Prop;
class PropManager {
public:
	void addPorp(Prop* Prop);
	void collection(Prop* Prop);
	static PropManager* getInstance() {
		if (nullptr == pInstance) {
			pInstance = new PropManager();
		}
		return pInstance;
	}
	~PropManager();
	void clearList();
public:
	list<Prop*> porpList;
private:
	static PropManager* pInstance;
	PropManager();

};
#endif // !__PorpManager_H__
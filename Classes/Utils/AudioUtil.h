#ifndef __AudioUtil_H__
#define __AudioUtil_H__
#include "cocos2d.h"
using namespace cocos2d;
class AudioUtil {
public:
	static AudioUtil* getInstence();
	//按钮点击声音
	void buttonClickSound();
	//游戏主场景声音
	void gameBGMSound();
	//敌机射击声音
	void enemyShootSound();
	//英雄射击声音
	void heroShoottSound();
	//僚机射击声音
	void wingAirShoot();
	//敌机死亡音效
	void enemyDesyEff();

	//声音暂停
	void audioPause();

	//声音恢复
	void audioResume();

	//背景音乐的get/set
	bool getBgmAudioState() {
		return m_bgmAudioState;
	}
	void setBgmAudioState(bool audioState) {
		m_bgmAudioState = audioState;
	}

	//音效的get/set
	bool getEffAudioState() {
		return m_effAudioState;
	}
	void setEffAudioState(bool audioState) {
		m_effAudioState = audioState;
	}

	//timi提示音
	void playTimi();
private:
	//背景音乐开关
	bool m_bgmAudioState;
	//音效开关
	bool m_effAudioState;

	AudioUtil();
	static AudioUtil* instence;
};
#endif // !__AudioUtil_H__




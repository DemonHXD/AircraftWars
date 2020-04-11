#include "AudioUtil.h"
#include "AudioEngine.h"
using namespace experimental;

AudioUtil* AudioUtil::instence = nullptr;

/*
	实现单例
*/
AudioUtil* AudioUtil::getInstence() {
	if (instence == nullptr) {
		instence = new AudioUtil();
	}
	return instence;
}

AudioUtil::AudioUtil():m_bgmAudioState(true), m_effAudioState(true){

}

/*
	按钮点击声音
*/
void AudioUtil::buttonClickSound() {
	if (instence->m_effAudioState) {
		AudioEngine::play2d("sound/button.mp3");
	}
}

/*
	游戏主场景声音
*/
void AudioUtil::gameBGMSound() {
	if (instence->m_bgmAudioState) {
		AudioEngine::setVolume(AudioEngine::play2d("sound/game_music.mp3", true), 0.3);
	}
}

/*
	敌机射击声音
*/
void AudioUtil::enemyShootSound() {
	if (instence->m_effAudioState) {
		AudioEngine::setVolume(AudioEngine::play2d("sound/button.mp3"), 0.1);
	}
}

/*
	英雄射击声音
*/
void AudioUtil::heroShoottSound() {
	if (instence->m_effAudioState) {
		AudioEngine::setVolume(AudioEngine::play2d("sound/heroShoot.mp3"), 0.1);
	}
}

/*
	僚机射击声音
*/
void AudioUtil::wingAirShoot() {
	if (instence->m_effAudioState) {
		AudioEngine::setVolume(AudioEngine::play2d("sound/wingAirShoot.mp3"), 0.1);
	}
}

//敌机死亡音效
void AudioUtil::enemyDesyEff() {
	if (instence->m_effAudioState) {
		AudioEngine::setVolume(AudioEngine::play2d("sound/enemyBlast.mp3"), 0.1);
	}
}

/*
	声音暂停
*/
void AudioUtil::audioPause() {
	bool bgmState = UserDefault::getInstance()->getBoolForKey("bgmSound");
	if (bgmState) {
		AudioEngine::pauseAll();
	}
}

/*
	声音恢复
*/
void AudioUtil::audioResume() {
	bool bgmState = UserDefault::getInstance()->getBoolForKey("bgmSound");
	if (bgmState) {
		AudioEngine::resumeAll();
	}
}

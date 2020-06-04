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

AudioUtil::AudioUtil()
	:m_bgmAudioState(true), 
	m_effAudioState(true), 
	startBgmId(0), 
	gameBgmId(0),
	isPauseStartBgm(false),
	isPauseGameBgm(false){

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
void AudioUtil::playGameBgm() {
	if (instence->m_bgmAudioState && gameBgmId == 0) {
		gameBgmId = AudioEngine::play2d("sound/game_music.mp3", true);
		AudioEngine::setVolume(gameBgmId, 0.1);
	} else if (instence->m_bgmAudioState && gameBgmId != 0 && isPauseGameBgm) {
		AudioEngine::resume(gameBgmId);
		isPauseGameBgm = false;
	}
}

void AudioUtil::stopGameBgm() {
	AudioEngine::pause(gameBgmId);
	isPauseGameBgm = true;
}

void AudioUtil::playStartBgm() {
	if (instence->m_bgmAudioState && startBgmId == 0) {
		startBgmId = AudioEngine::play2d("sound/start_bg.mp3", true);
		AudioEngine::setVolume(startBgmId, 0.1);
	} else if (instence->m_bgmAudioState && startBgmId != 0 && isPauseStartBgm) {
		AudioEngine::resume(startBgmId);
		isPauseStartBgm = false;
	}
}

void AudioUtil::stopStartBgm() {
	AudioEngine::pause(startBgmId);
	isPauseStartBgm = true;
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
		AudioEngine::setVolume(AudioEngine::play2d("sound/heroShoot.mp3"), 0.01);
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

void AudioUtil::playTimi() {
	if (instence->m_effAudioState) {
		AudioEngine::setVolume(AudioEngine::play2d("sound/timi.mp3"), 0.5);
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

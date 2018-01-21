/*
 * AudioEngine.h
 *
 *  Created on: Jul 29, 2015
 *      Author: Robert
 */

#pragma once

#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>

namespace SnowEngine
{

class SoundEffect
{
public:
	friend class AudioEngine;

	void play(int loops = 0);
private:
	Mix_Chunk* m_chunk = nullptr;
};

class Music
{
public:
	friend class AudioEngine;

	void play(int loops = -1);
	static void stop();
	static void pause();
	static void resume();
private:
	Mix_Music* m_music = nullptr;
};

class AudioEngine
{
public:
	AudioEngine();
	~AudioEngine();

	void init();
	void destroy();

	SoundEffect* loadSoundEffect(const std::string& filePath);
	Music* loadMusic(const std::string& filePath);
private:
	bool m_isInitalized = false;
	std::map<std::string, SoundEffect> m_effectMap;
	std::map<std::string, Music> m_musicMap;
};

} /* namespace SnowEngine */

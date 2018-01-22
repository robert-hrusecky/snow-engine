/*
 * AudioEngine.cpp
 *
 *  Created on: Jul 29, 2015
 *      Author: Robert
 */

#include "AudioEngine.h"

#include "errors.h"

namespace SnowEngine
{

void SoundEffect::play(int loops)
{
	if (Mix_PlayChannel(-1, m_chunk, loops) == -1)
	{
		if (Mix_PlayChannel(0, m_chunk, loops) == -1)
		{
			fatalError("Mix_PlayChannel error: " + std::string(Mix_GetError()));
		}
	}
}

void Music::play(int loops)
{
	if (Mix_PlayMusic(m_music, loops) == -1)
	{
		fatalError("Mix_PlayMusic error: " + std::string(Mix_GetError()));
	}
}

void Music::stop()
{
	Mix_HaltMusic();
}

void Music::pause()
{
	Mix_PauseMusic();
}

void Music::resume()
{
	Mix_ResumeMusic();
}

AudioEngine::AudioEngine()
{
	// TODO Auto-generated constructor stub

}

AudioEngine::~AudioEngine()
{
	destroy();
}

void AudioEngine::init()
{
	if (m_isInitalized)
	{
		fatalError("SDL_mixer was already initialized");
	}

	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1)
	{
		fatalError("Mix_Init error: " + std::string(Mix_GetError()));
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		fatalError("Mix_OpenAudio error: " + std::string(Mix_GetError()));
	}

	m_isInitalized = true;
}

void AudioEngine::destroy()
{
	if (m_isInitalized)
	{
		m_isInitalized = false;

		for (auto& it : m_effectMap)
		{
			Mix_FreeChunk(it.second.m_chunk);
		}

		for (auto& it : m_musicMap)
		{
			Mix_FreeMusic(it.second.m_music);
		}

		Mix_CloseAudio();
		Mix_Quit();
	}
}

SoundEffect* AudioEngine::loadSoundEffect(const std::string& filePath)
{
	auto it = m_effectMap.find(filePath);

	if (it == m_effectMap.end())
	{
		SoundEffect effect;
		effect.m_chunk = Mix_LoadWAV(filePath.c_str());
		if (effect.m_chunk == nullptr)
		{
			fatalError("Mix_LoadWav error: " + std::string(Mix_GetError()));
		}
		m_effectMap[filePath] = effect;
		return &m_effectMap[filePath];
	}
	return &it->second;
}

Music* AudioEngine::loadMusic(const std::string& filePath)
{
	auto it = m_musicMap.find(filePath);

	if (it == m_musicMap.end())
	{
		Music music;
		music.m_music = Mix_LoadMUS(filePath.c_str());
		if (music.m_music == nullptr)
		{
			fatalError("Mix_LoadMUS error: " + std::string(Mix_GetError()));
		}
		m_musicMap[filePath] = music;
		return &m_musicMap[filePath];
	}
	return &it->second;
}

} /* namespace SnowEngine */

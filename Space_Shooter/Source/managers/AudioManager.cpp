#include "pch.h"
#include "AudioManager.h"
#include "Dispatcher.h"


AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}

void AudioManager::Init()
{
	Dispatcher::GetInstance().Subscribe(eEvent::PlayerDeath, this);
	Dispatcher::GetInstance().Subscribe(eEvent::EnemyDeath, this);
}

void AudioManager::Recieve(const Event& aEvent)
{
	switch (aEvent.GetEventType())
	{
	case eEvent::PlayerDeath:
	case eEvent::EnemyDeath:
		PlayDeathSound();
		break;
	}
}

void AudioManager::PlayDeathSound()
{

}
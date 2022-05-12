#pragma once
#include "ResourceManager.hpp"
#include "Subscriber.h"


class AudioManager : public Subscriber
{
public:
	AudioManager();
	~AudioManager();

	void		 Init();
	virtual void Recieve(const Event& aEvent) override;


private:
	/* - Methods - */
	void PlayDeathSound();


	// TODO: Must  link OpenAL32.dll dynamically because of its license...
	//ResourceManager<sf::SoundBuffer, std::string>	m_sounds;
};
#pragma once

// project includes
#include "GridObject.h"
#include <SFML/Audio.hpp>

class Player : public GridObject
{

	  // functions
public:
	Player();

	
	// overriding Methods
	virtual void Input(sf::Event _gameEvent);
	virtual void Update(sf::Time _frameTime);


private:

	bool AttemptMove(sf::Vector2i _direction);

	// Data

private:

	sf::Vector2i m_pendingMove;
	sf::Sound m_sound;
	sf::Sound m_bumpSound;

};
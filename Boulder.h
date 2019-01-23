#pragma once

#include "GridObject.h"

class Boulder : public GridObject
{

public:
	Boulder();

	
	bool AttemptPush(sf::Vector2i _direction);
	void Update(sf::Time _frameTime);

private:
	
	bool AttemptFall(sf::Vector2i _direction);
	

	sf::Vector2i m_pendingFall;
	float m_secondsPerFall;
	bool m_IsFalling;
};
#pragma once

#include "GridObject.h"

class Boulder : public GridObject
{

public:
	Boulder();

	
	bool AttemptPush(sf::Vector2i _direction);

private:
	void Update(sf::Time _frameTime);
	bool AttemptFall(sf::Vector2i _direction);
	//bool IsFalling();

	sf::Vector2i m_pendingFall;
	float m_secondsPerFall;
	bool m_IsFalling;
};
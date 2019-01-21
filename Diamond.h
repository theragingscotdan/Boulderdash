#pragma once

// project includes
#include "GridObject.h"

class Diamond : public GridObject
{

public:
	Diamond();

private:
	void Update(sf::Time _frameTime);
	bool AttemptFall(sf::Vector2i _direction);

	sf::Vector2i m_pendingFall;
	float m_secondsPerFall;
	bool m_IsFalling;
};
#pragma once

#include "GridObject.h"

class Boulder : public GridObject
{

public:
	Boulder();

private:
	void Update(sf::Time _frameTime);
	bool AttemptFall(sf::Vector2i _direction);

	sf::Vector2i m_pendingFall;
	float m_secondsPerFall;
};
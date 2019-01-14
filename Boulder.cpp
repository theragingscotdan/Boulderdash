// project includes
#include "Boulder.h"
#include "Framework/AssetManager.h"
#include "Level.h"
#include "Player.h"

Boulder::Boulder()
	: GridObject()
	, m_pendingFall(0, 0)
	, m_secondsPerFall(0)
	, m_IsFalling(true)
	
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/boulder.png"));

	m_blocksMovement = true;
}

bool Boulder::AttemptPush(sf::Vector2i _direction)
{
	// attempt to move the box in the given direction

	// Get current position
	//Calculate target position
	sf::Vector2i targetPos = m_gridPosition + _direction;

	// check if the space is empty
	std::vector<GridObject*> targetCellContents = m_level->GetObjectAt(targetPos);

	// Check if any of those objects block movement
	bool blocked = false;
	for (int i = 0; i < targetCellContents.size(); ++i)
	{
		if (targetCellContents[i]->GetBlocksMovement() == true)
		{
			blocked = true;

		}

	}
	if (blocked == false)
	{
		bool moveSucceeded = m_level->MoveObjectTo(this, targetPos);


		return moveSucceeded;
	}
}

void Boulder::Update(sf::Time _frameTime)
{
	m_secondsPerFall += _frameTime.asSeconds();
	// If we have movement waiting to be processed,
	if (m_secondsPerFall > 1.5f)
	{
		// move in that direction
		bool moveSuccessful = AttemptFall(sf::Vector2i(0, 1));

		m_secondsPerFall = 0;

/*


			// and clear the pending movement
			m_pendingFall = sf::Vector2i(0, 0);


		} */
	}
}

bool Boulder::AttemptFall(sf::Vector2i _direction)
{
	// Attempting to move in the given direction

	// Get current position
	//Calculate target position
	sf::Vector2i targetPos = m_gridPosition + _direction;
	
	// TODO: check if the space is empty
	// Get list of objects in our target position
	std::vector<GridObject*> targetCellContents = m_level->GetObjectAt(targetPos);

	// Check if any of those objects block movement
	bool blocked = false;
	GridObject* blocker = nullptr;

	for (int i = 0; i < targetCellContents.size(); ++i)
	{
		if (targetCellContents[i]->GetBlocksMovement() == true)
		{
			blocked = true;
			blocker = targetCellContents[i];
		}

	}

	// If empty, move there
	if (blocked == false)
		return m_level->MoveObjectTo(this, targetPos);

	else
	
	return false;
}

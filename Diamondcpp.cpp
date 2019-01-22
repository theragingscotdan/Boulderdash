// project includes
#include "Diamond.h"
#include "Level.h"
#include "Player.h"
#include "Framework/AssetManager.h"


Diamond::Diamond()
	: GridObject()
	, m_pendingFall(0, 0)
	, m_secondsPerFall(0)
	, m_IsFalling(true)
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/diamond.gif"));
	m_blocksMovement = true;
}

void Diamond::Update(sf::Time _frameTime)
{
	m_secondsPerFall += _frameTime.asSeconds();
	// If we have movement waiting to be processed,
	if (m_secondsPerFall > 1.5f)
	{
		// move in that direction
		bool moveSuccessful = AttemptFall(sf::Vector2i(0, 1));

		m_secondsPerFall = 0;

		
	}
}

bool Diamond::AttemptFall(sf::Vector2i _direction)
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
	{
		Player* castPlayer = dynamic_cast <Player*>(blocker);

		// only do the thing if player is not null
		if (castPlayer != nullptr)
		{
			//  we were touch by the player

			// KILL THEM!!!!!!! 
			m_level->ReloadLevel();
			return true;
		}
	}

		return false;
}
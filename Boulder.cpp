// project includes
#include "Boulder.h"
#include "Framework/AssetManager.h"
#include "Level.h"
#include "Diamond.h"
#include "Player.h"
#include "Dirt.h"

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
		else
		{
			Boulder* castBoulder = dynamic_cast<Boulder*>(blocker); //cast to a boulder
			Diamond* castDiamond = dynamic_cast<Diamond*>(blocker);
			Dirt* castDirt = dynamic_cast<Dirt*>(blocker);

			if (castBoulder != nullptr && _direction == sf::Vector2i(0,1))
			{
				bool moveSuccessful = AttemptFall(sf::Vector2i(1, 1));
				return true;

			}
			else
			{
				if (castBoulder != nullptr && _direction == sf::Vector2i(1, 1))
				{
					bool moveSuccessful = AttemptFall(sf::Vector2i(-1, 1));
					return true;
				}
				else
					return false;
			}
			
			

			
			
			
		}
	}
	
			
	return false;
}

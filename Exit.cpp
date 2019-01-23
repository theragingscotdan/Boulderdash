#include "Exit.h"
#include "Framework/AssetManager.h"
#include "Player.h"
#include "Level.h"

Exit::Exit()
	: GridObject()
		
{
	
	m_sprite.setTexture(AssetManager::GetTexture("graphics/DoorClosed.png"));

	m_blocksMovement = true;

}

void Exit::Update(sf::Time _frameTime)
{
	// if not nullptr
	if (m_level != nullptr)
	{
		// pointer to GetIsOpen within level
		bool haveOpen = m_level->GetIsOpen();
		// if the door is open
		if (haveOpen == true)
		{
			// change the texture of the exit
			m_sprite.setTexture(AssetManager::GetTexture("graphics/DoorOpen.png"));
		}
	}
}

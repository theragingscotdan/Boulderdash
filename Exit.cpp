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
	if (m_level != nullptr)
	{
		bool haveOpen = m_level->GetIsOpen();
		if (haveOpen == true)
		{
			m_sprite.setTexture(AssetManager::GetTexture("graphics/DoorOpen.png"));
		}
	}
}

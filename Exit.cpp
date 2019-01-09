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


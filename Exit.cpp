#include "Exit.h"
#include "Framework/AssetManager.h"
#include "Player.h"

Exit::Exit()
	: GridObject()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/DoorClosed.png"));

	m_blocksMovement = true;
}

void Exit::Collide(GameObject& _collider)
{
	Player* castPlayer = dynamic_cast <Player*>(&_collider);

	// only do the thing if player is not null
	if (castPlayer != nullptr)
	{
		//  we were touch by the player

		/*// if the player has the key
		if (castPlayer->GetKey())
		{
			castPlayer->AdvanceLevel();
		}
		*/
	}
}

// project includes
#include "Boulder.h"
#include "Framework/AssetManager.h"

Boulder::Boulder()
	: GridObject()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/boulder.png"));
}
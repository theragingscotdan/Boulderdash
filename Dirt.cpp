// includes

#include "Dirt.h"
#include "Framework/AssetManager.h"

Dirt::Dirt()
	:GridObject()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/ground.png"));
	m_blocksMovement = false;
};
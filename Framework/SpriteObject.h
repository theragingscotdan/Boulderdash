#pragma once

// project includes
#include "GameObject.h"

class SpriteObject 
	: public GameObject 
	// the ": public" means this inherits from any class names that follow
{
public:

	SpriteObject();


	// overriding methods
	void Draw(sf::RenderTarget& _target);
	sf::FloatRect GetBounds();
	virtual void SetPosition(sf::Vector2f _position);
	virtual void SetPosition(float _x, float _y);
	virtual sf::Vector2f GetPosition();

protected: // this means derived/child classes can access

	sf::Sprite m_sprite;
};
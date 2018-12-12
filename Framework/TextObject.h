#pragma once

// project includes
#include "GameObject.h"

class TextObject
	: public GameObject
	// the ": public" means this inherits from any class names that follow
{
public:

	TextObject();


	// overriding methods
	void Draw(sf::RenderTarget& _target);

protected: // this means derived/child classes can access

	sf::Text m_Text;
};
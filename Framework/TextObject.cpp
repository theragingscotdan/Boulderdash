// project includes
#include "TextObject.h"

TextObject::TextObject()
	: GameObject() // always initialise your parent inside your constructor
	, m_Text()
{

}

void TextObject::Draw(sf::RenderTarget& _target)
{
	_target.draw(m_Text);
}
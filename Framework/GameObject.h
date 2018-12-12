#pragma once
 //library includes
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	GameObject();

	// these will be very simple or empty fuctions
	// that can be overridden in derived classes
	virtual void Draw(sf::RenderTarget& _target);
	virtual void Update(sf::Time _frameTime);
	virtual void Input(sf::Event _gameEvent);
	virtual sf::FloatRect GetBounds();
	virtual void Collide(GameObject& _collider);
	virtual void SetPosition(sf::Vector2f _position);
	virtual void SetPosition(float _x, float _y);
	virtual sf::Vector2f GetPosition();

	bool IsActive();

protected:

	bool m_active;
};



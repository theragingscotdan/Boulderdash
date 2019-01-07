#pragma once

// library includes 
#include <SFML/Graphics.hpp>

// project includes
#include "GridObject.h"

class Level
{

public:

	Level();

	void Draw(sf::RenderTarget& _target);
	void Update(sf::Time _frameTime);
	void Input(sf::Event _gameEvent);

	void LoadLevel(int _levelToLoad);
	void ReloadLevel();
	void LoadNextLevel();

	float GetCellSize();
	bool MoveObjectTo(GridObject* _toMove, sf::Vector2i _targetPos);

	bool DeleteObject(GridObject* _toMove);
	std::vector < GridObject* > GetObjectAt(sf::Vector2i _targetPos);

	bool CheckComplete();

private:

	const float m_cellSize;
	int m_currentLevel;
	int m_pendingLevel;
	std::vector< std::vector< sf::Sprite > > m_background;
	std::vector< std::vector< std::vector< GridObject* > >  > m_contents;
	

};
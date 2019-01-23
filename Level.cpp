// project includes
#include "Level.h"
#include "Framework/AssetManager.h"
#include "Wall.h"
#include "Dirt.h"
#include "Player.h"
#include "Diamond.h"
#include "Boulder.h"
#include "Exit.h"

// library includes
#include <iostream>
#include <fstream>

Level::Level()
	: m_cellSize(64.0f)
	, m_currentLevel(0)
	, m_pendingLevel(0)
	, m_background()
	, m_contents()
	, m_IsOpen(false)
	
	
{
	LoadLevel(1);
	
}
void Level::Draw(sf::RenderTarget& _target)
{
	// Create and update camera
	sf::View camera = _target.getDefaultView();

	// Adjust camera as needed
	camera.setCenter(m_background[0].size() * m_cellSize / 2 ,m_background.size() * m_cellSize / 2 );
	
	// Draw game world to the window
	_target.setView(camera);
	// TODO: Draw game objects
	for (int y = 0; y < m_background.size(); ++y)
	{
		for (int x = 0; x < m_background[y].size(); ++x)
		{
			_target.draw(m_background[y][x]);
		}
	}

	// rows
	for (int y = 0; y < m_contents.size(); ++y)
	{
		// cells
		for (int x = 0; x < m_contents[y].size(); ++x)
		{
			// sticky outie (grid objects)
			for (int z = 0; z < m_contents[y][x].size(); ++z)
			{
				m_contents[y][x][z]->Draw(_target);
			}
		}
	}

	
	// Reset view
	_target.setView(_target.getDefaultView());

}
void Level::Update(sf::Time _frameTime)
{
	for (int y = 0; y < m_contents.size(); ++y)
	{
		// cells
		for (int x = 0; x < m_contents[y].size(); ++x)
		{
			// sticky outie (grid objects)
			for (int z = 0; z < m_contents[y][x].size(); ++z)
			{
				m_contents[y][x][z]->Update(_frameTime);
			}
		}
	}
	// IF there is a pending level waiting... 
	if (m_pendingLevel != 0)
	{
		// load it
		LoadLevel(m_pendingLevel);
		// remove pending level
		m_pendingLevel = 0;
	}

}

void Level::Input(sf::Event _gameEvent)
{
	for (int y = 0; y < m_contents.size(); ++y)
	{
		// cells
		for (int x = 0; x < m_contents[y].size(); ++x)
		{
			// sticky outie (grid objects)
			for (int z = 0; z < m_contents[y][x].size(); ++z)
			{
				m_contents[y][x][z]->Input(_gameEvent);
			}
		}
	}
}

void Level::LoadLevel(int _levelToLoad)
{
	// clean up the old level

	// delete any data already in the level
	// rows
	for (int y = 0; y < m_contents.size(); ++y)
	{
		// cells
		for (int x = 0; x < m_contents[y].size(); ++x)
		{
			// sticky outie (grid objects)
			for (int z = 0; z < m_contents[y][x].size(); ++z)
			{
				delete m_contents[y][x][z];
			}
		}
	}

	// clear out our lists
	m_background.clear();
	m_contents.clear();


	// set the current level
	m_currentLevel = _levelToLoad;

	// set up the new level

	// Open our file for reading
	std::ifstream inFile;
	std::string fileName = "levels/Level" + std::to_string(m_currentLevel) + ".txt";
	inFile.open(fileName);

	// make sure the file was open
	if (!inFile)
	{
		std::cerr << "Unable to open file" + fileName;
		exit(1); // call system to stop program with error
	}

	// set the starting x and y coordinates used to position level objects
	int x = 0;
	int y = 0;

	// create the first row in our grid
	m_background.push_back(std::vector<sf::Sprite>());
	m_contents.push_back(std::vector<std::vector<GridObject*> >());
	
	// read each character one by one from the file
	char ch;
	// each time, try to read the next character
	// if sucessful, execute body of loop
	// the "noskipws" means our input from file will include
	// the white space (space and new lines)

	while (inFile >> std::noskipws >> ch)
	{
		// perform actions based on what character was read in

		if (ch == ' ')
		{
			++x;
		}
		else if (ch == '\n')
		{
			++y;
			x = 0;

			// create a new row in our grid
			m_background.push_back(std::vector<sf::Sprite>());
			m_contents.push_back(std::vector<std::vector<GridObject*> >());


		}
		else
		{
			// this is going to be some object or empty space
			// create background sprite
			m_background[y].push_back(sf::Sprite(AssetManager::GetTexture("graphics/ground.png")));
			m_background[y][x].setPosition(x*m_cellSize, y*m_cellSize);

			// create an empty vector for our grid contents in this cell
			m_contents[y].push_back(std::vector<GridObject*>());

			if (ch == '-')
			{
				// do no - empty space
			}
			else if (ch == 'W')
			{
				Wall* wall = new Wall();
				wall->SetLevel(this);
				wall->SetGridPosition(x, y);
				m_contents[y][x].push_back(wall);
			}
			else if (ch == 'P')
			{
				Player* player = new Player();
				player->SetLevel(this);
				player->SetGridPosition(x, y);
				m_contents[y][x].push_back(player);
			}
			else if (ch == 'm')
			{
				Dirt* dirt = new Dirt();
				dirt->SetLevel(this);
				dirt->SetGridPosition(x, y);
				m_contents[y][x].push_back(dirt); 
			} 
			else if (ch == 'G')
			{
				Diamond* diamond = new Diamond();
				diamond->SetLevel(this);
				diamond->SetGridPosition(x, y);
				m_contents[y][x].push_back(diamond);
			}
			else if (ch == 'R')
			{
				Boulder* boulder = new Boulder();
				boulder->SetLevel(this);
				boulder->SetGridPosition(x, y);
				m_contents[y][x].push_back(boulder);
			}
			else if (ch == 'E')
			{
				Exit* exit = new Exit();
				exit->SetLevel(this);
				exit->SetGridPosition(x, y);
				m_contents[y][x].push_back(exit);
			}
			else
			{
				std::cerr << "Unrecognised character in level file: " << ch;
			}
		}


	}

	// close the file now that we are done with it
	inFile.close();
			
	
	// score - position not dependant on level
	
}

void Level::ReloadLevel()
{
	m_pendingLevel = m_currentLevel;
	m_IsOpen = false;
}

void Level::LoadNextLevel()
{
	LoadLevel(m_currentLevel + 1);
	m_IsOpen = false;
}

float Level::GetCellSize()
{
	return m_cellSize;
}

bool Level::MoveObjectTo(GridObject* _toMove, sf::Vector2i _targetPos)
{
	// don't trust other code
	// make sure _toMove is a valid pointer
	// also check our target position is within the grid
	if (_toMove != nullptr
		&& _targetPos.y >= 0 && _targetPos.y < m_contents.size()
		&& _targetPos.x >= 0 && _targetPos.x < m_contents[_targetPos.y].size())
	{
		// get the current position of the grid object
		sf::Vector2i oldPos = _toMove->GetGridPosition();

		// find the object in the list using an iterator and the find method
		auto it = std::find(m_contents[oldPos.y][oldPos.x].begin(),
							m_contents[oldPos.y][oldPos.x].end(), _toMove);
		
		// if we found the object at this location, 
		// it will NOT equal the end of the vector
		if (it != m_contents[oldPos.y][oldPos.x].end())
		{
			// we found the object!

			// remove it from the old position
			m_contents[oldPos.y][oldPos.x].erase(it);

			// add it to its new position
			m_contents[_targetPos.y][_targetPos.x].push_back(_toMove);

			// tell the object its new position
			_toMove->SetGridPosition(_targetPos);

			// return sucess
			return true;

		}
	}
	// return failure
	return false;
}

bool Level::DeleteObject(GridObject* _toDelete)
{
	// if the player walks onto a dirt
	if (_toDelete != nullptr)
		
	{
		
		// get the current position of the grid object
		sf::Vector2i oldPos = _toDelete->GetGridPosition();

			// find the object in the list using an iterator and the find method
			auto it = std::find(m_contents[oldPos.y][oldPos.x].begin(),
				m_contents[oldPos.y][oldPos.x].end(), _toDelete);

			// if we found the object at this location, 
			// it will NOT equal the end of the vector
			if (it != m_contents[oldPos.y][oldPos.x].end())
			{
				// we found the object!

				// remove it from the old position
				m_contents[oldPos.y][oldPos.x].erase(it);

				delete _toDelete;
				
			
				// return sucess
				return true;

			}

	}

	
	return false;
} 

std::vector < GridObject* > Level::GetObjectAt(sf::Vector2i _targetPos)
{
	// don't trust the data!
	// make sure the coordinates are within the vector size
	if (_targetPos.y >= 0 && _targetPos.y < m_contents.size()
		&& _targetPos.x >= 0 && _targetPos.x < m_contents[_targetPos.y].size())
	{
		// Get the contents
		// return them
		return m_contents[_targetPos.y][_targetPos.x];
	}

	// default return
	// return an empty vector with nothing in it
	// (default constructor)
	return std::vector<GridObject*>();
}

bool Level::CheckComplete()
{
	// loop through and check all boxes to see if see if they are stored
	// rows
	for (int y = 0; y < m_contents.size(); ++y)
	{
		// cells
		for (int x = 0; x < m_contents[y].size(); ++x)
		{
			// sticky outie (grid objects)
			for (int z = 0; z < m_contents[y][x].size(); ++z)
			{
				// current object we are examining in the loop
				GridObject* thisObject = m_contents[y][x][z];

				// check if it is a box via dynamic cast
				Diamond* diamondObject = dynamic_cast<Diamond*>(thisObject);

				if (diamondObject != nullptr)
				{
					return false;
				}
			}
		}
	}

	
	// all boxes were stored! (none we unstored
	// so we completed the level
	m_IsOpen = true;
	

	
	// The level is complete so return true
	return true;
}

bool Level::GetIsOpen()
{
	return m_IsOpen;
}

// project includes
#include "Player.h"
#include "Framework/AssetManager.h"
#include "Level.h"
#include "Dirt.h"
#include "Diamond.h"

Player::Player()
	: GridObject()
	, m_pendingMove(0, 0)
	, m_sound()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandDown.png"));
	m_sound.setBuffer(AssetManager::GetSoundBuffer("audio/footstep1.ogg"));
	m_bumpSound.setBuffer(AssetManager::GetSoundBuffer("audio/bump.wav"));
};

void Player::Input(sf::Event _gameEvent)
{
	// read the input from the keyboard and convert it
	// to a direction to move in (and then move)

	// was the event a key press?
	if (_gameEvent.type == sf::Event::KeyPressed)
	{
		// yes it was a key press!

		// what key was pressed?

		if (_gameEvent.key.code == sf::Keyboard::W)
		{
			// it was W!
			// Move up
			m_pendingMove = sf::Vector2i(0, -1);
			m_sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandUp.png"));
			
		}
		else if (_gameEvent.key.code == sf::Keyboard::A)
		{
			// it was A!
			// Move left
			m_pendingMove = (sf::Vector2i(-1, 0));
			m_sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandLeft.png"));
		}
		else if (_gameEvent.key.code == sf::Keyboard::S)
		{
			// it was S!
			// Move down
			m_pendingMove = (sf::Vector2i(0, 1));
			m_sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandDown.png"));
		}
		else if (_gameEvent.key.code == sf::Keyboard::D)
		{
			// it was D!
			// Move right
			m_pendingMove = (sf::Vector2i(1, 0));
			m_sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandRight.png"));
		}
	}
}

void Player::Update(sf::Time _frameTime)
{
	// If we have movement waiting to be processed,
	
	if (m_pendingMove.x != 0 || m_pendingMove.y != 0)
	{
		// move in that direction
		bool moveSuccessful = AttemptMove(m_pendingMove);

		// play movement sound
		if (moveSuccessful)
		{
			m_sound.play();
		}
		
		// and clear the pending movement
		m_pendingMove = sf::Vector2i(0, 0);


	}
}

bool Player::AttemptMove(sf::Vector2i _direction)
{
	// Attempting to move in the given direction

	// Get current position
	//Calculate target position
	sf::Vector2i targetPos = m_gridPosition + _direction;


	// TODO: check if the space is empty
	// Get list of objects in our target position
	std::vector<GridObject*> targetCellContents = m_level->GetObjectAt(targetPos);

	// Check if any of those objects block movement
	bool blocked = false;
	GridObject* blocker = nullptr;

	for (int i = 0; i < targetCellContents.size(); ++i)
	{
		if (targetCellContents[i]->GetBlocksMovement() == true)
		{
			blocked = true;
			blocker = targetCellContents[i];
			m_bumpSound.play();
		}

	}


	// If empty, move there
	if (blocked == false)
		return m_level->MoveObjectTo(this, targetPos);
	else
	{
		Dirt* dirtPresent = dynamic_cast<Dirt*>(blocker);

		// if so (the thing is a box (not nullptr))
		if (dirtPresent != nullptr)
		{

			{
				// move to new spot (where blocker was)
				bool dirtDeleted = m_level->DeleteObject(dirtPresent);
				m_level->MoveObjectTo(this, targetPos);
			}

		}
		else
		{

			Diamond* diamondPresent = dynamic_cast<Diamond*>(blocker);

			// if so (the thing is a box (not nullptr))
			if (diamondPresent != nullptr)
			{


				// move to new spot (where blocker was)
				bool diamondDeleted = m_level->DeleteObject(diamondPresent);
				m_level->MoveObjectTo(this, targetPos);


			}

			// if movement is blocked, do nothing, return false
			// default

			return false;

		}
	}
}
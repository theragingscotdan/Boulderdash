// Library includes
#include <assert.h>

// project includes
#include "AssetManager.h"

// initiallise the static reference to our instance - to nullptr (aka zero)
AssetManager* AssetManager::s_instance = nullptr;


// constructor
AssetManager::AssetManager()
	: m_textures()
	, m_soundBuffers()
	, m_fonts()
{
	// throw an error and stop execution (in debug mode) if a copy of this
	// class has already been created
	assert(s_instance == nullptr);

	// assign ourselves to the instance pointer
	// - this is the new instance of the class that has just been created
	s_instance = this;

}

sf::Texture& AssetManager::GetTexture(std::string _fileName)
{
	 // create an iterator to hold a key and value pair
	// and search for the required key using the
	// passed in file name
	auto keyValuePair = s_instance->m_textures.find(_fileName);
	// "auto in this case is equivalent to writing
	// std::map<std::string,sf::Texure>::iterator
	// this keyword (auto) can be used in cases where the
	// compiler can figure out the type of a variable for you
	// YOU ARE NOT ALLOWED TO USE THIS EXCEPT FOR ITERATORS
	
	// Did we find the texture? (aka was it already loaded?)
	// (iterator wil be at the end if we did NOT find it
	if (keyValuePair != s_instance->m_textures.end())
	{
		// YES! We found it!
		return keyValuePair->second;
	}
	else
	{
		// NO! We didn't find it!

		// let's create it then!

		// Create a new key value pair using the filename
		// The subcscript [] operator creates an entry in 
		// the map if there is not already one there

		sf::Texture& texture = s_instance->m_textures[_fileName];
		// blank texture has been created
		// Now just load it from file
		texture.loadFromFile(_fileName);

		// return the texture to the calling code
		return texture;
	}
}

sf::SoundBuffer& AssetManager::GetSoundBuffer(std::string _fileName)
{
	std::map<std::string, sf::SoundBuffer>::iterator keyValuePair1 = s_instance->m_soundBuffers.find(_fileName);

	if (keyValuePair1 != s_instance->m_soundBuffers.end())
	{
		// YES! We found it!
		return keyValuePair1->second;
	}
	else
	{
		// NO! We didn't find it!

		// let's create it then!

		// Create a new key value pair using the filename
		// The subcscript [] operator creates an entry in 
		// the map if there is not already one there

		sf::SoundBuffer& soundBuffer = s_instance->m_soundBuffers[_fileName];
		// blank texture has been created
		// Now just load it from file
		soundBuffer.loadFromFile(_fileName);

		return soundBuffer;
	}
}

sf::Font& AssetManager::GetFont(std::string _fileName)
{
	std::map<std::string, sf::Font>::iterator keyValuePair = s_instance->m_fonts.find(_fileName);

	if (keyValuePair != s_instance->m_fonts.end())
	{
		return keyValuePair->second;
	}
	else
	{
		sf::Font& font = s_instance->m_fonts[_fileName];
		font.loadFromFile(_fileName);

		return font;

	}
}
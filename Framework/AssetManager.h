#pragma once

// library includes
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class AssetManager
{

public:

	// public interface/ behaviours

	// contructor
	AssetManager();


	// get a texture based on a file name
	static sf::Texture& GetTexture(std::string _fileName);
	// get a sound buffer based on a file
	static sf::SoundBuffer& GetSoundBuffer(std::string _fileName);
	// get a font based on a file name
	static sf::Font& GetFont(std::string _fileName);
	

private:

	// private data for this class

	// a pointer to the class to itself
	// for the singleton design pattern
	// the one and only instance of this class

	static AssetManager* s_instance;


	// list of Textures
	std::map<std::string, sf::Texture> m_textures;
	// list of SoundBuffers
	std::map<std::string, sf::SoundBuffer> m_soundBuffers;
	// list of Fonts
	std::map<std::string, sf::Font> m_fonts;


};
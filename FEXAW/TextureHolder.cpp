#include "TextureHolder.hpp"
#include <assert.h>

// loads a new texture into the texture map
void TextureHolder::load(Textures::ID id, const std::string& filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	if(!texture->loadFromFile(filename))
		throw std::runtime_error("TextureHolder::load - Failed to load " + filename);

	auto inserted = mTextureMap.insert(std::make_pair(id, std::move(texture)));
	assert(inserted.second);
}

// let's get a texture from our map and return the texture itself
sf::Texture& TextureHolder::get(Textures::ID id)
{
	auto found = mTextureMap.find(id);
	assert(found != mTextureMap.end());

	return *found->second;
}
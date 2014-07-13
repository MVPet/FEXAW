#ifndef _TEXTUREHOLDER
#define _TEXTUREHOLDER

#include <SFML/Graphics.hpp>
#include <memory>

namespace Textures
{
	enum ID { Stuff };
}

class TextureHolder
{

public:
	void				load(Textures::ID id, const std::string& filename);
	sf::Texture&		get(Textures::ID id);
	const sf::Texture&	get(Textures::ID id) const;

private:
	std::map<Textures::ID, std::unique_ptr<sf::Texture>> mTextureMap;
};

#endif // TextureHolder.hpp
#pragma once
#ifndef SPRITEFONT_HPP
#define SPRITEFONT_HPP

#include <map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

class SpriteFont
{
public:
    SpriteFont();

    bool load(sf::Texture& inTexure);

    const sf::IntRect& getCharRegion(char c);
    sf::Texture* getTexture() const;

    unsigned int width() const { return 8; }
    unsigned int height() const { return 8; }
private:
    std::map<char, sf::IntRect> m_charIndex;
    sf::Texture* m_spriteTex{ nullptr };

    static const char charList[];
};

#endif

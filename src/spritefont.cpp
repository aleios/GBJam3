#include "SpriteFont.hpp"

const char SpriteFont::charList[] = {
                                      'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                                      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                                      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', ',', '.', '?', '_'
                                    };

SpriteFont::SpriteFont()
{
}

bool SpriteFont::load(sf::Texture& inTex)
{
    m_spriteTex = &inTex;

    sf::Vector2u texSize = inTex.getSize();

    int texCols = texSize.x / 8;

    int idx = 0;
    for (char c : charList)
    {
        sf::IntRect texRegion;

        int tu = idx % texCols;
        int tv = idx / texCols;

        texRegion.left = (tu * 8);
        texRegion.top = (tv * 8);
        texRegion.width = 8;
        texRegion.height = 8;

        m_charIndex.insert(std::pair<char, sf::IntRect>(c, texRegion));
        ++idx;
    }

    return true;
}

sf::Texture* SpriteFont::getTexture() const
{
    return m_spriteTex;
}

const sf::IntRect& SpriteFont::getCharRegion(char c)
{
    auto it = m_charIndex.find(c);
    if (it == m_charIndex.end())
        throw 0;

    return it->second;
}
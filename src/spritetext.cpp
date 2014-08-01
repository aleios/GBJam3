#include "SpriteText.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

SpriteText::SpriteText()
{

}

void SpriteText::setString(const std::string& inStr)
{
    if (inStr.size() == 0 || inStr == m_string)
        return;

    m_string = inStr;

    updateGeometry();
}

void SpriteText::setSpriteFont(SpriteFont& inFont)
{
    m_font = &inFont;

    updateGeometry();
}

void SpriteText::updateGeometry()
{
    if (m_font == nullptr)
        return;

    m_vertices.clear();
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(m_string.size() * 4);

    sf::Vector2f position;
    int idx = 0;
    for (char c : m_string)
    {
        if (c == '\n')
        {
            position.y += m_font->height(); // Replace with something better?
            position.x = 0.0f; // Reset x position.
        }
        else if (c == ' ')
        {
            position.x += m_font->width();
        }
        else
        {
            sf::Vertex* quad = &m_vertices[idx * 4];
            sf::IntRect bounds = m_font->getCharRegion(c);

            quad[0].position = position;
            quad[0].texCoords = sf::Vector2f(bounds.left, bounds.top);

            quad[1].position = sf::Vector2f((position.x + bounds.width), position.y);
            quad[1].texCoords = sf::Vector2f((bounds.left + bounds.width), bounds.top);

            quad[2].position = sf::Vector2f((position.x + bounds.width), (position.y + bounds.height));
            quad[2].texCoords = sf::Vector2f((bounds.left + bounds.width), (bounds.top + bounds.height));

            quad[3].position = sf::Vector2f(position.x, (position.y + bounds.height));
            quad[3].texCoords = sf::Vector2f(bounds.left, (bounds.top + bounds.height));

            position.x += bounds.width;
            idx++;
        }
    }
}

void SpriteText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_font == nullptr || m_vertices.getVertexCount() <= 0)
        return;

    states.transform *= getTransform();

    states.texture = m_font->getTexture();

    target.draw(m_vertices, states);
}
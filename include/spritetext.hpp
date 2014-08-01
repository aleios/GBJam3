#pragma once
#ifndef SPRITETEXT_HPP
#define SPRITETEXT_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "SpriteFont.hpp"

class SpriteText
    : public sf::Drawable, public sf::Transformable
{
public:
    SpriteText();

    void setString(const std::string& inStr);
    void setSpriteFont(SpriteFont& inFont);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    SpriteFont* m_font{ nullptr };
    std::string m_string{ "" };

    void updateGeometry();
};

#endif

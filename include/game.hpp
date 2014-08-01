#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Game
{
public:
    Game();
    ~Game();

    void run();
private:
    void update();
    void draw();

    sf::RenderWindow m_window;

    static const int WINDOW_WIDTH{160}, WINDOW_HEIGHT{144};
};

#endif

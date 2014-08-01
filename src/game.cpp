#include <game.hpp>
#include <modstream.hpp>

Game::Game()
{

}

Game::~Game()
{

}

void Game::run()
{
    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GBJam3");
    m_window.setFramerateLimit(60);

    ModStream ms;
    ms.load("test.xm");

    ms.play();

    while(m_window.isOpen())
    {
        update();
        draw();
    }

    ms.stop();
}

void Game::update()
{
    sf::Event ev;
    while(m_window.pollEvent(ev))
    {
        if (ev.type == sf::Event::Closed)
            m_window.close();
        else if (ev.type == sf::Event::Resized)
        {
            float aspect = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT);

            int viewWidth = ev.size.width;
            int viewHeight = (int)(ev.size.width / aspect + 0.5f);

            if (viewHeight > ev.size.height)
            {
                viewHeight = ev.size.height;
                viewWidth = (int)(ev.size.height * aspect + 0.5f);
            }

            float vpx = (ev.size.width - viewWidth) / 2;
            float vpy = (ev.size.height - viewHeight) / 2;

            sf::View v = m_window.getView();
            v.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);

            sf::FloatRect viewport;

            viewport.left = vpx / ev.size.width;
            viewport.top = (ev.size.height - (vpy + viewHeight)) / ev.size.height;
            viewport.width = static_cast<float>(viewWidth) / static_cast<float>(ev.size.width);
            viewport.height = static_cast<float>(viewHeight) / static_cast<float>(ev.size.height);

            v.setViewport(viewport);

            m_window.setView(v);
        }
    }
}

void Game::draw()
{
    m_window.clear();

    m_window.display();
}

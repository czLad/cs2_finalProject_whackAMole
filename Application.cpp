#include "Application.h"
#include <iostream>
#include <SFML/Audio.hpp>
void Application::run()
{
    sf::RenderWindow window({720, 720, 32}, "WhackAMole");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    Board wAM(4, {720,720});
    RandomPatternGenerator rpg;
    rpg.setVariations(4);
    rpg.setTimeIncrement(0.6);
    int clickCount = 0;
    sf::Texture backgroundTexture;
    sf::Sprite background;
    backgroundTexture.loadFromFile("dayBackground.png");
    background.setTexture(backgroundTexture);
    background.setPosition({0, 0});
    sf::Font scoreFont;
    scoreFont.loadFromFile("arial.ttf");
    sf::Text score;
    score.setFont(scoreFont);
    score.setCharacterSize(30);
    score.setFillColor(sf::Color::Yellow);
    score.setPosition(10, 10);
    sf::Text timePassed;
    timePassed.setFont(scoreFont);
    timePassed.setCharacterSize(30);
    timePassed.setFillColor(sf::Color::White);
    timePassed.setPosition(500, 10);
    sf::Clock wAMClock;

    while(window.isOpen())
    {
        //event listener
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(sf::Event::Closed == event.type)
            {
                window.close();
            }
            wAM.eventHandler(window, event, clickCount);
        }
        if(rpg.isEnabled())
        {
            int n = rpg.getPattern();
            wAM.goUp(n);
        }
        if(clickCount >= 10 || wAMClock.getElapsedTime().asSeconds() > 10)
            wAM.showDefault();
        score.setString("Score: " + std::to_string(clickCount));
        timePassed.setString("Time: " + std::to_string(wAMClock.getElapsedTime().asSeconds()));
        window.clear();
        window.draw(background);
        window.draw(score);
        window.draw(timePassed);
        window.draw(wAM);
        window.display();
    }
}
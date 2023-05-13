#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include "Application.h"
int main()
{
    srand(time(0));
    sf::Music music;
    if (!music.openFromFile("BonJovi1.ogg"))
        std::cout<< "music";
    music.play();
    music.setLoop(true);
    Application application;
    application.run();
    return 0;
}

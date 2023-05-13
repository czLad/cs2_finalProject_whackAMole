#include "Board.h"
Board::Board()
{

}

Board::Board(int numberOfMoles, sf::Vector2f windSize)
{
    windowSize = windSize;
    column = 4;
    for(int i = 0; i < numberOfMoles; i++)
        moles.push_back(createAMole(4, column, 5));
    position();
}

void Board::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    for(int i=0; i<moles.size(); i++)
        window.draw(moles[i]);
}

AnimatedSprite Board::createAMole(int rows, int col, float speed)
{
    texture.loadFromFile("mole_edit_6.png");
    AnimatedSprite mole(texture, rows, col);
    mole.setSpeed(speed);
    mole.setScale(0.7f, 0.7f);
    return mole;
}

void Board::position()
{
    moles[3].setPosition((windowSize.x / 2), (windowSize.y / 2));
    sf::FloatRect b = moles[3].getGlobalBounds();
    moles[1].setPosition(b.top, b.top - b.width);
    moles[2].setPosition(b.left - b.width, b.top);
    moles[0].setPosition(b.left - b.width, b.top - b.width);
}

void Board::setPosition(sf::Vector2f position)
{
    moles[3].setPosition((windowSize.x / 2), (windowSize.y / 2));
    Board::position();
}

void Board::eventHandler(sf::RenderWindow& window, sf::Event event, int &clickCount)
{
    if(sf::Mouse::isButtonPressed((sf::Mouse::Left)))
    {
        sf::Vector2f  mpos = (sf::Vector2f) sf::Mouse::getPosition(window);
        for(int i = 0; i < moles.size(); i++)
        {
            if(moles[i].getGlobalBounds().contains(mpos) && moles[i].goUpIsEnabled())
            {
                clickCount++;
                break;
            }
        }
    }
    while(sf::Mouse::isButtonPressed((sf::Mouse::Left)));
}

void Board::goUp(int index)
{
    if(!stop)
    moles[index].animate();
}

void Board::showDefault()
{
    for(int i = 0; i < moles.size(); i++)
        moles[i].animateDefault();
    stop = true;
}
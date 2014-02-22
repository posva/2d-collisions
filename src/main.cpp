#include <SFML/Graphics.hpp>
#include "CollisionRectangle.hpp"
#include <iostream>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define DEG2RAD(X) (2.f*M_PI*(X)/360.f)


int main()
{
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Hello World - SFML");

    CollisionRectangle r1(glm::vec2(5,5), glm::vec2(100, 40)),
                       r2(glm::vec2(200, 100), glm::vec2(50, 120));

    r1.setOrigin(glm::vec2(50, 20));
    r2.setOrigin(glm::vec2(10, 30));

    bool choose = false;
    bool r1Col(false), r2Col(false);

    // Start the main loop
    while (App.isOpen())
    {
        // Process events
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            // Close window : exit
            if (Event.type == sf::Event::Closed || (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape))
                App.close();

            if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Space) {
                choose = !choose;
            }

            if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Return) {
                r1Col = r1.checkCollision(r2);
                r2Col = r2.checkCollision(r1);
                std::cout<<"\n";
            }

            if (Event.type == sf::Event::MouseWheelMoved) {
                if (choose)
                    r1.rotate(DEG2RAD(Event.mouseWheel.delta)*5.f);
                else
                    r2.rotate(DEG2RAD(Event.mouseWheel.delta));
            }
        }

        if (choose)
            r1.setPosition(glm::vec2(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y));
        else
            r2.setPosition(glm::vec2(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y));

        // Clear screen, and fill it with blue
        App.clear(sf::Color::Black);

        sf::ConvexShape rd1(4),
                        rd2(4);
        rd1.setOutlineColor(sf::Color::Blue);
        rd1.setFillColor(sf::Color(0.f, 0.f, 0.f, 0.f));
        rd1.setOutlineThickness(2.f);
        rd2.setOutlineColor(sf::Color::Blue);
        rd2.setFillColor(sf::Color(0.f, 0.f, 0.f, 0.f));
        rd2.setOutlineThickness(2.f);

        r1Col = r1.checkCollision(r2);
        r2Col = r2.checkCollision(r1);

        if (r1Col)
            rd1.setOutlineColor(sf::Color::Green);
        if (r2Col)
            rd2.setOutlineColor(sf::Color::Green);

        for (int i = 0; i < 4; i++) {
            rd1.setPoint(i, sf::Vector2f(r1.getVertex(i).x, r1.getVertex(i).y));
            rd2.setPoint(i, sf::Vector2f(r2.getVertex(i).x, r2.getVertex(i).y));
        }

        App.draw(rd1);
        App.draw(rd2);

        // Display the content of the window on screen
        App.display();
    }

    return 0;
}

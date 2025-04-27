#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Crawler.h"
#include "Hopper.h"
#include "KnightBug.h"

const int cellSize = 64;
const int windowSize = cellSize * 10;

void runBugLifeGUI() {
    Board board;
    board.loadBugsFromFile("all-bugs.txt");

    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Bug's Life - GUI");

    sf::Texture crawlerTexture, hopperTexture, knightTexture, superTexture;

    if (!crawlerTexture.loadFromFile("resources/crawler.png") ||
        !hopperTexture.loadFromFile("resources/hopper.png") ||
        !knightTexture.loadFromFile("resources/knightbug.png") ||
        !superTexture.loadFromFile("resources/superbug.png"))
    {
        std::cout << "Error\n";
        return;
    }


    sf::Sprite superBug(superTexture);
    superBug.setScale(
        static_cast<float>(cellSize) / superTexture.getSize().x,
        static_cast<float>(cellSize) / superTexture.getSize().y
    );
    sf::Vector2i superBugPos(5, 5);
    superBug.setPosition(superBugPos.x * cellSize, superBugPos.y * cellSize);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up && superBugPos.y > 0) superBugPos.y--;
                if (event.key.code == sf::Keyboard::Down && superBugPos.y < 9) superBugPos.y++;
                if (event.key.code == sf::Keyboard::Left && superBugPos.x > 0) superBugPos.x--;
                if (event.key.code == sf::Keyboard::Right && superBugPos.x < 9) superBugPos.x++;
                superBug.setPosition(superBugPos.x * cellSize, superBugPos.y * cellSize);


                for (auto* bug : board.getBugs()) {
                    if (bug->isAlive() && bug->getPosition().x == superBugPos.x && bug->getPosition().y == superBugPos.y) {
                        bug->setAlive(false);
                        std::cout << "SuperBug eliminated a Bug ID: " << bug->getId() << std::endl;
                    }
                }
            }
        }

        window.clear(sf::Color::White);


        for (int x = 0; x < 10; ++x) {
            for (int y = 0; y < 10; ++y) {
                sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
                cell.setPosition(x * cellSize, y * cellSize);
                cell.setFillColor((x + y) % 2 == 0 ? sf::Color(220, 220, 220) : sf::Color(255, 255, 255));
                window.draw(cell);
            }
        }


        for (const auto* bug : board.getBugs()) {
            if (!bug->isAlive()) continue;

            sf::Sprite sprite;
            if (dynamic_cast<const Crawler*>(bug)) sprite.setTexture(crawlerTexture);
            else if (dynamic_cast<const Hopper*>(bug)) sprite.setTexture(hopperTexture);
            else if (dynamic_cast<const KnightBug*>(bug)) sprite.setTexture(knightTexture);

            sprite.setScale(
                static_cast<float>(cellSize) / sprite.getTexture()->getSize().x,
                static_cast<float>(cellSize) / sprite.getTexture()->getSize().y
            );

            sprite.setPosition(bug->getPosition().x * cellSize, bug->getPosition().y * cellSize);
            window.draw(sprite);
        }


        window.draw(superBug);

        window.display();
    }
}

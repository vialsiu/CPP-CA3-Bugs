#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Crawler.h"
#include "Hopper.h"
#include "KnightBug.h"

const int cellSize = 64;
const int windowSize = cellSize * 10;

Board runBugLifeGUI() {
    Board board;
    board.loadBugsFromFile("all-bugs.txt");

    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Bug's Life - GUI");

    sf::Texture crawlerTexture, hopperTexture, knightTexture, superTexture;

    if (!crawlerTexture.loadFromFile("resources/crawler.png") ||
        !hopperTexture.loadFromFile("resources/hopper.png") ||
        !knightTexture.loadFromFile("resources/knightbug.png") ||
        !superTexture.loadFromFile("resources/superbug.png"))
    {
        std::cout << "Error loading textures\n";
        return board;
    }

    sf::Sprite superBug(superTexture);
    superBug.setScale(
        static_cast<float>(cellSize) / superTexture.getSize().x * 0.8f,
        static_cast<float>(cellSize) / superTexture.getSize().y * 0.8f
    );
    sf::Vector2i superBugPos(5, 5);
    superBug.setPosition(
        superBugPos.x * cellSize + (cellSize - superBug.getGlobalBounds().width) / 2,
        superBugPos.y * cellSize + (cellSize - superBug.getGlobalBounds().height) / 2
    );

    sf::Clock clock;
    float moveTimer = 0.f;

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

                superBug.setPosition(
                    superBugPos.x * cellSize + (cellSize - superBug.getGlobalBounds().width) / 2,
                    superBugPos.y * cellSize + (cellSize - superBug.getGlobalBounds().height) / 2
                );

                for (auto* bug : board.getBugs()) {
                    if (bug->isAlive() &&
                        bug->getPosition().x == superBugPos.x &&
                        bug->getPosition().y == superBugPos.y)
                    {
                        bug->setAlive(false);
                        std::cout << "SuperBug eliminated Bug ID: " << bug->getId() << std::endl;
                    }
                }
            }
        }

        moveTimer += clock.restart().asSeconds();
        if (moveTimer >= 3.f) {
            board.tapBoard(false);
            moveTimer = 0.f;
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
            if (bug->getType() == "Crawler") sprite.setTexture(crawlerTexture);
            else if (bug->getType() == "Hopper") sprite.setTexture(hopperTexture);
            else if (bug->getType() == "KnightBug") sprite.setTexture(knightTexture);

            sprite.setScale(
                static_cast<float>(cellSize) / sprite.getTexture()->getSize().x * 0.8f,
                static_cast<float>(cellSize) / sprite.getTexture()->getSize().y * 0.8f
            );

            int x = bug->getPosition().x;
            int y = bug->getPosition().y;

            int bugsInCell = 0;
            for (const auto* other : board.getBugs()) {
                if (other->isAlive() && other->getPosition().x == x && other->getPosition().y == y)
                    bugsInCell++;
            }

            if (bugsInCell == 1) {
                sprite.setPosition(
                    x * cellSize + (cellSize - sprite.getGlobalBounds().width) / 2,
                    y * cellSize + (cellSize - sprite.getGlobalBounds().height) / 2
                );
            } else {
                if (bug->getType() == "Crawler") {
                    sprite.setPosition(
                        x * cellSize + 5,
                        y * cellSize + 5
                    );
                } else if (bug->getType() == "Hopper") {
                    sprite.setPosition(
                        x * cellSize + cellSize / 2,
                        y * cellSize + cellSize / 2
                    );
                } else {
                    sprite.setPosition(
                        x * cellSize + (cellSize - sprite.getGlobalBounds().width) / 2,
                        y * cellSize + (cellSize - sprite.getGlobalBounds().height) / 2
                    );
                }
            }

            window.draw(sprite);
        }

        window.draw(superBug);

        window.display();
    }

    return board;
}

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 700), "Doodle Jump", sf::Style::Close);
    window.setFramerateLimit(60);
    sf::Texture backgroundTexture;
    sf::Texture playerTexture;
    sf::Texture platformTexture;
    backgroundTexture.loadFromFile("../projectsPhotos/doodle/doodlePackground.png");
    playerTexture.loadFromFile("../projectsPhotos/doodle/doodle.png");
    platformTexture.loadFromFile("../projectsPhotos/doodle/platform.png");
    sf::Sprite background(backgroundTexture);
    sf::Sprite player(playerTexture);
    sf::Sprite platform(platformTexture);

    sf::RectangleShape gameoverBackground(sf::Vector2f(500, 700));
    gameoverBackground.setFillColor(sf::Color::White);

    sf::Font font;
    font.loadFromFile("../projectsPhotos/doodle/Ubuntu-Bold.ttf");
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::Red);
    sf::Text gameoverText;
    gameoverText.setFont(font);
    gameoverText.setString("Game Over!");
    gameoverText.setCharacterSize(80);
    gameoverText.setFillColor(sf::Color::Red);

    // initialize platforms
    sf::Vector2u platformPosition[10];
    std::uniform_int_distribution<unsigned> x(0, 500 - platformTexture.getSize().x);
    std::uniform_int_distribution<unsigned> y(100, 700);
    std::default_random_engine e(time(0));
    for (size_t i = 0; i < 10; ++i)
    {
        platformPosition[i].x = x(e);
        platformPosition[i].y = y(e);
    }

    // player's positon and down velocity
    int playerX = 250;
    int playerY = 151;
    float dy = 0;
    int height = 150;
    int score = 0;

    // player's bounding box. It should modify according to the image size
    const int PLAYER_LEFT_BOUNDING_BOX = 20;
    const int PLAYER_RIGHT_BOUNDING_BOX = 60;
    const int PLAYER_BOTTOM_BOUNDING_BOX = 70;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            playerX -= 4;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            playerX += 4;

        if (playerX > 500)
            playerX = 0;
        if (playerX < -40)
            playerX = window.getSize().x - playerTexture.getSize().x;

        // score
        // dy = -1.60001 is terminal velocity that player stand on the platform and don't go up anymore
        // score can't increase in this situation
        if (playerY == height && dy < (-1.62))
        {
            score += 1;
            scoreText.setString("Score: " + std::to_string(score));
        }

        // player's jump mechanism
        dy += 0.2;
        playerY += dy;

        if (playerY < height)
            for (size_t i = 0; i < 10; ++i)
            {
                playerY = height;
                platformPosition[i].y -= dy;  // vertical translation
                if (platformPosition[i].y > 700) // set new platform on the top
                {
                    platformPosition[i].y = 0;
                    platformPosition[i].x = x(e);
                }

            }
        // detect jump on the platform
        for (size_t i = 0; i < 10; ++i)
        {
            if ((playerX + PLAYER_RIGHT_BOUNDING_BOX > platformPosition[i].x) && (playerX + PLAYER_LEFT_BOUNDING_BOX < platformPosition[i].x + 60)
                && (playerY + PLAYER_BOTTOM_BOUNDING_BOX > platformPosition[i].y) && (playerY + PLAYER_BOTTOM_BOUNDING_BOX < platformPosition[i].y + 17)
                && (dy > 0))
            {
                dy = -10;
            }

        }
        player.setPosition(playerX, playerY);

        window.draw(background);
        window.draw(player);

        // set and draw platforms
        for (size_t i = 0; i < 10; ++i)
        {
            platform.setPosition(platformPosition[i].x, platformPosition[i].y);
            window.draw(platform);
        }

        // game over
        if (playerY > 700)
        {
            gameoverText.setPosition(30, 200);
            scoreText.setPosition(150, 400);
            goto gameover;
        }
        window.draw(scoreText);
        window.display();
    }

    // Game Over
    gameover:
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.draw(gameoverBackground);
        window.draw(gameoverText);
        window.draw(scoreText);
        window.display();
    }
    return 0;
}
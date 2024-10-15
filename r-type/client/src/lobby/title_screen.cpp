#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include "client_config.hpp"


sf::View adjustAspectWithBlackBars(sf::View view, float windowWidth, float windowHeight) {
    float windowRatio = windowWidth / windowHeight;
    float viewRatio = view.getSize().x / view.getSize().y;
    std::vector<float> pos(2, 0);
    std::vector<float> size(2, 1);

    if (windowRatio >= viewRatio) {
        size[0] = viewRatio / windowRatio;
        pos[0] = (1 - size[0]) / 2.f;
    } else {
        size[1] = windowRatio / viewRatio;
        pos[1] = (1 - size[1]) / 2.f;
    }
    view.setViewport(sf::FloatRect(pos[0], pos[1], size[0], size[1]));
    return view;
}

/*!
* @brief Create letter sprites.
*
* This function creates letter sprites from the given texture.
*
* @param maxWidth The maximum width for scaling.
* @param maxHeight The maximum height for scaling.
* @param texture The texture containing the letters.
* @return std::vector<sf::Sprite> A vector of letter sprites.
*/
std::vector<sf::Sprite> create_letters(float maxWidth, float maxHeight, const sf::Texture& texture) {
    std::vector<sf::Sprite> sprites;
    sprites.emplace_back(texture, sf::IntRect(228, 891, 468, 468));
    sprites.emplace_back(texture, sf::IntRect(749, 891, 300, 468));
    sprites.emplace_back(texture, sf::IntRect(1051, 891, 484, 468));
    sprites.emplace_back(texture, sf::IntRect(1571, 891, 480, 468));
    sprites.emplace_back(texture, sf::IntRect(2076, 891, 480, 468));
    sprites.emplace_back(texture, sf::IntRect(2591, 891, 441, 468));
    for (int i =0;  i < 6; i++)
        sprites[i].setScale((maxWidth / 3077.f), (maxHeight / 1727.f));
    return sprites;
}

/*!
* @brief Create line sprites.
*
* This function creates line sprites from the given texture.
*
* @param maxWidth The maximum width for scaling.
* @param maxHeight The maximum height for scaling.
* @param texture The texture containing the lines.
* @return std::vector<sf::Sprite> A vector of line sprites.
*/
std::vector<sf::Sprite> create_lines(float maxWidth, float maxHeight, const sf::Texture& texture) {
    std::vector<sf::Sprite> lines;
    lines.emplace_back(texture, sf::IntRect(1678, 74, 1, 61));
    lines.emplace_back(texture, sf::IntRect(1678, 136, 1, 61));
    lines.emplace_back(texture, sf::IntRect(1807, 266, 1, 62));
    lines.emplace_back(texture, sf::IntRect(1807, 331, 1, 62));
    lines.emplace_back(texture, sf::IntRect(2140, 460, 1, 64));
    lines.emplace_back(texture, sf::IntRect(2386, 717, 1, 62));
    lines.emplace_back(texture, sf::IntRect(1471, 1612, 1, 68));
    std::vector<sf::Vector2f> positions = {sf::Vector2f((0.527f * maxWidth), (0.042f * maxHeight)),
                                           sf::Vector2f((0.527f * maxWidth), (0.078f * maxHeight)),
                                           sf::Vector2f((0.569f * maxWidth), (0.154f * maxHeight)),
                                           sf::Vector2f((0.569f * maxWidth), (0.191f * maxHeight)),
                                           sf::Vector2f((0.666f * maxWidth), (0.266f * maxHeight)),
                                           sf::Vector2f((0.758f * maxWidth), (0.415f * maxHeight)),
                                           sf::Vector2f((0.459f * maxWidth), (0.933f * maxHeight))};
    for (int i = 0; i < 7; i++) {
        lines[i].setPosition(positions[i]);
        lines[i].setScale((1920.f / 3077.f), (1080.f / 1727.f));
    }
    return lines;
}

/*!
* @brief Calculate the first animation.
*
* This function calculates the positions for the first animation.
*
* @param sprites The sprites to animate.
* @param startPos The starting position.
* @param positions The target positions.
* @param progress The progress of the animation.
*/
void firstAnimationCalculi(std::vector<sf::Sprite> &sprites, sf::Vector2f startPos, std::vector<sf::Vector2f> positions, float progress) {
    for (size_t i = 0; i < sprites.size(); ++i) {
        sf::Vector2f endPos = positions[i];
        float x = startPos.x + progress * (endPos.x - startPos.x);
        float y = startPos.y + progress * (endPos.y - startPos.y);
        sprites[i].setPosition(x, y);
    }
}

/*!
* @brief Calculate the second animation.
*
* This function calculates the positions for the second animation.
*
* @param sprites The sprites to animate.
* @param firstPos The starting positions.
* @param secondPos The target positions.
* @param progress The progress of the animation.
*/
void secondAnimationCalculi(std::vector<sf::Sprite> &sprites, std::vector<sf::Vector2f> firstPos, std::vector<sf::Vector2f> secondPos, float progress) {
    for (size_t i = 0; i < sprites.size(); ++i) {
        sf::Vector2f startPos = firstPos[i];
        sf::Vector2f endPos = secondPos[i];
        float x = startPos.x + progress * (endPos.x - startPos.x);
        float y = startPos.y + progress * (endPos.y - startPos.y);
        sprites[i].setPosition(x, y);
    }
}

/*!
* @brief Calculate the third animation.
*
* This function calculates the position for the third animation.
*
* @param endPos The target position.
* @param progress The progress of the animation.
* @return sf::Vector2f The calculated position.
*/
sf::Vector2f thirdAnimationCalculi(sf::Vector2f endPos, float progress) {

    sf::Vector2f startPos(0.f, 0.f);
    float x = startPos.x + progress * (endPos.x - startPos.x);
    float y = startPos.y + progress * (endPos.y - startPos.y);
    return {x, y};
}

/*!
* @brief Calculate the fourth animation.
*
* This function calculates the positions for the fourth animation.
*
* @param sprites The sprites to animate.
* @param secondPos The starting positions.
* @param thirdPos The target positions.
* @param progress The progress of the animation.
*/
void fourthAnimationCalculi(std::vector<sf::Sprite> &sprites, std::vector<sf::Vector2f> secondPos,std::vector<sf::Vector2f> thirdPos,float progress) {
    for (size_t i = 0; i < sprites.size(); ++i) {
        sf::Vector2f startPos = secondPos[i];
        sf::Vector2f endPos = thirdPos[i];
        float x = startPos.x + progress * (endPos.x - startPos.x);
        float y = startPos.y + progress * (endPos.y - startPos.y);
        sprites[i].setPosition(x, y);
    }
}

/*!
* @brief Calculate the fifth animation.
*
* This function calculates the fifth animation, which involves changing the width of the lines.
*
* @param sprites The sprites to animate.
* @param index The current index of the line.
* @param sixthAnimation A flag indicating if the sixth animation should start.
* @param clock The clock to measure elapsed time.
*/
void fifthAnimationCalculi(std::vector<sf::Sprite> &sprites, int &index, bool &sixthAnimation, sf::Clock &clock) {
    std::vector<int> maxWidthLines = {1360, 1360, 1169, 1169, 778, 594, 1489};
    float progress = clock.getElapsedTime().asSeconds() / 0.5f;
    if (progress > 1.0f) progress = 1.0f;

    sf::IntRect currentRect = sprites[index].getTextureRect();
    int targetWidth = maxWidthLines[index];
    auto newWidth = (int) (progress * (float) targetWidth);
    currentRect.width = newWidth;
    sprites[index].setTextureRect(currentRect);
    if (newWidth >= targetWidth) {
        std::cout << "end of line" << index << " next line" << std::endl;
        index++;
        if (index > 6)
            sixthAnimation = true;
        clock.restart();
    }
}

/*!
* @brief Calculate the sixth animation.
*
* This function calculates the sixth animation, which involves changing the opacity of the sprites.
*
* @param sprites The sprites to animate.
* @param transparent A flag indicating if the sprites should become transparent.
* @param opacity The current opacity of the sprites.
* @param clock The clock to measure elapsed time.
*/
void sixthAnimationCalculi(std::vector<sf::Sprite> &sprites, bool &transparent, float &opacity, sf::Clock &clock) {
    float elapsed = clock.getElapsedTime().asSeconds();
    if (elapsed > 0.05f) {
        if (transparent) {
            opacity -= 10;
            if (opacity <= 0) {
                opacity = 0;
                transparent = false;
            }
        } else {
            opacity += 10;
            if (opacity >= 255) {
                opacity = 255;
                transparent = true;
            }
        }
        clock.restart();
    }
    sprites[4].setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(opacity)));
}

/*!
* @brief Display the title screen.
*
* This function displays the title screen with animations and music.
*
* @param assetPath The path to the assets.
*/
void title_screen(const std::string& assetPath) {
    sf::View view;
    view.setSize( 1920.f, 1080.f );
    view.setCenter( view.getSize().x / 2, view.getSize().y / 2 );
    view = adjustAspectWithBlackBars( view, 1920.f, 1080.f);
    sf::RenderWindow window(sf::VideoMode(1920,1080), "MVP R-TYPE by Pol Pot", (sf::Style::Resize + sf::Style::Close));
    sf::Texture texture;
    texture.loadFromFile(assetPath + "/sprites/r-typesheet45.gif");
    sf::Music musique;
    musique.openFromFile(assetPath + "/Soundtracks/ambient_music/01. Title.wav");
    musique.setLoop(true);
    float maxWidth = view.getSize().x;
    float maxHeight = view.getSize().y;
    std::vector<sf::Sprite> letters  = create_letters(maxWidth, maxHeight, texture);
    sf::Sprite tm_sprite(texture, sf::IntRect(2835, 1423, 140, 49));
    tm_sprite.setScale((1920.f / 3077.f), (1080.f / 1727.f));
    std::vector<sf::Sprite> lines = create_lines(maxWidth, maxHeight, texture);

    std::vector<int> maxWidthLines = {1360, 1360, 1169, 1169, 778, 594, 1489};
    std::vector<sf::Vector2f> firstPos = {
        sf::Vector2f((0.06f * maxWidth), (0.43f * maxHeight)),
        sf::Vector2f((0.06f * maxWidth), (0.43f * maxHeight)),
        sf::Vector2f((0.06f * maxWidth), (0.43f * maxHeight)),
        sf::Vector2f((0.06f * maxWidth), (0.43f * maxHeight)),
        sf::Vector2f((0.06f * maxWidth), (0.43f * maxHeight)),
        sf::Vector2f((0.06f * maxWidth), (0.43f * maxHeight))
    };

    std::vector<sf::Vector2f> secondPos = {
        sf::Vector2f((0.04f * maxWidth), (0.43f * maxHeight)),
        sf::Vector2f((0.22f * maxWidth), (0.43f * maxHeight)),
        sf::Vector2f((0.32f * maxWidth), (0.43f * maxHeight)),
        sf::Vector2f((0.49f * maxWidth), (0.43f * maxHeight)),
        sf::Vector2f((0.66f * maxWidth), (0.43f * maxHeight)),
        sf::Vector2f((0.83f * maxWidth), (0.43f * maxHeight)),
        sf::Vector2f((0.924f * maxWidth), (0.724f * maxHeight)),

    };

    std::vector<sf::Vector2f> thirdPos = {
        sf::Vector2f((0.04f * maxWidth), (0.53f * maxHeight)),
        sf::Vector2f((0.22f * maxWidth), (0.53f * maxHeight)),
        sf::Vector2f((0.32f * maxWidth), (0.53f * maxHeight)),
        sf::Vector2f((0.49f * maxWidth), (0.53f * maxHeight)),
        sf::Vector2f((0.66f * maxWidth), (0.53f * maxHeight)),
        sf::Vector2f((0.83f * maxWidth), (0.53f * maxHeight)),
        sf::Vector2f((0.924f * maxWidth), (0.824f * maxHeight)),
    };

    for (auto& letter : letters)
        letter.setPosition(maxWidth, maxHeight);

    sf::Clock clock;
    bool secondAnimation = false;
    bool thirdAnimation = false;
    bool fourthAnimation = false;
    bool fifthAnimation = false;
    bool sixthAnimation = false;
    int currentLine = 0;
    float opacity = 255.f;
    bool transparent = true;

    musique.play();
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (event.type == sf::Event::Resized)
                view = adjustAspectWithBlackBars( view, (float)event.size.width, (float)event.size.height );

        float timeElapsed = clock.getElapsedTime().asSeconds();
        float progress = timeElapsed / 1.5f;

        if (progress > 1.0f) {
            progress = 1.0f;
            if (!secondAnimation) {
                std::cout<< "starting 2nd" << std::endl;
                secondAnimation = true;
                clock.restart();
            } else if (!thirdAnimation) {
                std::cout<< "starting 3rd" << std::endl;
                thirdAnimation = true;
                clock.restart();
            } else if (!fourthAnimation) {
                std::cout<< "starting 4th" << std::endl;
                letters.emplace_back(tm_sprite);
                fourthAnimation = true;
                clock.restart();
            } else if (!fifthAnimation) {
                std::cout<< "starting 5th" << std::endl;
                fifthAnimation = true;
                clock.restart();
            }
        }
        if (!secondAnimation) {
            firstAnimationCalculi(letters,
                                  sf::Vector2f(maxWidth, (0.43f * maxHeight)),
                                  firstPos,
                                  progress);
        } else if (!thirdAnimation) {
            secondAnimationCalculi(letters, firstPos, secondPos, progress);
        } else if (!fourthAnimation) {
            float thirdProgress = clock.getElapsedTime().asSeconds() / 1.f;
            if (thirdProgress > 1.0f) thirdProgress = 1.0f;
            sf::Vector2f newPosition = thirdAnimationCalculi(sf::Vector2f((0.924f * maxWidth), (0.724f * maxHeight)),
                                                             thirdProgress);
            tm_sprite.setPosition(newPosition);
        } else if (!fifthAnimation){
            float fourthProgress = clock.getElapsedTime().asSeconds() / 0.5f;
            if (fourthProgress > 1.0f) fourthProgress = 1.0f;
            fourthAnimationCalculi(letters, secondPos, thirdPos, fourthProgress);
        } else if(!sixthAnimation)
            fifthAnimationCalculi(lines, currentLine, sixthAnimation, clock);
        else
            sixthAnimationCalculi(lines, transparent, opacity, clock);
        window.clear();

        window.setView(view);
        for (const auto& letter : letters)
            window.draw(letter);
        if (thirdAnimation && !fourthAnimation)
            window.draw(tm_sprite);
        if (fifthAnimation)
            for (const auto & line : lines)
                window.draw(line);

        window.display();
    }
}

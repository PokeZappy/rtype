#include <SFML/Graphics.hpp>

sf::View adjustAspectWithBlackBars(sf::View view, float windowWidth, float windowHeight) {
    float windowRatio = windowWidth / windowHeight;
    float viewRatio = view.getSize().x / view.getSize().y;
    std::vector<float> pos(2, 0);
    std::vector<float> size(2, 1);

    if (bool horizontalSpacing = windowRatio >= viewRatio) {
        size[0] = viewRatio / windowRatio;
        pos[0] = (1 - size[0]) / 2.f;
    } else {
        size[1] = windowRatio / viewRatio;
        pos[1] = (1 - size[1]) / 2.f;
    }
    view.setViewport(sf::FloatRect(pos[0], pos[1], size[0], size[1]));
    return view;
}
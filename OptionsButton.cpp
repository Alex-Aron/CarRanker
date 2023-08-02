#include "OptionsButton.h"

OptionsButton::OptionsButton(int x, int y) {
	option.setRadius(18);
	option.setFillColor(sf::Color::White);
	option.setPosition(x, y);
	selectedOption.setRadius(16);
	selectedOption.setFillColor(sf::Color::White);
	selectedOption.setPosition(x + 2, y + 2);
	selected = false;
}

void OptionsButton::select() {
	selected = !selected;
}

bool OptionsButton::isSelected() {
	return selected;
}

sf::CircleShape OptionsButton::myOption() {
	return option;
}

void OptionsButton::drawButton(sf::RenderWindow& window) {
	if (selected) {
		selectedOption.setFillColor(sf::Color::Black);
	}
	else {
		selectedOption.setFillColor(sf::Color::White);
	}
	window.draw(option);
	window.draw(selectedOption);
}
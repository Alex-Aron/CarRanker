#pragma once
#include <SFML/Graphics.hpp>

class OptionsButton {
	sf::CircleShape option;
	sf::CircleShape selectedOption;
	bool selected;
public:
	OptionsButton(int x, int y);
	void select();
	sf::CircleShape myOption();	//getter (returns the sf option object)
	bool isSelected();			//getter (returns the selected status)
	void drawButton(sf::RenderWindow& window);
};

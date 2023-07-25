#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "cars.h"
#include "AdList.h"
#include "weather.h"

// Function to split a string based on a delim (comma in this case)
std::vector<std::string> splitString(const std::string& line, char delim) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(line);
    while (std::getline(tokenStream, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    AdList adList;
    std::ifstream carFile("cars.csv");
    if (!carFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }
    std::vector<cars> carData;
    std::vector<weather> weatherData;
    std::string line;

    std::getline(carFile, line);
    while (std::getline(carFile, line)) {
        std::vector<std::string> row = splitString(line, ',');
        for(auto & str : row){
            str.erase(std::remove(str.begin(), str.end(), '\"'), str.end());
        }
            cars car(std::stoi(row[0]), std::stoi(row[1]), std::stoi(row[2]), row[3], row[4],
                     true, std::stoi(row[6]), row[7], std::stoi(row[8]), row[9],
                     std::stoi(row[10]), true, row[12], row[13], row[14], std::stoi(row[15]),
                     std::stoi(row[16]), std::stoi(row[17]));
            carData.push_back(car);
    }

    std::ifstream weatherFile("weather.csv");
    if (!carFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }
    std::getline(weatherFile, line);
    while (std::getline(weatherFile, line)) {
        std::vector<std::string> row = splitString(line, ',');
        for(auto & str : row){
            str.erase(std::remove(str.begin(), str.end(), '\"'), str.end());
        }
            weather weatherCity(std::stof(row[0]), row[1], std::stoi(row[2]), std::stoi(row[3]), std::stoi(row[4]),row[5], row[6], row[7], row[9], std::stoi(row[10]), std::stoi(row[11]), std::stoi(row[12]), std::stoi(row[13]), std::stof(row[14]));
            weatherData.push_back(weatherCity);
    }

    for(int i = 0; i < carData.size(); i++){
        for(int j = i + 1; j < carData.size(); j++){
            if(carData[i].getMake() == carData[j].getMake()){
                adList.insertEdge(carData[i], carData[j]);
            }
        }
    }
    // Define the window dimensions
    const int windowWidth = 540;
    const int windowHeight = 930;

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML Portrait Window");

    // Define the button dimensions and position
    const int buttonWidth = 250;
    const int buttonHeight = 100;
    const int buttonX = (windowWidth - buttonWidth) / 2; // Center the button horizontally
    const int buttonY = (windowHeight * 2) / 3; // Position the button about 1/3 from the bottom

    // Create the button shape and text
    sf::RectangleShape button(sf::Vector2f(buttonWidth, buttonHeight));
    button.setPosition(buttonX, buttonY);
    button.setFillColor(sf::Color::Blue);
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text buttonText("Find Car", font, 18);
    buttonText.setPosition(buttonX + (buttonWidth - buttonText.getLocalBounds().width) / 2,
                           buttonY + (buttonHeight - buttonText.getLocalBounds().height) / 2);
    buttonText.setFillColor(sf::Color::White);
    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            // Check for button click
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << "Implement action Later" << std::endl;
                    }
                }
            }
        }

        // Clear the window
        window.clear(sf::Color::White);

        // Draw the button
        window.draw(button);
        window.draw(buttonText);

        // Display the content
        window.display();
    }

    carFile.close();
    weatherFile.close();
    return 0;
}
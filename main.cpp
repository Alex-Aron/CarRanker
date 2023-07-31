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
void sfmlHandling(std::string& userState, std::string& makeBoxText, std::string& cylinderCount);
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
    std::string userState;
    std::string makeBoxText;
    std::string cylinderCount;
    AdList carAdList;//Might switch to matrix
    AdList weatherAdList;
    std::ifstream carFile("cars.csv");
    if (!carFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }
    sfmlHandling(userState, makeBoxText, cylinderCount);
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
                carAdList.insertCarEdge(carData[i], carData[j]);
            }
        }
    }
    for(int i = 0; i < weatherData.size(); i++){
        for(int j = i + 1; j < weatherData.size(); j++){
            if(weatherData[i].getLocation() == weatherData[j].getLocation()){
                weatherAdList.insertWeatherEdge(weatherData[i], weatherData[j]);
            }
        }
    }

    carFile.close();
    weatherFile.close();
    return 0;
}

void sfmlHandling(std::string& userState, std::string& makeBoxText, std::string& cylinderCount){
    const int windowWidth = 540;
    const int windowHeight = 930;
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML Portrait Window");
    const int buttonWidth = 250;
    const int buttonHeight = 100;
    const int buttonX = (windowWidth - buttonWidth) / 2; // Center the button horizontally
    const int buttonY = (windowHeight * 2) / 2.5; // Position the button about 1/3 from the bottom
    bool showMakeBox = false;
    bool showCylinderBox = false;
    // Create the button shape and text
    sf::RectangleShape carButton(sf::Vector2f(buttonWidth, buttonHeight));
    sf::RectangleShape underLine(sf::Vector2f(windowWidth, 1));
    sf::RectangleShape stateInput(sf::Vector2f(300, 30));
    sf::RectangleShape makeBox(sf::Vector2f(150, 20));
    sf::RectangleShape cylinderBox(sf::Vector2f(200, 20));
    makeBox.setFillColor(sf::Color::Black);
    cylinderBox.setFillColor(sf::Color::Black);
    sf::CircleShape option1;
    sf::CircleShape option2;
    sf::CircleShape option3;
    sf::CircleShape option4;
    sf::CircleShape option5;
    sf::CircleShape option6;
    sf::CircleShape selectedOption;
    sf::CircleShape automaticSelected;
    selectedOption.setFillColor(sf::Color::Black);
    automaticSelected.setFillColor(sf::Color::White);
    selectedOption.setRadius(16);
    automaticSelected.setRadius(16);
    option1.setRadius(18);
    option2.setRadius(18);
    option3.setRadius(18);
    option4.setRadius(18);
    option5.setRadius(18);
    option6.setRadius(18);
    option1.setPosition(80,170);
    option2.setPosition(80,250);
    option3.setPosition(80,330);
    option4.setPosition(80,410);
    option5.setPosition(80,490);
    option6.setPosition(80, 570);
    automaticSelected.setPosition(82, 572);
    option1.setFillColor(sf::Color::White);
    option2.setFillColor(sf::Color::White);
    option3.setFillColor(sf::Color::White);
    option4.setFillColor(sf::Color::White);
    option5.setFillColor(sf::Color::White);
    stateInput.setPosition(120,670);
    carButton.setPosition(buttonX, buttonY);
    underLine.setPosition(0, 90);
    carButton.setFillColor(sf::Color::Blue);
    underLine.setFillColor(sf::Color::White);
    stateInput.setFillColor(sf::Color::White);
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text buttonText("Find Car", font, 26);
    sf::Text titleText("Car Selection Helper", font, 34);
    sf::Text questionText("What Do You Want to Prioritize: ", font, 28);
    sf::Text option1Text("Horsepower (HP)", font, 28);
    sf::Text option2Text("Car Make (Example: Cheverolet)", font, 25);
    sf::Text option2SubText("Enter Make: ", font, 18);
    sf::Text option3Text("Engine Type (Example: 6 Cylinder)" , font, 24);
    sf::Text option3SubText("Number of Cylinders:", font, 14);
    sf::Text option4Text("Gas Mileage(City Priority)", font, 28);
    sf::Text option5Text("Gas Mileage(Highway Priority)", font, 28);
    sf::Text option6Text("Automatic Engine(Blank for Manual)", font, 20);
    sf::Text locationPrompt("What State Do You Live In?", font, 28);
    sf::Text userInput("", font, 28);
    sf::Text makeInput("", font, 18);
    sf::Text cylinderInput("", font, 18);
    option1Text.setPosition(130, 170);
    option2Text.setPosition(130, 250);
    option3Text.setPosition(130, 330);
    option4Text.setPosition(130, 410);
    option5Text.setPosition(130, 490);
    option6Text.setPosition(130, 570);
    userInput.setPosition(125, 665);
    questionText.setPosition(80, 110);
    locationPrompt.setPosition(100, 630);
    titleText.setPosition(120, 50);
    buttonText.setPosition(buttonX + (buttonWidth - buttonText.getLocalBounds().width) / 2,
                           buttonY + (buttonHeight - buttonText.getLocalBounds().height) / 2);
    //buttonText.setFillColor(sf::Color::White);
    //titleText.setFillColor(sf::Color::White);
    userInput.setFillColor(sf::Color::Black);
    makeInput.setFillColor(sf::Color::Black);
    cylinderInput.setFillColor(sf::Color::Black);
    option3SubText.setFillColor(sf::Color::White);
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
                    if (option6.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        if (automaticSelected.getFillColor() == sf::Color::Black) {
                            automaticSelected.setFillColor(sf::Color::White);
                        } else {
                            automaticSelected.setFillColor(sf::Color::Black);
                        }
                    }
                    if (option1.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        selectedOption.setPosition(82, 172);
                        showMakeBox = false;
                        showCylinderBox = false;
                    } else if (option2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        selectedOption.setPosition(82, 252);
                        makeBox.setFillColor(sf::Color::White);
                        makeBox.setPosition(230, 282);
                        option2SubText.setPosition(130, 282);
                        makeInput.setPosition(240, 282);
                        makeInput.setFillColor(sf::Color::Black);
                        showMakeBox = true;
                        showCylinderBox = false;
                    } else if (option3.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        selectedOption.setPosition(82, 332);
                        cylinderBox.setFillColor(sf::Color::White);
                        cylinderBox.setPosition(265, 364);
                        option3SubText.setPosition(130, 362);
                        cylinderInput.setPosition(270, 362);
                        cylinderInput.setFillColor(sf::Color::Black);
                        showMakeBox = false;
                        showCylinderBox = true;
                    } else if (option4.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        selectedOption.setPosition(82, 412);
                        showMakeBox = false;
                        showCylinderBox = false;
                    } else if (option5.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        selectedOption.setPosition(82, 492);
                        showMakeBox = false;
                        showCylinderBox = false;
                    }
                    if (carButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << "Implement action Later" << std::endl;
                    }
                }
            }
        if (event.type == sf::Event::TextEntered) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (stateInput.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                if (event.text.unicode <
                    128) {//Ensure it is only the unicode alphabet characters that would be in a state
                    if (event.text.unicode == 13) { // Handle Enter key press (optional)
                        std::cout << "User State: " << userState << std::endl;
                        //Use if want to clear input userState.clear();
                    } else if (event.text.unicode == 8 &&
                               !userState.empty()) {//Backspace is unicode 8, so if that is pressed get rid of the last character.
                        userState.pop_back();
                    } else if (userState.size() <
                               20) {//Longest state name is Massachusetts, which is 13 characters, so it shouldn't even be longer than that
                        userState += static_cast<char>(event.text.unicode);
                    }
                    //Make sure the textBox shows the charcters being typed in
                    userInput.setString(userState);
                }
            } else if (makeBox.getGlobalBounds().contains(mousePos.x, mousePos.y) && showMakeBox) {
                if (event.type == sf::Event::TextEntered && showMakeBox) {
                    if (event.text.unicode <
                        128) {//Ensure it is only the unicode alphabet characters that would be in a state
                        if (event.text.unicode == 13) { // Handle Enter key press (optional)
                            std::cout << makeBoxText << std::endl;
                            //Use if want to clear input userState.clear();
                        } else if (event.text.unicode == 8 &&
                                   !makeBoxText.empty()) {//Backspace is unicode 8, so if that is pressed get rid of the last character.
                            makeBoxText.pop_back();
                        } else if (userState.size() <
                                   20) {//Longest state name is Massachusetts, which is 13 characters, so it shouldn't even be longer than that
                            makeBoxText += static_cast<char>(event.text.unicode);
                        }
                        //Make sure the textBox shows the charcters being typed in
                        makeInput.setString(makeBoxText);
                    }
                }
            }
            else if (cylinderBox.getGlobalBounds().contains(mousePos.x, mousePos.y) && showCylinderBox) {
                if (event.type == sf::Event::TextEntered && showCylinderBox) {
                    if (event.text.unicode <
                        128) {//Ensure it is only the unicode alphabet characters that would be in a state
                        if (event.text.unicode == 13) { // Handle Enter key press (optional)
                            std::cout << cylinderCount << std::endl;
                            //Use if want to clear input userState.clear();
                        } else if (event.text.unicode == 8 &&
                                   !cylinderCount.empty()) {//Backspace is unicode 8, so if that is pressed get rid of the last character.
                            cylinderCount.pop_back();
                        } else if (userState.size() <
                                   20) {//Longest state name is Massachusetts, which is 13 characters, so it shouldn't even be longer than that
                            cylinderCount += static_cast<char>(event.text.unicode);
                        }
                        //Make sure the textBox shows the charcters being typed in
                        cylinderInput.setString(cylinderCount);
                    }
                }
            }
        }
        }
            // Clear the window
            window.clear(sf::Color::Black);
            // Draw all the sfml objects
            window.draw(carButton);
            window.draw(buttonText);
            window.draw(titleText);
            window.draw(underLine);
            window.draw(questionText);
            window.draw(locationPrompt);
            window.draw(stateInput);
            window.draw(userInput);
            window.draw(option1);
            window.draw(option2);
            window.draw(option3);
            window.draw(option4);
            window.draw(option5);
            window.draw(option6);
            window.draw(option1Text);
            window.draw(option2Text);
            window.draw(option3Text);
            window.draw(option4Text);
            window.draw(option5Text);
            window.draw(option6Text);
            window.draw(selectedOption);
            window.draw(automaticSelected);
            if (showMakeBox) {
                window.draw(makeBox);
                window.draw(option2SubText);
                window.draw(makeInput);
            }
            if (showCylinderBox) {
            window.draw(cylinderBox);
            window.draw(option3SubText);
            window.draw(cylinderInput);
            }
            window.display();
        }
    }

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "cars.h"
#include "weather.h"
#include "OptionsButton.h"
#include "sorts.h"
//Function definitions
void sfmlHandling(std::string& userState, std::string& makeBoxText, std::string& cylinderCount, bool& horsepower, bool& gasCity, bool& gasHighway, bool& findCarClicked);
void resultWindow(std::vector<cars>& mergeResults, std::string mergeTimeTaken,std::vector<cars>& quickResults, std::string quickTimeTaken);
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
    bool horsepower = false;
    bool gasCity = false;
    bool gasHighway = false;
    bool findCarClicked = false;
    std::string userState = "";
    std::string makeBoxText = "";
    std::string cylinderCount = "";
    std::ifstream carFile("cars.csv");
    if (!carFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }
    //sfmlHandling(userState, makeBoxText, cylinderCount);
    std::vector<cars> carData;
    std::vector<weather> weatherData;
    std::string line;
    std::getline(carFile, line);
    while (std::getline(carFile, line)) {
        std::vector<std::string> row = splitString(line, ',');
        for (auto& str : row) {
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
        for (auto& str : row) {
            str.erase(std::remove(str.begin(), str.end(), '\"'), str.end());
        }
        weather weatherCity(std::stof(row[0]), row[1], std::stoi(row[2]), std::stoi(row[3]), std::stoi(row[4]), row[5], row[6], row[7], row[9], std::stoi(row[10]), std::stoi(row[11]), std::stoi(row[12]), std::stoi(row[13]), std::stof(row[14]));
        weatherData.push_back(weatherCity);
    }

    sfmlHandling(userState, makeBoxText, cylinderCount, horsepower, gasCity, gasHighway, findCarClicked);
    std::vector<cars> mergeResults;
    std::vector<cars> quickResults;
    auto startTimeMerge = std::chrono::high_resolution_clock::now();
    if (makeBoxText != "") {
        sortMake(carData, mergeResults, makeBoxText);
    }
    if (horsepower) {
        mergeSortHorsepower(carData, mergeResults);
    }

    if (gasCity) {
        mergeSortGasCity(carData, mergeResults);
    }

    if (gasHighway) {
        mergeSortGasHighway(carData, mergeResults);
    }
    auto endTimeMerge = std::chrono::high_resolution_clock::now();
    auto durationMerge = std::chrono::duration_cast<std::chrono::microseconds>(endTimeMerge - startTimeMerge).count();
    std::string mergeTimeTaken = std::to_string(durationMerge);
    auto startTimeQuick = std::chrono::high_resolution_clock::now();
    if (makeBoxText != "") {
        sortMake(carData, quickResults, makeBoxText);
    }
    if (horsepower) {
        quickSortHorsepower(carData, quickResults);
    }

    if (gasCity) {
        quickSortGasCity(carData, quickResults);
    }
    if (gasHighway) {
        quickSortGasHighway(carData, quickResults);
    }
    auto endTimeQuick = std::chrono::high_resolution_clock::now();
    auto durationQuick = std::chrono::duration_cast<std::chrono::microseconds>(endTimeQuick - startTimeQuick).count();
    std::string quickTimeTaken = std::to_string(durationQuick);
    if(findCarClicked){
        resultWindow(mergeResults, mergeTimeTaken, quickResults, quickTimeTaken);
    }

    std::cout << "Here is your list of cars other than the top two: " << std::endl;
    std::cout << mergeResults.size() << std::endl;
    for (int i = 0; i < mergeResults.size(); i++) {
        mergeResults[i].printCar();
    }
    carFile.close();
    weatherFile.close();
    return 0;
}

void sfmlHandling(std::string& userState, std::string& makeBoxText, std::string& cylinderCount, bool& horsepower, bool& gasCity, bool&
gasHighway, bool& findCarClicked) {
    const int windowWidth = 540;
    const int windowHeight = 930;
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Car Selection Helper");
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
    OptionsButton option1(80, 170);
    OptionsButton option2(80, 250);
    OptionsButton option3(80, 330);
    OptionsButton option4(80, 410);
    OptionsButton option5(80, 490);
    OptionsButton option6(80, 570);
    stateInput.setPosition(120, 670);
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
    sf::Text option3Text("Engine Type (Example: 6 Cylinder)", font, 24);
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
                    if (option1.myOption().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        option1.select();
                        horsepower = !horsepower;
                    }
                    if (option2.myOption().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        option2.select();
                        if (option2.isSelected()) {
                            makeBox.setFillColor(sf::Color::White);
                            makeBox.setPosition(230, 282);
                            option2SubText.setPosition(130, 282);
                            makeInput.setPosition(240, 282);
                            makeInput.setFillColor(sf::Color::Black);
                            showMakeBox = true;
                        }
                        else {
                            showMakeBox = false;
                        }
                    }
                    if (option3.myOption().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        option3.select();
                        if (option3.isSelected()) {
                            cylinderBox.setFillColor(sf::Color::White);
                            cylinderBox.setPosition(265, 364);
                            option3SubText.setPosition(130, 362);
                            cylinderInput.setPosition(270, 362);
                            cylinderInput.setFillColor(sf::Color::Black);
                            showCylinderBox = true;
                        }
                        else {
                            showCylinderBox = false;
                        }
                    }
                    if (option4.myOption().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        option4.select();
                        gasCity = !gasCity;
                    }
                    if (option5.myOption().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        option5.select();
                        gasHighway = !gasHighway;
                    }
                    if (option6.myOption().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        option6.select();
                    }
                    if (carButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        findCarClicked = true;
                        window.close();
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
                        }
                        else if (event.text.unicode == 8 &&
                            !userState.empty()) {//Backspace is unicode 8, so if that is pressed get rid of the last character.
                            userState.pop_back();
                        }
                        else if (userState.size() <
                            20) {//Longest state name is Massachusetts, which is 13 characters, so it shouldn't even be longer than that
                            userState += static_cast<char>(event.text.unicode);
                        }
                        //Make sure the textBox shows the charcters being typed in
                        userInput.setString(userState);
                    }
                }
                else if (makeBox.getGlobalBounds().contains(mousePos.x, mousePos.y) && showMakeBox) {
                    if (event.type == sf::Event::TextEntered && showMakeBox) {
                        if (event.text.unicode <
                            128) {//Ensure it is only the unicode alphabet characters that would be in a state
                            if (event.text.unicode == 13) { // Handle Enter key press (optional)
                                std::cout << makeBoxText << std::endl;
                                //Use if want to clear input userState.clear();
                            }
                            else if (event.text.unicode == 8 &&
                                !makeBoxText.empty()) {//Backspace is unicode 8, so if that is pressed get rid of the last character.
                                makeBoxText.pop_back();
                            }
                            else if (userState.size() <
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
                            }
                            else if (event.text.unicode == 8 &&
                                !cylinderCount.empty()) {//Backspace is unicode 8, so if that is pressed get rid of the last character.
                                cylinderCount.pop_back();
                            }
                            else if (userState.size() <
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
        option1.drawButton(window);
        option2.drawButton(window);
        option3.drawButton(window);
        option4.drawButton(window);
        option5.drawButton(window);
        option6.drawButton(window);
        window.draw(option1Text);
        window.draw(option2Text);
        window.draw(option3Text);
        window.draw(option4Text);
        window.draw(option5Text);
        window.draw(option6Text);
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

void resultWindow(std::vector<cars>& mergeResults, std::string mergeTimeTaken,std::vector<cars>& quickResults, std::string quickTimeTaken){
    sf::RenderWindow secondWindow(sf::VideoMode(450, 800), "SFML SubWindow");
    sf::Font font;
    font.loadFromFile("arial.ttf");
    while (secondWindow.isOpen()) {
        sf::Event secondEvent;
        std::string mergeCarText = mergeResults[0].carText();
        sf::Text mergeCarFound("Mergesort result found:\n" + mergeCarText, font, 14);
        mergeCarFound.setPosition(0, 10);
        sf::Text timeMT("Time Taken for Mergesort: " + mergeTimeTaken + " microseconds", font, 18);
        timeMT.setPosition(0, 315);
        while (secondWindow.pollEvent(secondEvent)) {
            if (secondEvent.type == sf::Event::Closed)
                secondWindow.close();
        }
        std::string quickCarText = quickResults[0].carText();
        sf::Text quickCarFound("Quicksort Result found:\n" + quickCarText, font, 14);
        quickCarFound.setPosition(0, 370);
        sf::Text timeQT("Time Taken for QuickSort: " + quickTimeTaken + " microseconds", font, 18);
        timeQT.setPosition(0, 675);
        while (secondWindow.pollEvent(secondEvent)) {
            if (secondEvent.type == sf::Event::Closed)
                secondWindow.close();
        }
        sf::Text timeFaster;
        if(std::stoi(mergeTimeTaken) < std::stoi(quickTimeTaken)){
            int timeDiff = std::stoi(quickTimeTaken) - std::stoi(mergeTimeTaken);
            timeFaster = sf::Text("Mergesort faster by " + std::to_string(timeDiff) + " microseconds", font, 16);
        }else if(std::stoi(mergeTimeTaken) > std::stoi(quickTimeTaken)){
            int timeDiff = std::stoi(mergeTimeTaken) - std::stoi(quickTimeTaken);
                timeFaster = sf::Text("Quicksort faster by " + std::to_string(timeDiff) + " microseconds", font, 16);
        }else{
                timeFaster = sf::Text("Same Exact Speed", font, 16);
        }
        timeFaster.setPosition(0, 770);
        secondWindow.clear(sf::Color::Black);
        secondWindow.draw(mergeCarFound);
        secondWindow.draw(timeMT);
        secondWindow.draw(quickCarFound);
        secondWindow.draw(timeFaster);
        secondWindow.draw(timeQT);
        secondWindow.display();
    }
}

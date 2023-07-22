#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "cars.h"
#include "AdList.h"

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
    std::vector<std::vector<std::string>> weatherData;

    std::string line;
    // Read the header row and print the column names
    std::getline(carFile, line);
    std::vector<std::string> header = splitString(line, ',');
    for (const auto& column : header) {
        std::cout << column << "\t";
    }
    std::cout << std::endl;

    while (std::getline(carFile, line)) {
        std::vector<std::string> row = splitString(line, ',');
        if (row.size() >= 18) { // Ensure the row contains at least 18 columns (a to r)
            cars car(std::stoi(row[0]), std::stoi(row[1]), std::stoi(row[2]), row[3], row[4],
                     row[5] == "1", std::stoi(row[6]), row[7], std::stoi(row[8]), row[9],
                     std::stoi(row[10]), row[11] == "1", row[12], row[13], row[14], std::stoi(row[15]),
                     std::stoi(row[16]), std::stoi(row[17]));
            carData.push_back(car);
        } else {
            std::cerr << "Invalid row format: " << line << std::endl;
        }
    }

    // Printing the content of the CSV file to the console along with column headers
    for (const auto& row : carData) {
        for (int i = 0; i < header.size(); ++i) {
        //    std::cout << header[i] << ": " << row[i] << "\t";
        }
        std::cout << std::endl;
    }

    carFile.close();
    std::ifstream WeatherFile("weather.csv");
    if (!carFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }
    // Read the header row and print the column names
    std::getline(carFile, line);
    header = splitString(line, ',');
    for (const auto& column : header) {
        std::cout << column << "\t";
    }
    std::cout << std::endl;

    while (std::getline(carFile, line)) {
        std::vector<std::string> row = splitString(line, ',');
        if (row.size() >= 18) { // Ensure the row contains at least 18 columns (a to r)
            cars car(std::stoi(row[0]), std::stoi(row[1]), std::stoi(row[2]), row[3], row[4],
                    row[5] == "1", std::stoi(row[6]), row[7], std::stoi(row[8]), row[9],
                    std::stoi(row[10]), row[11] == "1", row[12], row[13], row[14], std::stoi(row[15]),
                    std::stoi(row[16]), std::stoi(row[17]));
            carData.push_back(car);
        } else {
            std::cerr << "Invalid row format: " << line << std::endl;
        }
    }

    // Printing the content of the CSV file to the console along with column headers
    for(int i = 0; i < carData.size(); i++){
        for(int j = i + 1; j < carData.size(); j++){
            if(carData[i].getMake() == carData[j].getMake()){
                adList.insertEdge(carData[i], carData[j]);
            }
        }
    }

    carFile.close();
    return 0;
}
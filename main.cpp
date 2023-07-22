#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "cars.h"

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
    std::ifstream carFile("cars.csv");
    if (!carFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    std::vector<std::vector<std::string>> carData;
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
            carData.push_back(row);
        } else {
            std::cerr << "Invalid row format: " << line << std::endl;
        }
    }

    // Printing the content of the CSV file to the console along with column headers
    for (const auto& row : carData) {
        for (int i = 0; i < header.size(); ++i) {
            std::cout << header[i] << ": " << row[i] << "\t";
        }
        std::cout << std::endl;
    }

    carFile.close();
    std::ifstream WeatherFile("cars.csv");
    if (!carFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }
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
            carData.push_back(row);
        } else {
            std::cerr << "Invalid row format: " << line << std::endl;
        }
    }

    // Printing the content of the CSV file to the console along with column headers
    for (const auto& row : carData) {
        for (int i = 0; i < header.size(); ++i) {
            std::cout << header[i] << ": " << row[i] << "\t";
        }
        std::cout << std::endl;
    }

    carFile.close();
    return 0;
}
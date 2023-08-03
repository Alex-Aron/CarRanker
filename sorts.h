#include <iostream>
#include <vector>
#include "cars.h"
#include "weather.h"
void sortMake(std::vector<cars>& carData, std::vector<cars>& ans, std::string make, std::string isAuto);
void mergeHP(std::vector<cars>& carData, int start, int mid, int end);
void mergeSortHP(std::vector<cars>& carData, int start, int end);
void mergeSortHorsepower(std::vector<cars>& carData, std::vector<cars>& ans, std::string isAuto);
int qPartitionHP(std::vector<cars>& carData, int low, int high);
void quickSortHP(std::vector<cars>& carData, int low, int high);
void quickSortHorsepower(std::vector<cars>& carData, std::vector<cars>& ans, std::string isAuto);
int qPartitionC(std::vector<cars>& carData, int low, int high);
void quickSortC(std::vector<cars>& carData, int low, int high);
void quickSortGasCity(std::vector<cars>& carData, std::vector<cars>& ans, std::string isAuto);
void mergeC(std::vector<cars>& carData, int start, int mid, int end);
void mergeSortC(std::vector<cars>& carData, int start, int end);
void mergeSortGasCity(std::vector<cars>& carData, std::vector<cars>& ans, std::string isAuto);
int qPartitionH(std::vector<cars>& carData, int low, int high);
void quickSortH(std::vector<cars>& carData, int low, int high);
void quickSortGasHighway(std::vector<cars>& carData, std::vector<cars>& ans, std::string isAuto);
void mergeHW(std::vector<cars>& carData, int start, int mid, int end);
void mergeSortHW(std::vector<cars>& carData, int start, int end);
void mergeSortGasHighway(std::vector<cars>& carData, std::vector<cars>& ans, std::string isAuto);
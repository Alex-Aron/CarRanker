#include "sorts.h"
void sortMake(std::vector<cars>& carData, std::vector<cars>& ans, std::string make) {
    for (int i = 0; i < carData.size(); i++) {
        if (carData[i].getMake() == make) {
            ans.push_back(carData[i]);//Data in csv already sorted by make
        }
    }
}

void mergeHP(std::vector<cars>& carData, int start, int mid, int end) {
    int len1 = mid - start + 1;
    int len2 = end - mid;
    std::vector<cars> vect1;
    std::vector<cars> vect2;
    for (int i = 0; i < len1; i++) {
        vect1.push_back(carData[start + i]);
    }
    for(int i = 0; i < len2; i++) {
        vect2.push_back(carData[mid + 1 + i]);
    }
    int i = 0;
    int j = 0;
    int k = start;
    while (i < len1 && j < len2) {
        if (vect1[i].getHorsepower() <= vect2[j].getHorsepower()) {
            carData[k] = vect1[i];
            i++;
        }
        else {
            carData[k] = vect2[j];
            j++;
        }
        k++;
    }
    while (i < len1) {
        carData[k] = vect1[i];
        i++;
        k++;
    }
    while (j < len2) {
        carData[k] = vect2[j];
        j++;
        k++;
    }
}

void mergeSortHP(std::vector<cars>& carData, int start, int end) {
    if (start == end) {
        return;
    }
    int mid = (start + end) / 2;
    mergeSortHP(carData, start, mid);
    mergeSortHP(carData, mid + 1, end);
    mergeHP(carData, start, mid, end);
}

void mergeSortHorsepower(std::vector<cars>& carData, std::vector<cars>& ans) {
    mergeSortHP(carData, 0, carData.size() - 1);
    for (int i = carData.size() - 1; i > carData.size() - 1001; i--) {
        ans.push_back(carData[i]);
    }
}


int qPartitionHP(std::vector<cars>& carData, int low, int high) {
    int pivot = carData[high].getHorsepower();
    int up = low;
    int down = high - 1;
    while (up <= down) {
        while (up <= down && carData[up].getHorsepower() <= pivot) {
            up++;
        }
        while (down >= up && carData[down].getHorsepower() >= pivot) {
            down--;
        }
        if (up < down) {
            cars temp = carData[up];
            carData[up] = carData[down];
            carData[down] = temp;
        }
    }
    cars temp = carData[up];
    carData[up] = carData[high];
    carData[high] = temp;
    return up;
}
void quickSortHP(std::vector<cars>& carData, int low, int high) {
    if (low < high) {
        int pivot = qPartitionHP(carData, low, high);
        quickSortHP(carData, low, pivot - 1);
        quickSortHP(carData, pivot + 1, high);
    }
    return;
}

void quickSortHorsepower(std::vector<cars>& carData, std::vector<cars>& ans) {
    quickSortHP(carData, 0, carData.size() - 1);
    for (int i = carData.size() - 1; i > carData.size() - 1001; i--) {
        ans.push_back(carData[i]);
    }
}

int qPartitionC(std::vector<cars>& carData, int low, int high) {
    int pivot = carData[high].getCityMPG();
    int up = low;
    int down = high - 1;
    while (up <= down) {
        while (up <= down && carData[up].getCityMPG() <= pivot) {
            up++;
        }
        while (down >= up && carData[down].getCityMPG() >= pivot) {
            down--;
        }
        if (up < down) {
            cars temp = carData[up];
            carData[up] = carData[down];
            carData[down] = temp;
        }
    }
    cars temp = carData[up];
    carData[up] = carData[high];
    carData[high] = temp;
    return up;
}

void quickSortC(std::vector<cars>& carData, int low, int high) {
    if (low < high) {
        int pivot = qPartitionC(carData, low, high);
        quickSortC(carData, low, pivot - 1);
        quickSortC(carData, pivot + 1, high);
    }
    return;
}

void quickSortGasCity(std::vector<cars>& carData, std::vector<cars>& ans) {
    quickSortC(carData, 0, carData.size()-1);
    for (int i = carData.size() - 1; i > carData.size() - 1001; i--) {
        ans.push_back(carData[i]);
    }
    return;
}


void mergeC(std::vector<cars>& carData, int start, int mid, int end) {
    int len1 = mid - start + 1;
    int len2 = end - mid;
    std::vector<cars> vect1;
    std::vector<cars> vect2;
    for (int i = 0; i < len1; i++) {
        vect1.push_back(carData[start + i]);
    }
    for(int i = 0; i < len2; i++) {
        vect2.push_back(carData[mid + 1 + i]);
    }
    int i = 0;
    int j = 0;
    int k = start;
    while (i < len1 && j < len2) {
        if (vect1[i].getCityMPG() <= vect2[j].getCityMPG()) {
            carData[k] = vect1[i];
            i++;
        }
        else {
            carData[k] = vect2[j];
            j++;
        }
        k++;
    }
    while (i < len1) {
        carData[k] = vect1[i];
        i++;
        k++;
    }
    while (j < len2) {
        carData[k] = vect2[j];
        j++;
        k++;
    }
}

void mergeSortC(std::vector<cars>& carData, int start, int end) {
    if (start == end) {
        return;
    }
    int mid = (start + end) / 2;
    mergeSortC(carData, start, mid);
    mergeSortC(carData, mid + 1, end);
    mergeC(carData, start, mid, end);
}

void mergeSortGasCity(std::vector<cars>& carData, std::vector<cars>& ans) {
    mergeSortC(carData, 0, carData.size()-1);
    for (int i = carData.size() - 1; i > carData.size() - 1001; i--) {
        ans.push_back(carData[i]);
    }
    return;
}
int qPartitionH(std::vector<cars>& carData, int low, int high) {
    int pivot = carData[high].getHighwayMPG();
    int up = low;
    int down = high - 1;
    while (up <= down) {
        while (up <= down && carData[up].getHighwayMPG() <= pivot) {
            up++;
        }
        while (down >= up && carData[down].getHighwayMPG() >= pivot) {
            down--;
        }
        if (up < down) {
            cars temp = carData[up];
            carData[up] = carData[down];
            carData[down] = temp;
        }
    }
    cars temp = carData[up];
    carData[up] = carData[high];
    carData[high] = temp;
    return up;
}

void quickSortH(std::vector<cars>& carData, int low, int high) {
    if (low < high) {
        int pivot = qPartitionH(carData, low, high);
        quickSortH(carData, low, pivot - 1);
        quickSortH(carData, pivot + 1, high);
    }
    return;
}

void quickSortGasHighway(std::vector<cars>& carData, std::vector<cars>& ans) {
    quickSortH(carData, 0, carData.size() - 1);
    for (int i = carData.size() - 1; i > carData.size() - 1001; i--) {
        ans.push_back(carData[i]);
    }
    return;
}

void mergeHW(std::vector<cars>& carData, int start, int mid, int end) {
    int len1 = mid - start + 1;
    int len2 = end - mid;
    std::vector<cars> vect1;
    std::vector<cars> vect2;
    for (int i = 0; i < len1; i++) {
        vect1.push_back(carData[start + i]);
    }
    for(int i = 0; i < len2; i++) {
        vect2.push_back(carData[mid + 1 + i]);
    }
    int i = 0;
    int j = 0;
    int k = start;
    while (i < len1 && j < len2) {
        if (vect1[i].getHighwayMPG() <= vect2[j].getHighwayMPG()) {
            carData[k] = vect1[i];
            i++;
        }
        else {
            carData[k] = vect2[j];
            j++;
        }
        k++;
    }
    while (i < len1) {
        carData[k] = vect1[i];
        i++;
        k++;
    }
    while (j < len2) {
        carData[k] = vect2[j];
        j++;
        k++;
    }
}

void mergeSortHW(std::vector<cars>& carData, int start, int end) {
    if (start == end) {
        return;
    }
    int mid = (start + end) / 2;
    mergeSortHW(carData, start, mid);
    mergeSortHW(carData, mid + 1, end);
    mergeHW(carData, start, mid, end);
}

void mergeSortGasHighway(std::vector<cars>& carData, std::vector<cars>& ans) {
    mergeSortHW(carData, 0, carData.size()-1);
    for (int i = carData.size() - 1; i > carData.size() - 1001; i--) {
        ans.push_back(carData[i]);
    }
    return;
}


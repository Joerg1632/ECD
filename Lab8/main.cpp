#include <iostream>
#include <vector>
#include <fstream>
#include <x86intrin.h>
#include <limits>
#include <random>
#include <algorithm>
#include <ctime>

void arrayTraverseDirect(std::vector<int>& arr) {
    for (int k = 0, i = 0; i < arr.size() * 3; i++) {
        k = arr[k];
    }
}

void directFilling(std::vector<int>& arr) {
    int value = 0;
    for (int& element : arr) {
        element = ++value;
    }
    arr[arr.size() - 1] = 0;
}

void reverseFilling(std::vector<int>& arr) {
    int value = arr.size() - 1;
    for (int i = arr.size() - 1; i > 0; i--) {
        arr[i] = --value;
    }
    arr[0] = 254;
}

void sattolo(std::vector<int>& arr) {
    int i, j, value = 0;
    for (auto& el : arr) {
        el = value++;
    }
    for (i = arr.size() - 1; i > 0; i--) {
        do {
            j = std::rand() % i;
        } while (j >= i);
        std::swap(arr[i], arr[j]);
    }
}

double measureAccessTime(void (*traversalFunction)(std::vector<int>&), std::vector<int>& arr, int repetitions = 3) {

    double minTime = std::numeric_limits<double>::max();
    traversalFunction(arr);
    arrayTraverseDirect(arr);
    for (int rep = 0; rep < repetitions; ++rep) {
        unsigned long long start = __rdtsc();
        arrayTraverseDirect(arr);
        unsigned long long end = __rdtsc();
        double elapsedTime = static_cast<double>(end - start);

 
        if (elapsedTime < minTime) {
            minTime = elapsedTime;
        }
    }

    return minTime/arr.size()/3;
}


int main() {
    srand(static_cast<unsigned int>(time(0)));

    const int minArraySize = 256;
    const int maxArraySize = 32 * 1024 * 1024;
    int step = 512;
    int percent10 = maxArraySize / 10;
    int wed = 10;

    std::vector<int> sizes;
    std::vector<double> directTimes;
    std::vector<double> reverseTimes;
    std::vector<double> randomTimes;

    for (int size = minArraySize; size <= maxArraySize; size += step) {

        sizes.push_back(size);

        std::vector<int> arr(size);

        directTimes.push_back(measureAccessTime(directFilling, arr));
        reverseTimes.push_back(measureAccessTime(reverseFilling, arr));
        randomTimes.push_back(measureAccessTime(sattolo, arr));
        if (size > percent10) {
            std::cout << wed << "% \n";
            wed += 10;
            percent10 += maxArraySize / 10;
        }

        if (size >= 3 * 1024 * 1024) {
            step = 1024 * 1024;
        }
        else if (size >= 512 * 1024) {
            step = 256 * 1024;
        }
        else {
            step = 1024; 
        }
    }

    std::ofstream outFile("access_times.txt");
    if (outFile.is_open()) {
        outFile << "Sizes\tDirect\tReverse\tRandom\n";
        for (size_t i = 0; i < sizes.size(); ++i) {
            outFile << sizes[i] << "\t" << directTimes[i] << "\t" << reverseTimes[i] << "\t" << randomTimes[i] << "\n";
        }
        outFile.close();
        std::cout << "Results saved to access_times.txt" << std::endl;
    }
    else {
        std::cerr << "Unable to open file!" << std::endl;
    }

    return 0;
}
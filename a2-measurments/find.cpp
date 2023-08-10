#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

// Function to find x < 7 in the middle of the vector (where all other elements are >= 7)
int std_find(const std::vector<int>& numbers, int valueToFindInMiddle) {
    auto itMiddle = std::find(numbers.begin(), numbers.end(), valueToFindInMiddle);
    if (itMiddle != numbers.end()) {
        return *itMiddle;
    } else {
        return -1; // Element not found
    }
}

// Function to find x < 7 in the vector where no element is 7
int std_find_if(const std::vector<int>& numbers, int valueToFindNotInVector) {
    auto itNotInVector = std::find_if(numbers.begin(), numbers.end(), [valueToFindNotInVector](int x) { return x < valueToFindNotInVector; });
    if (itNotInVector != numbers.end()) {
        return *itNotInVector;
    } else {
        return -1; // Element not found
    }
}


int main() {
    const int numValues = 10000000;
    std::vector<int> numbers(numValues, 9);

    // Find x < 7 in the middle of the vector (where all other elements are >= 7)
    int valueToFindInMiddle = 7;
    numbers[numValues / 2] = valueToFindInMiddle; // Put 7 in the middle
    auto startMiddle = std::chrono::high_resolution_clock::now();
    int resultMiddle = std_find(numbers, valueToFindInMiddle);
    auto endMiddle = std::chrono::high_resolution_clock::now();
    if (resultMiddle != -1) {
        std::cout << "Value " << resultMiddle << " found in the middle of the vector." << std::endl;
    } else {
        std::cout << "Value " << valueToFindInMiddle << " not found in the vector" << std::endl;
    }
    auto durationMiddle = std::chrono::duration_cast<std::chrono::microseconds>(endMiddle - startMiddle).count();
    std::cout << "Time taken to find x < 7 in the middle: " << durationMiddle << " microseconds" << std::endl;

    // Find x < 7 in the vector where no element is 7
    int valueToFindNotInVector = 7;
    auto startNotInVector = std::chrono::high_resolution_clock::now();
    int resultNotInVector = std_find_if(numbers, valueToFindNotInVector);
    auto endNotInVector = std::chrono::high_resolution_clock::now();
    if (resultNotInVector != -1) {
        std::cout << "Value " << resultNotInVector << " found in the vector where no element is 7." << std::endl;
    } else {
        std::cout << "Value " << valueToFindNotInVector << " not found in the vector." << std::endl;
    }
    auto durationNotInVector = std::chrono::duration_cast<std::chrono::microseconds>(endNotInVector - startNotInVector).count();
    std::cout << "Time taken to find x < 7 in the vector where no element is 7: " << durationNotInVector << " microseconds." << std::endl;

    return 0;
}

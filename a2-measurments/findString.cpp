#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include <chrono>

std::string generateRandomString() {
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, chars.size() - 1);

    std::string randomString;
    for (int i = 0; i < 20; ++i) {
        randomString += chars[distribution(generator)];
    }
    return randomString;
}

int main() {
    const int numValues = 1000000;
    std::vector<std::string> strings;

    for (int i = 0; i < numValues; ++i) {
        strings.push_back(generateRandomString());
    }

    std::string stringToFind = "XXXXXXXXXXXXXXXXXXX";
    auto it = std::find(strings.begin(), strings.end(), stringToFind);

    if (it != strings.end()) {
        std::cout << "String " << stringToFind << " found in the vector." << std::endl;
    } else {
        std::cout << "String " << stringToFind << " not found in the vector" << std::endl;
    }

    strings[numValues / 2] = stringToFind;

    it = std::find(strings.begin(), strings.end(), stringToFind);

    if (it != strings.end()) {
        std::cout << "String " << stringToFind << " found in the middle of the vector." << std::endl;
    } else {
        std::cout << "String " << stringToFind << " not found in the middle of the vector" << std::endl;
    }

    return 0;
}

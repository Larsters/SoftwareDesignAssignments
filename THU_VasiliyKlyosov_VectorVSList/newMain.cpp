#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <chrono>
#include <random>

// Function to generate N unique random integers and insert them into a container
template <typename Container>
void generateAndInsert(Container& sequence, int N) {
    // Create a set with unique numbers
    std::set<int> uniqueNumbers;
    for (int i = 1; i <= 1000000; ++i) {
        uniqueNumbers.insert(i);
    }

    // Shuffle the set to get random order
    std::default_random_engine generator(std::time(0));
    std::vector<int> shuffledNumbers(uniqueNumbers.begin(), uniqueNumbers.end());
    std::shuffle(shuffledNumbers.begin(), shuffledNumbers.end(), generator);

    // Take the first N elements from the shuffled set
    for (int i = 0; i < N; ++i) {
        int num = shuffledNumbers[i];
        // Insert the number into the container
        sequence.insert(sequence.end(), num);
    }
}

// Function to remove elements one at a time based on random positions
template <typename Container>
void removeElements(Container& sequence) {
    if constexpr (std::is_same_v<Container, std::list<int>>) {
        // For lists, directly erase elements using iterators
        std::default_random_engine generator(std::time(0));
        while (!sequence.empty()) {
            auto it = std::next(sequence.begin(), std::uniform_int_distribution<int>(0, sequence.size() - 1)(generator));
            sequence.erase(it);
        }
    } else if constexpr (std::is_same_v<Container, std::vector<int>> || std::is_same_v<Container, std::set<int>>) {
        // For vectors and sets, convert to an iterator before erasing
        std::default_random_engine generator(std::time(0));
        while (!sequence.empty()) {
            auto it = std::next(sequence.begin(), std::uniform_int_distribution<int>(0, sequence.size() - 1)(generator));
            sequence.erase(it);
        }
    } else {
        std::cerr << "Unsupported container type." << std::endl;
    }
}

int main() {
    int N;
    std::cout << "How many unique numbers to generate: ";
    std::cin >> N;

    std::list<int> myList;
    std::vector<int> myVector;
    std::set<int> mySet;

    // Insertion time comparison
    auto start = std::chrono::high_resolution_clock::now();
    generateAndInsert(myList, N);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> listInsertionTime = end - start;

    start = std::chrono::high_resolution_clock::now();
    generateAndInsert(myVector, N);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> vectorInsertionTime = end - start;

    start = std::chrono::high_resolution_clock::now();
    generateAndInsert(mySet, N);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> setInsertionTime = end - start;

    // Output the insertion times
    std::cout << "Insertion time for list: " << listInsertionTime.count() << " seconds\n";
    std::cout << "Insertion time for vector: " << vectorInsertionTime.count() << " seconds\n";
    std::cout << "Insertion time for set: " << setInsertionTime.count() << " seconds\n";

    // Removal time comparison
    start = std::chrono::high_resolution_clock::now();
    removeElements(myList);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> listRemovalTime = end - start;

    start = std::chrono::high_resolution_clock::now();
    removeElements(myVector);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> vectorRemovalTime = end - start;

    start = std::chrono::high_resolution_clock::now();
    removeElements(mySet);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> setRemovalTime = end - start;

    // Output the removal times; std::fixed so that it wouldn't print scientific notations
    std::cout << std::fixed;
    std::cout << "Removal time for list: " << std::setprecision(6) << listRemovalTime.count() << " seconds\n";
    std::cout << "Removal time for vector: " << std::setprecision(6) << vectorRemovalTime.count() << " seconds\n";
    std::cout << "Removal time for set: " << std::setprecision(6) << setRemovalTime.count() << " seconds\n";

    return 0;
}

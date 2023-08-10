#include <iostream>
#include <set>
#include <algorithm>
#include <random>
#include <ctime>

// Function to generate N unique random integers and insert them into a sequence
void generateAndInsert(std::set<int>& sequence, int N) {
    // Create a set with unique numbers
    std::set<int> uniqueNumbers;
    for (int i = 1; i <= 100000; ++i) {
        uniqueNumbers.insert(i);
    }

    // Shuffle the set to get random order
    std::default_random_engine generator(std::time(0));
    std::vector<int> shuffledNumbers(uniqueNumbers.begin(), uniqueNumbers.end());
    std::shuffle(shuffledNumbers.begin(), shuffledNumbers.end(), generator);

    // Take the first N elements from the shuffled set
    for (int i = 0; i < N; ++i) {
        int num = shuffledNumbers[i];
        // Insert the number into the set (it will be automatically sorted)
        sequence.insert(num);

        // Print sequence after each insertion
        for (int j : sequence) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

void removeElements(std::set<int>& sequence) {
    std::default_random_engine generator(std::time(0));

    while (!sequence.empty()) {
        int randomElement = *(std::next(sequence.begin(), std::uniform_int_distribution<int>(0, sequence.size() - 1)(generator)));
        sequence.erase(randomElement);
        for (int j : sequence) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}



int main() {
    int N;
    std::cout << "How many unique numbers to generate: ";
    std::cin >> N;

    std::set<int> sequence;
    generateAndInsert(sequence, N);

    std::cout << "Removing elements one at a time:\n";
    removeElements(sequence);

    return 0;
}

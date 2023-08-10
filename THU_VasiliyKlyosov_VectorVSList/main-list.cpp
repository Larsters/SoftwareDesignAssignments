#include <iostream>
#include <list>
#include <algorithm>
#include <random>
#include <ctime>

// Function to generate N unique random integers and insert them into a sequence
void generateAndInsert(std::list<int>& sequence, int N) {
    // Create a list with unique numbers
    std::list<int> uniqueNumbers;
    for (int i = 1; i <= 100000; ++i) {
        uniqueNumbers.push_back(i);
    }

    // Shuffle the list to get random order
    std::default_random_engine generator(std::time(0));
    std::vector<int> shuffledNumbers(uniqueNumbers.begin(), uniqueNumbers.end());
    std::shuffle(shuffledNumbers.begin(), shuffledNumbers.end(), generator);

    // Take the first N elements from the shuffled list
    for (int i = 0; i < N; ++i) {
        int num = shuffledNumbers[i];
        // Insert the number in its proper position
        auto it = std::lower_bound(sequence.begin(), sequence.end(), num);
        sequence.insert(it, num);

        // Print sequence after each insertion
        for (int j : sequence) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

void removeElements(std::list<int>& sequence) {
    // Create a random number generator
    std::default_random_engine generator(std::time(0));
    std::uniform_int_distribution<int> distribution(0, sequence.size() - 1);

    while (!sequence.empty()) {
        int pos = distribution(generator);
        auto it = sequence.begin();
        std::advance(it, pos);

        if (it != sequence.end()) {
            sequence.erase(it);
        }

        // Print the sequence after each removal
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

    std::list<int> sequence;
    generateAndInsert(sequence, N);

    std::cout << "Removing elements one at a time:\n";
    removeElements(sequence);

    return 0;
}

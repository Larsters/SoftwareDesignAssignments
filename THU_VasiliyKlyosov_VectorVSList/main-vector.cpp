#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

// Function to generate N random integers and insert them into a sequence
void generateAndInsert(std::vector<int>& sequence, int N) {
    // Create a random number generator
    std::default_random_engine generator(std::time(0));
    std::uniform_int_distribution<int> distribution(1, 100); // Change range

    for (int i = 0; i < N; i++) {
        int num = distribution(generator);
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

// Function to remove elements one at a time based on random positions
void removeElements(std::vector<int>& sequence) {
    // Create a random number generator
    std::default_random_engine generator(std::time(0));
    std::uniform_int_distribution<int> distribution(0, sequence.size() - 1);

    while (!sequence.empty()) {
        int pos = distribution(generator);
        sequence.erase(sequence.begin() + pos);

        // Print the sequence after each removal
        for (int j : sequence) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}


int main() {
    int N;
    std::cout << "How many numbers to generate: ";
    std::cin >> N;

    std::vector<int> sequence;
    generateAndInsert(sequence, N);

    std::cout << "Removing elements one at a time:\n";
    removeElements(sequence);

    return 0;
}

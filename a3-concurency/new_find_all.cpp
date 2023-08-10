#include <iostream>
#include <vector>
#include <future>
#include <queue>
#include <mutex>
#include <chrono>
#include <random>

template <typename T>
std::vector<T*> find_all(std::vector<T>& v, const T& val, typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end) {
    std::vector<T*> res;
    for (auto it = begin; it != end; ++it) {
        if (*it == val) {
            res.push_back(&(*it));
        }
    }
    return res;
}

template <typename T>
std::vector<T*> find_all(std::vector<T>& v, const T& val) {
    return find_all(v, val, v.begin(), v.end());
}

template <typename T>
class SynchronizedQueue {
public:
    void push(const T& value) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(value);
    }
    T pop() {
        std::lock_guard<std::mutex> lock(mutex_);
        T value = queue_.front();
        queue_.pop();
        return value;
    }
    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
};

template <typename T>
std::vector<T*> find_all_parallel(std::vector<T>& v, const T& val) {
    const size_t numThreads = 10;
    const size_t elementsPerThread = v.size() / numThreads;
    SynchronizedQueue<std::vector<T*>> resultQueue;

    auto find_all_thread = [&](typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end) {
        std::vector<T*> threadResult = find_all(v, val, begin, end);
        resultQueue.push(threadResult);
    };

    std::vector<std::future<void>> futures;
    for (size_t i = 0; i < numThreads; ++i) {
        auto begin = v.begin() + i * elementsPerThread;
        auto end = (i == numThreads - 1) ? v.end() : (begin + elementsPerThread);
        futures.push_back(std::async(std::launch::async, find_all_thread, begin, end));
    }

    for (auto& f : futures) {
        f.wait();
    }

    std::vector<T*> finalResult;
    while (!resultQueue.empty()) {
        auto threadResult = resultQueue.pop();
        finalResult.insert(finalResult.end(), threadResult.begin(), threadResult.end());
    }

    return finalResult;
}

std::vector<int> generateRandomIntVector(size_t size, int minVal, int maxVal) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(minVal, maxVal);

    std::vector<int> randomVector(size);
    for (size_t i = 0; i < size; ++i) {
        randomVector[i] = distribution(generator);
    }
    return randomVector;
}

std::vector<std::string> generateRandomStringVector(size_t size) {
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, chars.size() - 1);

    std::vector<std::string> randomVector(size);
    for (size_t i = 0; i < size; ++i) {
        std::string randomString;
        for (int j = 0; j < 20; ++j) {
            randomString += chars[distribution(generator)];
        }
        randomVector[i] = randomString;
    }
    return randomVector;
}

int main() {
    const size_t numValues = 1000000;

    // Generate input vectors
    std::vector<int> intVector = generateRandomIntVector(numValues, 1, 10);
    std::vector<std::string> stringVector = generateRandomStringVector(numValues);

    // Test sequential find_all for integers
    auto start = std::chrono::high_resolution_clock::now();
    auto resultInt = find_all(intVector, 4);
    auto end = std::chrono::high_resolution_clock::now();

    // Output results for integers
    std::cout << "Sequential Find for Integers:" << std::endl;
    for (const auto& ptr : resultInt) {
        std::cout << *ptr << " ";
    }
    std::cout << std::endl;

    // Execution time
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Sequential Execution time for Integers: " << elapsed.count() << " seconds" << std::endl;

    // Test sequential find_all for strings
    start = std::chrono::high_resolution_clock::now();
    auto resultString = find_all(stringVector, std::string("DENMARK"));
    end = std::chrono::high_resolution_clock::now();

    // Output results for strings
    std::cout << "Sequential Find for Strings:" << std::endl;
    for (const auto& ptr : resultString) {
        std::cout << *ptr << " ";
    }
    std::cout << std::endl;

    // Execution time
    elapsed = end - start;
    std::cout << "Sequential Execution time for Strings: " << elapsed.count() << " seconds" << std::endl;

    // Test concurrent find_all for integers
    start = std::chrono::high_resolution_clock::now();
    auto resultIntParallel = find_all_parallel(intVector, 9);
    end = std::chrono::high_resolution_clock::now();

    // Output results for integers
    std::cout << "Concurrent Find for Integers:" << std::endl;
    for (const auto& ptr : resultIntParallel) {
        std::cout << *ptr << " ";
    }
    std::cout << std::endl;

    // Execution time
    elapsed = end - start;
    std::cout << "Concurrent Execution time for Integers: " << elapsed.count() << " seconds" << std::endl;

    // Test concurrent find_all for strings
    start = std::chrono::high_resolution_clock::now();
    auto resultStringParallel = find_all_parallel(stringVector, std::string("Denmark"));
    end = std::chrono::high_resolution_clock::now();

    // Output results for strings
    std::cout << "Concurrent Find for Strings:" << std::endl;
    for (const auto& ptr : resultStringParallel) {
        std::cout << *ptr << " ";
    }
    std::cout << std::endl;

    // Execution time
    elapsed = end - start;
    std::cout << "Concurrent Execution time for Strings: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}

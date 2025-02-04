#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>

/*
Exercise: Basic Statistics Calculator

Implement a Statistics calculator that can process a series of integers and compute basic statistics.

Requirements:
1. Complete the Stats class implementation below
2. The class should store the following statistics:
   - sum: The sum of all numbers
   - max: The maximum value
   - avg: The average (mean) value as a double
3. The program should handle standard input correctly in normal mode

Notes:
- Handle empty input appropriately
- Consider edge cases like negative numbers
- The calculate() method should process the input vector and update all statistics
*/

class Stats {
    public:
        Stats() = default;
        Stats(const std::vector<int>& data) {
            calculate(data);
        }

        void calculate(const std::vector<int>& data);

        int sum{0};
        int max{0};
        double avg{0.0};
};

void
Stats::calculate(const std::vector<int>& data) {
    // Process the input vector and update sum, max, and avg
    if (data.size() < 1)
        return;
    this->max = data[1];
    for (auto num : data) {
        this->sum += num;
        if (num > this->max) {
            this->max = num;
        }
    }
    this->avg = (double)this->sum / data.size();
}

bool unit_test(const int n,
               const std::vector<int>& data,
               const int expected_sum,
               const int expected_max,
               const double expected_avg) {
    bool pass = true;
    Stats s(data);
    if (s.sum != expected_sum) {
        std::cerr << "Data sum was not expected value, expected "
            << expected_sum << " got " << s.sum << std::endl;
        pass = false;
    }
    if (s.max != expected_max) {
        std::cerr << "Data max was not expected value, expected "
            << expected_max << " got " << s.max << std::endl;
        pass = false;
    }
    if (s.avg != expected_avg) {
        std::cerr << "Data avg was not expected value, expected "
            << expected_avg << " got " << s.avg << std::endl;
        pass = false;
    }
    if (pass) {
        std::cout << "Test " << n << " passed!" << std::endl;
    } else {
        std::cout << "Test " << n << " failed!" << std::endl;
    }
    return pass;
}

int main(int argc, char** argv) {
    if (argc >= 2 && strcmp(argv[1], "--test") == 0) {
        std::cout << "Running unit tests:\n" << std::endl;
        if (!unit_test(1, {}, 0, 0, 0.0))
            return 1;
        if (!unit_test(2, {-1, -2, -3}, -6, -1, -2.0))
            return 1;
        if (!unit_test(3, {10000, -10000}, 0, 10000, 0.0))
            return 1;
        if (!unit_test(4, {0, 0, 0, 0, 0, 0, 0}, 0, 0, 0.0))
            return 1;
        if (!unit_test(5, {1, 1, 1, 1, 1, 1, 1}, 7, 1, 1.0))
            return 1;
        std::cout << "\nAll tests passed!" << std::endl;
        return 0;
    }
    std::vector<int> data;
    // Read integers from stdin into data until EOF or invalid input
    // Exit with appropriate message if input is invalid
    for (std::string line; std::getline(std::cin, line);) {
        // processed_chars contains the number of chars that have been
        // converted to an integer. If that number if less than the
        // length of the string, then some of the chars were not part
        // of the parsed integer, meaning the input was invalid
        std::size_t processed_chars = 0;
        try {
            int read_char = std::stoi(line, &processed_chars);
            if (processed_chars != line.size()) {
                std::cerr << "Line `" << line
                    << "` contains an invalid integer!" << std::endl;
                return 1;
            }
            data.push_back(read_char);
        } catch (std::invalid_argument const& _err) {
            // stoi is the only thing that could be throwing this
            // exception so we don't need to inspect _err
            std::cerr << "Line `" << line
                << "` contains an invalid integer!" << std::endl;
            return 1;
        }
    }
    Stats s(data);
    
    std::cout << "Count: " << data.size() << std::endl;
    std::cout << "Sum:   " << s.sum << std::endl;
    std::cout << "Max:   " << s.max << std::endl;
    std::cout << "Avg:   " << std::fixed << std::setprecision(6)
              << s.avg << std::endl;
    
    return 0;
}

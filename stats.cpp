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
    for (auto num : data) {
        this->sum += num;
        if (num > this->max) {
            this->max = num;
        }
    }
    this->avg = (double)this->sum / data.size();
}

int main(int argc, char** argv) {
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


#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(void) {
    std::ifstream       file("part1.txt");
    std::string         line;
    std::vector<int>    left, right;
    long                sum;

    if (!file.is_open()) {
        std::cout << "File not open." << std::endl;
        return (1);
    }

    while (file and !file.eof()) {
        line.clear();
        std::getline(file, line);
        if (line.empty())
            break;
        // skip all the starting spaces
        line = line.substr(line.find_first_not_of(' '));
        left.push_back(std::stoi(line));
        // skip the first number
        line = line.substr(line.find_first_of(' '));
        right.push_back(std::stoi(line));
    }

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    sum = 0;
    while (left.size() > 0 and right.size() > 0) {
        sum += std::abs(left.front() - right.front());
        left.erase(left.begin());
        right.erase(right.begin());
    }

    std::cout << "The total distance between the two lists is " << sum << std::endl;

    return (0);
}


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

typedef std::vector<std::string> StringVector;

std::string readFile(std::string filename) {
    std::ifstream       file(filename);
    std::stringstream   buffer;

    if (!file.is_open())
        throw std::runtime_error("Error: file not open!");

    buffer << file.rdbuf();
    return buffer.str();
}

StringVector split(std::string str, std::string separators, bool removeSeparator=true) {
    std::vector<std::string>    strs;
    size_t                      i = 0, j = 0;

    while (i < str.size()) {
        if (separators.find(str[i]) == std::string::npos) {
            i++;
            continue;
        }
        strs.push_back(str.substr(j, i - j + !removeSeparator));
        j = ++i;
    }
    if (j < i)
        strs.push_back(str.substr(j, i - j + !removeSeparator));
    return strs;
}

std::string reverse(std::string str) {
    return std::string(str.rbegin(), str.rend());
}

size_t countHorizontal(StringVector strs, std::string needle) {
    std::string reverseNeedle = reverse(needle);
    size_t      count, i;

    count = 0;
    for (const std::string row : strs) {
        // std::cout << row << "|";
        for (i = 0; i < row.size() - needle.size(); i++) {
            if (row.compare(i, needle.size(), needle) == 0 or row.compare(i, reverseNeedle.size(), reverseNeedle) == 0) {
                i += needle.size() - 1;
                // std::cout << "*";
                count++;
            }
        }
        // std::cout << std::endl;
    }
    return count;
}

size_t  countVertical(StringVector strs, std::string needle) {
    std::string reverseNeedle = reverse(needle), tmp;
    size_t  count, row, col, i;

    count = 0;
    for (row = 0; row < strs.size(); row++) {
        for (col = 0; col < strs[row].size(); col++) {
            if (strs[row][col] != needle.front() and strs[row][col] != needle.back())
                continue;
            i = 0;
            tmp = (strs[row][col] == needle.front()) ? needle : reverseNeedle;
            while (i < tmp.size() and row + i < strs.size() and strs[row + i][col] == tmp[i])
                i++;
            count += (i == tmp.size());
        }
    }
    return count;
}

size_t  countDiagonal(StringVector strs, std::string needle) {
    std::string reverseNeedle = reverse(needle), tmp;
    size_t  count, row, col, i, j;

    count = 0;
    for (row; row < strs.size(); row++) {
        for (col = 0; col < strs[row].size(); col++) {
            if (strs[row][col] != needle.front() and strs[row][col] != needle.back())
                continue;
            tmp = (strs[row][col] == needle.front()) ? needle : reverseNeedle;
            // check bottom left
            i, j = 0, 0;
            while (i < tmp.size() and j < tmp.size()
                    and row + i < strs.size() and col - j < strs[row + i].size()
                    and strs[row + i][col - j] == tmp[i]) {
                i++;
                j++;
            }
            count += (i == tmp.size() and j == tmp.size());
            // check bottom right
            i, j = 0, 0;
            while (i < tmp.size() and j < tmp.size()
                    and row + i < strs.size() and col + j < strs[row + i].size()
                    and strs[row + i][col + j] == tmp[i]) {
                i++;
                j++;
            }
            count += (i == tmp.size() and j == tmp.size());
        }
    }
    return count;
}

// 
int main(void) {
    std::string     text = readFile("part1.txt");
    StringVector    strs;
    size_t          count;

    strs = split(text, " \n\t");

    count = countHorizontal(strs, "XMAS") + countVertical(strs, "XMAS") + countDiagonal(strs, "XMAS");

    std::cout << "The number of times XMAS appears is " << count << std::endl;

    return (0);
}

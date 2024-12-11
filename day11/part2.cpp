
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <forward_list>
#include <cmath>
#include <set>

using String = std::string;

template <typename T>
using Vector = std::vector<T>;

template <typename T>
using Set = std::set<T>;

template <typename T>
using List = std::forward_list<T>;

template <typename T>
using Pair = std::pair<T,T>;

using StringVector = Vector<String>;
using LongVector = Vector<long>;
using LongList = List<long>;
using CharVector = Vector<char>;
using IntPair = Pair<int>;




template <typename T>
void    printVector(Vector<T> vect) {
    std::cout << "[";
    for (size_t i = 0; i < vect.size() - 1; i++)
        std::cout << vect[i] << ", ";
    std::cout << vect.back() << "]" << std::endl;
}

template <typename T>
void    printList(List<T> mylist) {
    std::cout << "[";
    for (auto it = mylist.begin(); it != mylist.end(); ++it)
        std::cout << ((it != mylist.begin()) ? " " : "") << *it;
    std::cout << "]" << std::endl;
}

String  readFile(String filename) {
    std::ifstream       file(filename);
    std::stringstream   buffer;

    if (!file.is_open())
        throw std::runtime_error("Error: file not open!");

    buffer << file.rdbuf();
    return buffer.str();
}

StringVector    split(String str, String separators, bool removeSeparator=true) {
    StringVector    strs;
    String          tmp;
    size_t          i = 0, j = 0;

    while (i < str.size()) {
        if (separators.find(str[i]) == String::npos) {
            i++;
            continue;
        }
        tmp = str.substr(j, i - j + !removeSeparator);
        if (!removeSeparator or not tmp.empty())
            strs.push_back(tmp);
        j = ++i;
    }
    if (j < i) {
        if (!removeSeparator or not tmp.empty())
            strs.push_back(str.substr(j, i - j + !removeSeparator));
    }
    return strs;
}

LongList   mapToLong(StringVector arr) {
    LongVector  nums;

    for (const String & num : arr) {
        nums.push_back(std::stol(num));
    }
    return LongList(nums.begin(), nums.end());
}

int numOfDigits(long num) {
    int digits = 0;
    do {
        num /= 10;
        digits++;
    } while (num > 0);
    return digits;
}

void  blink(LongList & stones) {
    long    n;
    int     digits;

    for (auto it = stones.begin(); it != stones.end(); ++it) {
        n = *it;
        // std::cout << "n: " << n << " -> ";
        // printList(stones);
        if (n == 0) {
            *it = 1;
            continue;
        }
        digits = numOfDigits(n);
        if (digits % 2 != 0) {
            *it = n * 2024;
            continue;
        }

        digits = std::pow(10, digits / 2);
        // std::cout << "digits: " << digits << std::endl;
        // std::cout << "1: " << *it << std::endl;
        *it = n / digits;
        // std::cout << "2: " << *it << std::endl;
        it = stones.insert_after(it, n % digits);
        // std::cout << "3: " << *it << std::endl;
    }
}

// 224529
int main(void) {
    String      text = readFile("part1.txt");
    LongList    stones = mapToLong(split(text, " "));

    // printList(stones);

    for (size_t iterations = 35; iterations > 0; iterations--){
        blink(stones);
        // std::cout << "ite: " << 75 - iterations << std::endl;
    }

    // printList(stones);

    int count = 0;
    for (auto it = stones.begin(); it != stones.end(); ++it)
        count++;
    std::cout << "The total number of stones is " << count << std::endl;
    return (0);
}

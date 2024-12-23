
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <map>

using String = std::string;

template <typename T>
using Vector = std::vector<T>;

template <typename T>
using Set = std::set<T>;

template <typename T, typename U>
using Map = std::map<T, U>;

template <typename T>
using Pair = std::pair<T,T>;

using StringVector = Vector<String>;
using LongVector = Vector<long>;
using CharVector = Vector<char>;
using IntPair = Pair<int>;



struct Point {
    u_int   x;
    u_int   y;

    Point(): x(0), y(0) { }
    Point(const u_int &x, const u_int &y): x(x), y(y) { }
    Point(const Point &p): x(p.x), y(p.y) { }

    Point operator +(const Point &p) const {
        return Point(this->x + p.x, this->y + p.y);
    }

    Point &operator =(const Point &p) {
        this->x = p.x;
        this->y = p.y;
        return *this;
    }

    Point &operator +=(const Point &p) {
        this->x += p.x;
        this->y += p.y;
        return *this;
    }

    bool operator ==(const Point &p) const {
        return this->x == p.x and this->y == p.y;
    }

    bool operator !=(const Point &p) const {
        return this->x != p.x or this->y != p.y;
    }

    u_int to_int() const {
        return x * 1000 + y;
    }

    float distance(const Point &p) {
        return std::sqrt(std::pow(x + p.x, 2) + std::pow(y + p.y, 2));
    }
};

std::ostream &operator <<(std::ostream &out, const Point &p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}




template <typename T>
void    print(Vector<T> vect) {
    if (vect.size() == 0) {
        std::cout << "[]" << std::endl;
        return;
    }
    std::cout << "[";
    for (size_t i = 0; i < vect.size() - 1; i++)
        std::cout << vect[i] << ", ";
    std::cout << vect.back() << "]" << std::endl;
}

void    print(StringVector strs) {
    for (const String &line : strs)
        std::cout << line << std::endl;
}

template <typename T, typename U>
void    print(const Map<T, U> &map) {
    for (auto const &pair : map) {
        std::cout << pair.first << ": " << pair.second << " | ";
    }
    std::cout << std::endl;
}

String  readFile(String filename) {
    std::ifstream       file(filename);
    std::stringstream   buffer;

    if (!file.is_open())
        throw std::runtime_error("Error: file not open!");

    buffer << file.rdbuf();
    return buffer.str();
}

StringVector    split(String str, String separators) {
    StringVector    strs;
    String          tmp;
    size_t          i = 0, j = 0;

    while (i < str.size()) {
        if (separators.find(str[i]) == String::npos) {
            i++;
            continue;
        }
        tmp = str.substr(j, i - j);
        if (not tmp.empty())
            strs.push_back(tmp);
        j = ++i;
    }
    if (j < i) {
        if (not tmp.empty())
            strs.push_back(str.substr(j, i - j));
    }
    return strs;
}

StringVector    genMap(const u_int width, const u_int height, const char filler='+') {
    return StringVector(height, String(width, filler));
}

Vector<Point> parsePoints(const String &input) {
    Vector<Point>   points;
    StringVector    nums;

    for (auto line : split(input, "\n")) {
        nums = split(line, ",");
        points.push_back(Point(std::stoi(nums.front()), std::stoi(nums.back())));
    }
    return points;
}

Vector<Point> dirs({
    Point(0, -1),
    Point(0, +1),
    Point(-1, 0),
    Point(+1, 0),
});

Vector<Point> possibleDirs(const StringVector &map, const Point &p, const Set<u_int> visited) {
    Vector<Point>   possibles;
    Point           next;

    for (auto dir : dirs) {
        next = p + dir;
        if (next.y >= map.size() or next.x >= map[next.y].size())
            continue;
        if (map[next.y][next.x] == '#' or visited.find(next.to_int()) != visited.end())
            continue;
        possibles.push_back(next);
    }
    std::sort(possibles.begin(), possibles.end(), [](Point a, Point b) {
        return a.distance(Point(6, 6)) > b.distance(Point(6, 6));
    });
    return possibles;
}

void    findPath(StringVector &map, Point p, Set<u_int> &visited, u_int steps) {
    Point next;

    map[p.y][p.x] = '@';
    print(map);
    map[p.y][p.x] = '+';
    String text;
    std::getline(std::cin, text);

    if (p.y == map.size() - 1 and p.x == map[p.y].size() - 1) {
        std::cout << "Reached end with " << steps << " steps" << std::endl;
        return;
    }

    visited.insert(p.to_int());

    Vector<Point> possibles = possibleDirs(map, p, visited);

    for (auto next : possibles)
        findPath(map, next, visited, steps + 1);
}

// 
int main(void) {
    String          text = readFile("example.txt");
    StringVector    map = genMap(7, 7);
    Vector<Point>   points = parsePoints(text);
    Set<u_int>      visited;

    points.resize(12);

    for (const Point &p : points)
        map[p.y][p.x] = '#';

    findPath(map, Point(0, 0), visited, 0);

    return (0);
}

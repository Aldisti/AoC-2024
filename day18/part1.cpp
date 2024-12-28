
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
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

template <typename T>
using Queue = std::queue<T>;

using StringVector = Vector<String>;
using LongVector = Vector<long>;
using CharVector = Vector<char>;
using IntPair = Pair<int>;



struct Point {
    u_int   x;
    u_int   y;
    u_int   d;

    Point(): x(0), y(0), d(0) { }
    Point(const u_int &x, const u_int &y): x(x), y(y), d(0) { }
    Point(const u_int &x, const u_int &y, const u_int &d): x(x), y(y), d(d) { }
    Point(const Point &p): x(p.x), y(p.y), d(p.d) { }

    Point &operator =(const Point &p) {
        this->x = p.x;
        this->y = p.y;
        this->d = p.d;
        return *this;
    }

    Point &operator +=(const Point &p) {
        this->x += p.x;
        this->y += p.y;
        return *this;
    }

    Point operator +(const Point &p) const { return Point(this->x + p.x, this->y + p.y); }

    bool operator <(const Point &p) const { return x < p.x and y < p.y; }

    bool operator ==(const Point &p) const { return x == p.x and y == p.y; }

    bool operator !=(const Point &p) const { return x != p.x or y != p.y; }

    u_int to_int() const { return x * 1000 + y; }

    float distance(const Point &p) {
        return std::sqrt(std::pow(x + p.x, 2) + std::pow(y + p.y, 2));
    }
};

std::ostream &operator <<(std::ostream &out, const Point &p) {
    return out << "(" << p.x << ", " << p.y << ", " << p.d << ")";
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

template <typename T>
void    print(const Set<T> &set) {
    std::cout << "[" << *(set.begin());
    for (auto it = set.begin(); it != set.end();) {
        ++it;
        std::cout << ", " << *it;
    }
    std::cout << "]" << std::endl;
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

u_int findPath(const StringVector &map, Set<u_int> &visited) {
    Point p, next;
    Queue<Point> queue;
    queue.push(p);
    visited.insert(p.to_int());
    while (not queue.empty()) {
        p = queue.front();
        queue.pop();
 
        if (p == Point(map.size() - 1, map[0].size() - 1))
            return p.d;
 
        for (const Point &dir : dirs) {
            Point next = p + dir;
            if (next.y >= map.size() or next.x >= map[next.y].size()
                    or visited.find(next.to_int()) != visited.end())
                continue;
            next.d = p.d + 1;
            queue.push(next);
            visited.insert(next.to_int());
        }
    }
    return 0;
}

// 338
int main(void) {
    String          text = readFile("input.txt");
    u_int           size = 71;
    StringVector    map = genMap(size, size);
    Vector<Point>   points = parsePoints(text);
    Set<u_int>      visited;

    points.resize(1024);

    for (const Point &p : points) {
        if (p.y >= map.size() or p.x >= map[p.y].size())
            continue;
        visited.insert(p.to_int());
        map[p.y][p.x] = '#';
    }

    u_int steps = findPath(map, visited);

    std::cout << "The minimum number of steps is " << steps << std::endl;
    return (0);
}


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <forward_list>
#include <cmath>
#include <set>
#include <map>

using String = std::string;

template <typename T>
using Vector = std::vector<T>;

template <typename T>
using Set = std::set<T>;

template <typename T>
using List = std::forward_list<T>;

template <typename T, typename U>
using Map = std::map<T, U>;

template <typename T>
using Pair = std::pair<T,T>;

template <typename T>
using PairVector = Vector<Pair<T>>;

using StringVector = Vector<String>;
using LongVector = Vector<long>;
using LongList = List<long>;
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

    Point operator =(const Point &p) {
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
};

std::ostream &operator <<(std::ostream &out, Point const &p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}


template <typename T>
void    print(Vector<T> vect) {
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
void    print(List<T> mylist) {
    std::cout << "[";
    for (auto it = mylist.begin(); it != mylist.end(); ++it)
        std::cout << ((it != mylist.begin()) ? " " : "") << *it;
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

Map<char, Point>    dirs({
    {'^', Point(0, -1)}, // up
    {'v', Point(0, +1)}, // down
    {'<', Point(-1, 0)}, // left
    {'>', Point(+1, 0)}  // right
});

Point   findPoint(const StringVector &map, const char &c) {
    for (u_int y = 0; y < map.size(); y++)
        for (u_int x = 0; x < map[y].size(); x++)
            if (map[y][x] == c)
                return Point(x, y);
    return Point();
}

void    findPaths(const StringVector &map, Point p, const Point &dir, u_int score, Vector<u_int> &paths) {
    if (score > 100000)
        return;
    Point next = p + dir;
    if (map[next.y][next.x] == 'E') {
        paths.push_back(score);
        std::cout << "Reached end with " << score << " score" << std::endl;
        u_int smallest = paths[0];
        for (auto score : paths) {
            if (score < smallest)
                smallest = score;
        }
        std::cout << smallest << std::endl;
        return;
    }

    // std::cout << "Checking " << p << " -> " << (p + dir) << " " << score << std::endl;
    if (map[next.y][next.x] == '.') {
        // score.push_back(next);
        findPaths(map, next, dir, score + 1, paths);
    }

    // String tmp;
    // std::getline(std::cin, tmp);

    for (const char &c : "><^v") {
        const Point &d = dirs[c];
        if (d == Point() or dir + d == Point() or d == dir)
            continue;
        next = p + d;
        if (map[next.y][next.x] == '.') {
            // std::cout << "Checking direction: " << c << " " << d << ", p: " << p << ", next: " << next << std::endl;
            // score.push_back(next);
            findPaths(map, next, d, score + 1000, paths);
        }
    }
}


// 
int main(void) {
    String          text = readFile("example1.txt");
    StringVector    map = split(text, "\n");
    Vector<u_int>   paths;
    Point           start = findPoint(map, 'S');

    findPaths(map, start, dirs['>'], 0, paths);

    print(paths);

    return (0);
}

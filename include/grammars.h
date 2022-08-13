#ifndef __GRAMMARS__
#define __GRAMMARS__

#include <vector>
#include <string>

class Sign;

enum SignType {
    nFin = 0,
    Fin
};

class Sign {
public:
    std::string name;
    bool isFin;
    std::vector<std::vector<size_t>> productions;
    Sign() {}
    Sign(SignType type, std::string name) : name(std::move(name)), isFin(type) {}
};

class Grammar {
public:
    std::vector<Sign> signs;
    void read();
    void display();
    void display_N();
    bool isFin(size_t index) {
        return signs[index].isFin;
    }
private:
};

#endif
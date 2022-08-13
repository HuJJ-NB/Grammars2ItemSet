#ifndef __ITEMS__
#define __ITEMS__

#include <iostream>
#include <vector>
#include "grammars.h"

extern Grammar g;

class Item {
public:
    size_t sign;
    size_t production;
    size_t pos;
    void display () {
        std::cout << sign << " -> ";
        for (size_t i = 0; i < g.signs[sign].productions[production].size(); ++i) {
            if(i == pos) std::cout << ". ";
            std::cout << g.signs[sign].productions[production][i] << " ";
        }
        if (pos == g.signs[sign].productions[production].size()) std::cout << ". ";
        std::cout << std::endl;
    }
    size_t NextSign() {
        if (pos < g.signs[sign].productions[production].size()) return g.signs[sign].productions[production][pos];
        return 0;
    }
    Item next();
    Item(size_t sign, size_t pos, size_t production) : sign(sign), production(production) ,pos(pos) {}
};

class ItemSet {
public:
    std::vector<Item> set;
    std::vector<size_t> go;
    void display() {
        for (size_t i = 0; i < set.size(); ++i) {
            set[i].display();
        }
        for (size_t i = 0; i < go.size(); ++i) {
            if(go[i] > 0) std::cout << i << " go " << go[i] << std::endl;
        }
    }
};

class ItemSets {
public:
    std::vector<ItemSet> sets;
    ItemSets();
    size_t addClosure(ItemSet set);
    void Go(size_t index, size_t x);
    void display() {
        std::cout << "文法：" << std::endl;
        g.display();
        std::cout << "文法（数字表示）：" << std::endl;
        g.display_N();
        std::cout << "项目集：" << std::endl;
        for (size_t i = 0; i < sets.size(); ++i) {
            std::cout << i << "：" << std::endl;
            sets[i].display();
            std::cout << std::endl;
        }
    }
};

#endif
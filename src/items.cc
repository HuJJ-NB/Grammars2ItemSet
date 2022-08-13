#include <items.h>

Grammar g;

Item Item::next() {
    return Item{sign, pos + 1, production};
}

size_t ItemSets::addClosure(ItemSet set) {
    for (size_t i = 0; i < this->sets.size(); ++i) {
        for (size_t j = 0; j < set.set.size(); ++j) {
            if (set.set[j].pos != this->sets[i].set[j].pos || set.set[j].sign != this->sets[i].set[j].sign || set.set[j].production != this->sets[i].set[j].production)break;
            return i;
        }
    }

    std::vector<bool> book;
    book.assign(g.signs.size(), false);
    for (size_t i = 0; i < set.set.size(); ++i) {
        size_t ns = set.set[i].NextSign();

        if (ns > 0 && !g.isFin(ns)) {
            book[ns] = true;
        }
    }
    for (size_t i = 0; i < book.size(); ++i) {
        if (book[i]) {
            for (size_t j = 0; j < g.signs[i].productions.size(); ++j){
                set.set.push_back(Item{i,0,j});
            }
        }
    }
    set.go.assign(g.signs.size(), 0);
    this->sets.push_back(set);
    return this->sets.size() - 1;
}

void ItemSets::Go(size_t index, size_t x) {
    bool flag = false;
    ItemSet newSet;
    for (size_t i = 0; i < this->sets[index].set.size(); ++i) {
        if (this->sets[index].set[i].NextSign() == x) {
            flag = true;
            newSet.set.push_back(this->sets[index].set[i].next());
        }
    }
    if (flag) {
        this->sets[index].go[x] = this->addClosure(newSet);
    }
}

ItemSets::ItemSets() {
    g.read();
    ItemSet firstSet;
    firstSet.set.push_back(Item{0,0,0});
    this->addClosure(firstSet);

    for (size_t i = 0; i < this->sets.size(); ++i) {
        for (size_t j = 1; j < g.signs.size(); ++j) {
            this->Go(i, j);
        }
    }
}
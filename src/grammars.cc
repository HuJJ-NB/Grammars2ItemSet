#include <cstring>
#include <grammars.h>
#include <iostream>

void Grammar::read() {
    this->signs.clear();

    int nr_Fin = 0;
    int n;
    std::cout << "请输入非终结符号的数量" << std::endl;
    std::cin >> n;
    this->signs.reserve(2 * n);
    std::cout << "请分别输入座位开始符号的非终结符号的名称" << std::endl;
    std::string name;
    std::cin >> name;
    this->signs.push_back(Sign(nFin, name + "'"));
    this->signs.push_back(Sign(nFin, name));
    this->signs[0].productions.resize(1);
    this->signs[0].productions[0].push_back(1);

    if (n > 1) std::cout << "请分别输入剩余" << n - 1 << "个非终结符号的名称" << std::endl;
    for (int i = 0; i < n - 1; ++i) {
        std::string name;
        std::cin >> name;
        this->signs.push_back(Sign(nFin, name));
    }

    for (int i = 1; i <= n; ++i) {
        int nr_productions;
        std::cout << "请输入" << this->signs[i].name << "产生式的数量" << std::endl;
        std::cin >> nr_productions;
        this->signs[i].productions.resize(nr_productions);


        for (int j = 0; j < nr_productions; ++j) {
            int nr_signs;
            std::cout << "请输入第" << j << "条产生式的符号数量" << std::endl;
            std::cin >> nr_signs;
            this->signs[i].productions[j].resize(nr_signs);

            std::cout << "请输入第" << j << "条产生式" << std::endl;
            for (int k = 0; k < nr_signs; ++k) {
                std::string name;
                std::cin >> name;
                int p;
                for (p = 1; p <= n + nr_Fin; ++p) {
                    if (!name.compare(this->signs[p].name)) {
                        this->signs[i].productions[j][k] = p;
                        break;
                    }
                }
                if (p > n + nr_Fin) {
                    this->signs.push_back(Sign(Fin, name));
                    this->signs[i].productions[j][k] = n + ++nr_Fin;
                }
            }
        }
    }
}

void Grammar::display() {
    for (int i = 0; i < (int)this->signs.size(); ++i) {
        std::cout << this->signs[i].name;
        if (!this->signs[i].isFin) {
            std::cout << " -> ";
            for (int j = 0; j < (int)this->signs[i].productions.size(); ++j) {
                for (int k = 0; k < (int)this->signs[i].productions[j].size(); ++k) {
                    std::cout << this->signs[this->signs[i].productions[j][k]].name << " ";
                }
                if (j < (int)this->signs[i].productions.size() - 1) std::cout << "| ";
            }
        }
        std::cout << std::endl;
    }
}
void Grammar::display_N() {
    for (int i = 0; i < (int)this->signs.size(); ++i) {
        std::cout << i;
        if (!this->signs[i].isFin) {
            std::cout << " -> ";
            for (int j = 0; j < (int)this->signs[i].productions.size(); ++j) {
                for (int k = 0; k < (int)this->signs[i].productions[j].size(); ++k) {
                    std::cout << this->signs[i].productions[j][k] << " ";
                }
                if (j < (int)this->signs[i].productions.size() - 1) std::cout << "| ";
            }
        }
        std::cout << std::endl;
    }
}
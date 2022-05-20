#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <array>


#define MapContains(map, key) ((map).count(key) > 0)

int transition[4][4];

struct xiaoyezi {
    template<typename T> 
    size_t operator() (T const &a) const {
        return a[0] + a[1] * 50 + a[2] * 2500 + a[3] * 125000;
    }
}; 

bool cannotTransition(const std::array<int, 4> &key) {
    for (size_t i = 0; i < 4; i++) {
        if (key[i]>=2 && transition[i][i] != -1)
            return false;
        for (size_t j = i+1; j < 4; j++) {
            if ((key[i] != 0 && key[j] != 0) && transition[i][j] != -1) {
                return false;
            }
        }
    }
    return true;
}
bool isDestinatedToWin(const std::array<int, 4> &key) {
    static std::unordered_map<std::array<int, 4>, bool, xiaoyezi> map;
    if (MapContains(map, key)) {
        return map[key];
    }
    if (cannotTransition(key)) {
        return map[key] = false;
    }
    //可以转移，看下一步有没有对手失败的可能。
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = i; j < 4; j++) {
            if ((key[i]+key[j]>= 2 && key[i]>0 && key[j]>0) && transition[i][j] != -1) {
//            if ((key[i]+key[j]>= 2 && key[i]!=0 && key[j]!=0) && transition[i][j] != -1) {
                auto transitionedKey = key;
                --transitionedKey[i], --transitionedKey[j];
                ++transitionedKey[transition[i][j]];
                if (!isDestinatedToWin(transitionedKey)) {
                    return map[key] = true;
                }
            }
        }
    }
    return map[key] = false;
}
int main(int argc, const char **argv) {
    for (auto & i : transition) {
        for (int & j : i) {
            std::cin >> j; //range based
        }
    }
    int Q;
    std::cin >> Q;
    for (size_t i = 0; i < Q; i++) {
        std::array<int, 4> line{};
        std::cin >> line[0] >> line[1] >> line[2] >> line[3];
        std::cout << (isDestinatedToWin(line) ? "Satori" : "irotaS")<<std::endl; //加括号
    }
    return 0;
}
#include <array>
#include <bitset>
#include <iostream>
#include <vector>

//constexpr size_t MaxN = 300;
constexpr size_t MaxN = 20;
constexpr size_t MaxLen = MaxN * (MaxN - 1) / 2 + 1;
constexpr auto getPossibleNumbersOfIntersections() {
    //    std::array<std::bitset<MaxLen>, MaxN+1> possibleNumbersOfIntersections{{{0b1}, {0b1}, {0b11}, {0b1101}, }};
    std::array<std::array<bool, MaxLen>, MaxN + 1> possibleNumbersOfIntersections{{
            {true},
            {true},
            {true, true},
            {true, false, true, true},
    }};
    for (size_t i = 4; i <= MaxN; i++) {
        auto &set = possibleNumbersOfIntersections[i];
        for (size_t j = i; j >= 1; --j) {
            const auto remaining = i - j;
            const auto &prev = possibleNumbersOfIntersections[remaining];
            const auto newIntersect = remaining * j;
            for (size_t k = 0; k < MaxLen; k++) {
                if (prev[k])
                    set[k + newIntersect] = true;
            }
            //            set|=prev<<newIntersect;
        }
    }
    return possibleNumbersOfIntersections;
}
constexpr auto possibleNumbersOfIntersections = getPossibleNumbersOfIntersections();
int main() {
    int T, n;
    std::cin >> T;
    for (int i = 0; i < T; i++) {
        std::cin >> n;
        auto &result = possibleNumbersOfIntersections[n];
        for (size_t j = 0; j < MaxLen; j++) {
            if (result[j])//读取std::vector<bool>没有坑。
                std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}
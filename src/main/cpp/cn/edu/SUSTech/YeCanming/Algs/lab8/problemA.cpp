
#include <array>
#include <iostream>
#include <vector>

// static std::array<std::vector<bool>, 301> possibleNumbersOfIntersections{{true}, {true}, {true, true}, {true, false, true, true}};
// static std::array<std::vector<int>, 301> possibleNumbersOfIntersections{{1}, {1}, {1, 1}, {1, 0, 1, 1}, };
 static std::vector<int> possibleNumbersOfIntersections[301] {{1}, {1}, {1, 1}, {1, 0, 1, 1}, };
//static std::vector<std::vector<int>> possibleNumbersOfIntersections{{1}, {1}, {1, 1}, {1, 0, 1, 1}};
constexpr void solve() {
    for (size_t i = 4; i <= 300; i++) {
         auto &set = possibleNumbersOfIntersections[i];
         set = std::vector<int>(i * (i - 1) / 2 + 1);
//        std::vector<int> set(i * (i - 1) / 2 + 1);
        for (size_t j = i; j >= 1; --j) {
            const auto remaining = i - j;
            const auto &prev = possibleNumbersOfIntersections[remaining];
            const auto newIntersect = remaining * j;
            for (size_t k = 0; k < prev.size(); k++) {
                if (prev[k])
                    // set[k + newIntersect] = true;
                    set[k + newIntersect] = 1;
            }
        }
//        possibleNumbersOfIntersections.push_back(set);
    }
}
int main() {
    int T, n;
    std::cin >> T;
    solve();
    for (int i = 0; i < T; i++) {
        std::cin >> n;
        auto result = possibleNumbersOfIntersections[n];
        for (size_t j = 0; j < result.size(); j++) {
            if (result[j])//读取std::vector<bool>没有坑。
                std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}
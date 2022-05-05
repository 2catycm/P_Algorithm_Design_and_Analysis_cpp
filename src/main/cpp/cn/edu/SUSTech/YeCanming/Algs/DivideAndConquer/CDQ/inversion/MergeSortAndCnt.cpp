#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>
template<class InputIt1, class InputIt2, class OutputIt>
int64_t mergeAndCount(InputIt1 first1, const InputIt1 last1,
                      InputIt2 first2, const InputIt2 last2,
                      OutputIt d_first) {
    int64_t result{0};
    for (; first1 != last1; ++d_first) {
        if (first2 == last2) {
            std::copy(first1, last1, d_first);
            return result;
        }
        if (*first2 < *first1) {
            *d_first = *first2;
            ++first2;
            result+=std::distance(first1, last1);
        } else {
            *d_first = *first1;
            ++first1;
        }
    }
    std::copy(first2, last2, d_first);
    return result;
}
template<class It>
int64_t solve(const It first, const It last) {
    size_t len = std::distance(first, last);
    if (len<=1)
        return 0;
    size_t mid = len >> 1;
    int64_t result = solve(first, first + mid) + solve(first + mid, last);
    std::vector<int> temp(len);
    result += mergeAndCount(first, first + mid, first + mid, last, temp.begin());
    std::copy(temp.begin(), temp.end(), first);
    return result;
}
int main(int argc, const char **argv) {
    size_t n;
    std::cin >> n;
    std::vector<int> arrayA(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> arrayA[i];
    }
    std::cout << solve(arrayA.begin(), arrayA.end()) << std::endl;
    return 0;
}
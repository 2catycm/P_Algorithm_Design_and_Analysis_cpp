//
// Created by 叶璨铭 on 2022/5/5.
//
#pragma GCC Optimize(fast)
#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#define MapContains(map, key) ((map).count(key) > 0)
constexpr size_t INF = std::numeric_limits<decltype(INF)>::max();
constexpr size_t safeAdd(size_t a, size_t b) {
    if (a == INF || b == INF)
        return INF;
    else
        return a + b;
}
//std::string::iterator global_first;
template<class It>
size_t solve(const It first, const It last) {
    //    std::clog<<"solve("<<first-global_first<<", "<<last-global_first<<")"<<std::endl;
    static std::map<std::tuple<It, It>, size_t> answers;
    auto key = std::make_tuple(first, last);
    if (MapContains(answers, key)) {
        std::clog << "Already computed. Answer is " << answers[key] << std::endl;
        return answers[key];
    }
    auto len = std::distance(first, last);
    //    std::clog<<"Length is "<<len<<std::endl;
    //    if (len <= 1) {
    if (len <= 0) {
        //        std::clog<<"Answer is "<<len<<std::endl;
        return answers[key] = len;
    }
    if (len == 1) {
        return answers[key] = first[0] == '*' ? 0 : 1;
    }
    auto firstChar = first[0], lastChar = first[len - 1];
    if (firstChar == '*' && lastChar == '*') {
        auto solutionA = solve(first + 1, last - 1),// 左右*都不配，都是0.
                solutionB = solve(first + 1, last), // 左边* 不配，保留右边
                solutionC = solve(first, last - 1); // 右边*不配，保留左边
                                                    //        std::clog<<"Answer is the smallest among "<<solutionA<<", "<<solutionB<<", "<<solutionC<<std::endl;
        return answers[key] = std::min(solutionA, std::min(solutionB, solutionC));
    } else if (firstChar == '*') {
        //        auto solutionA = safeAdd(solve(first + 1, last - 1), 2),
        auto solutionA = safeAdd(solve(first, last - 1), 2),//默认匹配不牺牲*， 在里面的递归决议不匹配的时候才牺牲。
                solutionB = solve(first + 1, last);         // 牺牲*
                                                            //        std::clog<<"Answer is the smallest among "<<solutionA<<", "<<solutionB<<std::endl;
        return answers[key] = std::min(solutionA, solutionB);
    } else if (lastChar == '*') {
        auto solutionA = safeAdd(solve(first + 1, last), 2),//默认匹配不牺牲*， 在里面的递归决议不匹配的时候才牺牲。
                solutionB = solve(first, last - 1);         // 牺牲* 不匹配，但是左边还要。
                                                            //        std::clog<<"Answer is the smallest among "<<solutionA<<", "<<solutionB<<std::endl;
        return answers[key] = std::min(solutionA, solutionB);
    } else {
        //        std::clog<<"No * occurs."<<std::endl;
        if (firstChar == lastChar || firstChar == '?' || lastChar == '?')
            return answers[key] = safeAdd(solve(first + 1, last - 1), 2);
        else
            return answers[key] = INF;
    }
    assert(false);
}
template<class It>
size_t solveIteratively(const It first, const It last) {
    auto N = std::distance(first, last);
    std::vector<size_t> opt((N + 1) * (N + 1));
    //    std::fill(opt.begin(), opt.end(), INF);
    std::fill(opt.begin(), opt.end(), 0);
#define OPT(i, j) opt[(i) * (N + 1) + (j)]
    for (int i = 1; i <= N; ++i) {        // i是区间长度。
        for (int j = 0; j + i <= N; ++j) {//j+i是end，可以到N
            std::clog << "bruteForceSolve[" << j << ", " << j + i << ")" << std::endl;
            if (i == 1) {
                OPT(j, j+i) = first[j] == '*' ? 0 : 1;
            } else {
                auto firstChar = first[j], lastChar = first[j + i - 1];
                if (firstChar == '*' && lastChar == '*') {
                    auto solutionA = OPT(j + 1, j + i - 1),// 左右*都不配，都是0.
                            solutionB = OPT(j + 1, j + i), // 左边* 不配，保留右边
                            solutionC = OPT(j, j + i - 1); // 右边*不配，保留左边
                    std::clog << "Answer is the smallest among " << solutionA << ", " << solutionB << ", " << solutionC << std::endl;
                    OPT(j, j+i) = std::min(solutionA, std::min(solutionB, solutionC));
                } else if (firstChar == '*') {
                    //        auto solutionA = safeAdd(solve(first + 1, last - 1), 2),
                    auto solutionA = safeAdd(OPT(j, j + i - 1), 2),//默认匹配不牺牲*， 在里面的递归决议不匹配的时候才牺牲。
                            solutionB = OPT(j + 1, j + i);         // 牺牲*
                    std::clog << "Answer is the smallest among " << solutionA << ", " << solutionB << std::endl;
                    OPT(j, j+i) = std::min(solutionA, solutionB);
                } else if (lastChar == '*') {
                    auto solutionA = safeAdd(OPT(j + 1, j + i), 2),//默认匹配不牺牲*， 在里面的递归决议不匹配的时候才牺牲。
                            solutionB = OPT(j, j + i - 1);         // 牺牲* 不匹配，但是左边还要。
                    std::clog << "Answer is the smallest among " << solutionA << ", " << solutionB << std::endl;
                    OPT(j, j+i) = std::min(solutionA, solutionB);
                } else {
                    std::clog << "No * occurs." << std::endl;
                    if (firstChar == lastChar || firstChar == '?' || lastChar == '?')
                        OPT(j, j+i) = safeAdd(OPT(j + 1, j + i - 1), 2);
                    else
                        OPT(j, j+i) = INF;
                }
            }
//            std::clog << "Final choice: " << OPT(i, j) << std::endl; //典型错误
            std::clog << "Final choice: " << OPT(j, j+i) << std::endl;
        }
    }
    return OPT(0, N);
}
int main() {
    std::ios::sync_with_stdio(false);
    std::string s;
    std::cin >> s;
//    for (int i = 0; i < s.size(); ++i) {
//        std::clog<<i;
//    }
//    std::clog<<std::endl;
    //    global_first = s.begin(); //debug
    //    auto result = solve(s.begin(), s.end());
    auto result = solveIteratively(s.begin(), s.end());
    std::cout << (result == INF ? "AHHHHH" : std::to_string(result)) << std::endl;
    return 0;
}
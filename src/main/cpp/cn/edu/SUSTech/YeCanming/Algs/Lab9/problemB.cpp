//
// Created by 叶璨铭 on 2022/5/5.
//
#include <cassert>
#include <iostream>
#include <map>
#include <string>
#define MapContains(map, key) ((map).count(key) > 0)
constexpr size_t INF = std::numeric_limits<decltype(INF)>::max();
constexpr size_t safeAdd(size_t a, size_t b) {
    if (a == INF || b == INF)
        return INF;
    else
        return a + b;
}
std::string::iterator global_first;
template<class It>
size_t solve(const It first, const It last) {
    std::clog<<"solve("<<first-global_first<<", "<<last-global_first<<")"<<std::endl;
    static std::map<std::tuple<It, It>, size_t> answers;
    auto key = std::make_tuple(first, last);
    if (MapContains(answers, key)) {
        std::clog<<"Already computed. Answer is "<<answers[key]<<std::endl;
        return answers[key];
    }
    auto len = std::distance(first, last);
    std::clog<<"Length is "<<len<<std::endl;
//    if (len <= 1) {
    if (len <= 0) {
        std::clog<<"Answer is "<<len<<std::endl;
        return answers[key] = len;
    }
    if (len==1){
        return answers[key]= first[0]=='*'?0:1;
    }
    auto firstChar = first[0], lastChar = first[len - 1];
    if (firstChar == '*' && lastChar == '*') {
        auto solutionA = solve(first + 1, last - 1), // 左右*都不配，都是0.
             solutionB = solve(first + 1, last), // 左边* 不配，保留右边
             solutionC = solve(first, last - 1); // 右边*不配，保留左边
        std::clog<<"Answer is the smallest among "<<solutionA<<", "<<solutionB<<", "<<solutionC<<std::endl;
        return answers[key] = std::min(solutionA, std::min(solutionB, solutionC));
    } else if (firstChar == '*') {
        //        auto solutionA = safeAdd(solve(first + 1, last - 1), 2),
        auto solutionA = safeAdd(solve(first, last - 1), 2),//默认匹配不牺牲*， 在里面的递归决议不匹配的时候才牺牲。
                solutionB = solve(first + 1, last);     // 牺牲*
        std::clog<<"Answer is the smallest among "<<solutionA<<", "<<solutionB<<std::endl;
        return answers[key] = std::min(solutionA, solutionB);
    } else if (lastChar == '*') {
        auto solutionA = safeAdd(solve(first+1, last), 2),//默认匹配不牺牲*， 在里面的递归决议不匹配的时候才牺牲。
                solutionB = solve(first, last - 1);     // 牺牲* 不匹配，但是左边还要。
        std::clog<<"Answer is the smallest among "<<solutionA<<", "<<solutionB<<std::endl;
        return answers[key] = std::min(solutionA, solutionB);
    } else {
        std::clog<<"No * occurs."<<std::endl;
        if (firstChar == lastChar || firstChar == '?' || lastChar == '?')
            return answers[key] = safeAdd(solve(first + 1, last - 1), 2);
        else
            return answers[key] = INF;
    }
    assert(false);
}
int main() {
    std::string s;
    std::cin >> s;
    global_first = s.begin(); //debug
    auto result = solve(s.begin(), s.end());
    std::cout << (result == INF ? "AHHHHH" : std::to_string(result)) << std::endl;
    return 0;
}
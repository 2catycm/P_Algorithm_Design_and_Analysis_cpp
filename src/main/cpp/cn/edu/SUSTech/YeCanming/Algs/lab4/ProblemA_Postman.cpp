//
// Created by 叶璨铭 on 2022/4/3.
//

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>
namespace cn::edu::SUSTech::YeCanming::Algs::lab4 {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::lab4;
    struct Letter {
        int from, to, appearTime;
    };
    int64_t solvePostman(const int N, const int M, int K,
                         std::vector<int> distances, //复制，不修改外面的，但是里面修改。本方法不递归。
                         const std::vector<Letter> &letters) {
        // while 循环中不变的量：
        std::vector<int> latestAppearTime(N + 1);
        std::vector<int> receivedLetterCnt(N + 1);
        for (const auto &letter : letters) {
            receivedLetterCnt[letter.to]++;
            latestAppearTime[letter.from] = std::max(latestAppearTime[letter.from], letter.appearTime);
        }
        //循环计算的量: distances需要不断减少，下面的量需要重新计算
        std::vector<int> arriveTime(N + 1);
        std::vector<int> leaveTime(N + 1);
        std::vector<int64_t> influenceFactor(N - 1 + 1);//influenceFactor[i] 表示 distances[i]--导致的成本降低
        int64_t cost;
        while (K-- >= 0) {
            //未加速前 evaluation
            cost = 0;
            for (int i = 1; i <= N; ++i) {
                arriveTime[i] = leaveTime[i - 1] + distances[i - 1];//i=1这个公式也对，正好0是0.
                leaveTime[i] = std::max(arriveTime[i], latestAppearTime[i]);
            }
            for (const auto &letter : letters) {
                cost += int64_t(arriveTime[letter.to] - letter.appearTime);
            }
            //加速优化 iteration
            int64_t accumulatedAffectedLetters = 0;
            for (int i = N; i >= 2; --i) {//考虑到达房子 i 的时候，如果加速 i-1 到 i 的distance
                if (arriveTime[i] <= latestAppearTime[i]) {
                    //情况1：被挡住了。 包括等于，因为等于的时候，加速后仍然不能减少leaveTime
                    // 归零, 因为加速这一段和前面的任何一段，都无法影响后面的信件。
                    accumulatedAffectedLetters = (int64_t)receivedLetterCnt[i];//但是到达这里的信件还是可以影响的。
                } else {
                    //情况2：优化机会可以传递。
                    // 加速这一段，可以影响后面的和这里的信件。
                    accumulatedAffectedLetters += (int64_t)receivedLetterCnt[i];
                }
                influenceFactor[i - 1] = accumulatedAffectedLetters;
            }
            // 找到可以优化的（距离大于0）当中，最大的
            int argmax = 0;
            for (int i = 1; i <= N - 1; ++i) {
                assert(distances[i] >= 0);
                if (distances[i] == 0)
                    continue;
                if (influenceFactor[argmax] <= influenceFactor[i])//包括等于的情况，跳出0的非法状态。
                    argmax = i;
            }
            if (argmax == 0)
                break;//全部都是0，提前结束
            --distances[argmax];
        }
        return cost;
    }
}// namespace cn::edu::SUSTech::YeCanming::Algs::lab4
#ifndef NTEST
#define NTEST 1
#endif
#if NTEST
namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::lab4;
int main() {
    int N, M, K;
    std::cin >> N >> M >> K;//1:1e4, 1:5e5, 1:100
    std::vector<int> distances(N - 1 + 1);
    for (int i = 1; i <= N - 1; ++i) {
        std::cin >> distances[i];//0:1e9
    }
    std::vector<ThisPackage::Letter> letters(M);
    for (int i = 0; i < M; ++i) {
        auto &newLetter = letters[i];//这种写法不用构造新对象，利用已有的对象。
        std::cin >> newLetter.from >> newLetter.to >> newLetter.appearTime;
    }
    std::cout << ThisPackage::solvePostman(N, M, K, distances, letters) << std::endl;
    return 0;
}
#endif//NTEST
//
// Created by 叶璨铭 on 2022/4/2.
//
#pragma once
#include <cassert>
namespace cn::edu::SUSTech::YeCanming::Algs::DivideAndConquer {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::DivideAndConquer;
    /**
     * General purpose binary search algorithm, also known as "二分答案"(binary search for answer).
     * @tparam It
     * @tparam Pr
     * @param first
     * @param last
     * @param pred
     * @return the last element in the range that satisfies the predicate.
     * Behavior:
     *      Define the satisfaction sequence to be s, such that s[i] = pred(first[i]) .
     *      For example, the satisfaction sequence is 11111111000000.
     *      Then this algorithm will find the last 1('s iterator), which is before the first 0.
     * Warning:
     *      If the range is not monotonically decreasing according to the predicate,
     *      then the behavior is undefined.
     *      In other words, the satisfaction sequence must be monotonically non-increasing.
     * SpecialCase:
     *      If the sequence is 0000...0, then the result is first-1;
     * Time complexity: If std::distance(first, last) is n, then the time complexity is O(log n)
     */
    template<class It, class Pr>
    It binary_search_for_last_satisfies(It first, It last, const Pr& pred){
        while (std::distance(first, last)>0){ //当大于0的时候, 还有元素需要搜索。
            It mid = first + (std::distance(first, last)>>1);
            if (pred(*mid)){
                first = mid + 1; //If it satisfies, try to find a better match.
            } else{
                last = mid; //If it doesn't, we are now in the 0 section, let's try to look at
            }
        }
        assert (std::distance(first, last)==0);
        return first-1; //减1是因为first是激进指针，最后收敛的时候和last相等，但是last是一定不对的答案。
    }
}
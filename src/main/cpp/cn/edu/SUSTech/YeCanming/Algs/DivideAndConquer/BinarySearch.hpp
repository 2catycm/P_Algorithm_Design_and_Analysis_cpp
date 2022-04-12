//
// Created by 叶璨铭 on 2022/4/2.
//
#pragma once
#include <cassert>
#include <iterator>
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
     *      In other words, the satisfaction sequence must be monotonically non-increasing(ones then zeros).
     * SpecialCase:
     *      If the sequence is 0000...0(all are zero), then the result is std::end(your container), namely parameter "last";
     * Time complexity: If std::distance(first, last) is n, then the time complexity is O(log n)
     */
    template<class It, class Pr>
    It binary_search_for_last_satisfies(const It first, const It last, const Pr& pred){
        It left = first, right = last;
        while (std::distance(left, right)>0){ //当大于0的时候, 还有元素需要搜索。
            It mid = left + (std::distance(left, right)>>1);
            if (pred(*mid)){
                left = mid + 1; //If it satisfies, try to find a better match.
            } else{
                right = mid; //If it doesn't, we are now in the 0 section, let's try to look to our left.
            }
        }
        assert (std::distance(left, right)==0);
        if (left==first)
            return last; //全0的情况。如果first的左边有哨兵，那么是left-1，可惜C++管理左闭右开。
        return left-1;//减1是因为 left 是激进指针，最后收敛的时候和 right 相等，但是 right 是一定不对的答案, 所以结果必然是left-1。
    }
    /**
     * General purpose binary search algorithm, also known as "二分答案"(binary search for answer).
     * @tparam It
     * @tparam Pr
     * @param first
     * @param last
     * @param pred
     * @return the first element in the range that satisfies the predicate.
     * Behavior:
     *      Define the satisfaction sequence to be s, such that s[i] = pred(first[i]) .
     *      For example, the satisfaction sequence is 0000001111111.
     *      Then this algorithm will find the first 1('s iterator), which is after the last 0.
     * Warning:
     *      If the range is not monotonically increasing according to the predicate,
     *      then the behavior is undefined.
     *      In other words, the satisfaction sequence must be monotonically non-increasing(zeros then ones).
     * SpecialCase:
     *      If the sequence is 0000...0(all are zero), then the result is std::end(your container), namely parameter "last";
     * Time complexity: If std::distance(first, last) is n, then the time complexity is O(log n)
     */
    template<class It, class Pr>
    It binary_search_for_first_satisfies(const It first, const It last, const Pr& pred){
        It left = first, right = last;
        while (std::distance(left, right)>0){ //当大于0的时候, 还有元素需要搜索。
            It mid = left + (std::distance(left, right)>>1);
            if (pred(*mid)){
                right = mid; //If it satisfies, try to find a better match.
            } else{
                left = mid + 1; //If it doesn't, we are now in the 0 section, let's try to look to our right.
            }
        }
        assert (std::distance(left, right)==0);
        return left; //left 为保守指针，一定为正确答案（或者到达了last）。
    }
}
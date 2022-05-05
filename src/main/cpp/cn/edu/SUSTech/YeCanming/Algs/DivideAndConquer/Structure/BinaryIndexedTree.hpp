#pragma once
#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>
template<class R = int64_t>
class BinaryIndexedTree {
    const std::vector<R> &original;
    std::vector<R> tree;
    constexpr static int low_bit(int a) { return a & (-a); }

public:
    explicit BinaryIndexedTree(const std::vector<R> &original) : original{original}, tree{original} {
        for (int i = 1; i <= size(); ++i) {
            //method 1: definition
            for (int j = 1; j < low_bit(i); ++j) {
                tree[i] += original[i - j];
            }
            //method 2: incorrect
            //            for (int j = 1; j < low_bit(i)>>1; ++j) {
            //                tree[i] += tree[i - j];
            //            }
        }
        //method 3: 与其让我去加他，不如让他来加我(这种方法慢，tle)
        //        for (int i = 1; i <= size(); ++i) {
        //            for (int j = i+1; j <= size(); j+=low_bit(j)-1) {
        //                tree[j]+=original[i];
        //            }
        //        }
    }
//    void addAmong(int first, int last, R value) {
//        add(first, value);
//        add(last + 1, -value);
//    }
    void add(int index, R value) {
        for (; index <= size(); index += low_bit(index)) {
            tree[index] += value;//我的low_bit左移一位的那个节点，包括了我所包括的。因此我要提醒它更新。
        }
    }
    [[nodiscard]] R sumTo(int last) const {
        R ans{0};
        for (; last != 0; last -= low_bit(last)) {//之前答案管辖了low_bit个答案，没有管辖到前面的。
            ans += tree[last];                    // 当前是在答案中的，要加进去。
        }
        return ans;
    }
    [[nodiscard]] R get(int index) const {
        return sumTo(index) - sumTo(index - 1);
    }
    [[nodiscard]] R sumAmong(int first, int last) const {
        return sumTo(last) - sumTo(first - 1);
    }
    [[nodiscard]] int size() const noexcept {
        return tree.size() - 1;//0不用的。
    }
};

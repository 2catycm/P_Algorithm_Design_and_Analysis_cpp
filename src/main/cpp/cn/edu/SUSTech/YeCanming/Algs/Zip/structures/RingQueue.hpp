#pragma once
#include <array>
#include <queue>
#include <cassert>
namespace cn::edu::SUSTech::YeCanming::Algs::Zip::utilities {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip::utilities;
    /**
     * Fixed length array queue using ring algorithm.
     * @tparam T element type of the queue.
     * @tparam capacity Fixed length.
     */
    template<typename T, int capacity>
    class RingQueue {
        using reference = T &;
        using const_reference = const T &;
        using value_type = T;
        std::array<T, capacity + 1> mData;
        int mFront{0}, mRear{0};
        int modulus{capacity + 1};//modulus 与数组长度一致, capacity 比数组的长度要小一个。
        constexpr int safeMod(int maybeNegative, int positiveModulus) {
            return (maybeNegative + positiveModulus) % positiveModulus;//由于队列的特殊性。
        }

    public:
        template<typename Lambda>
        bool rear2frontTraversal(const Lambda &elementVisitor) {
            if (mRear >= mFront) {
                for (int i = mRear - 1; i >= mFront; --i) {
                    if (elementVisitor(mData[i])) {
                        return true;//返回了 finish标志，提前结束遍历。
                    }
                }
            } else {
                for (int i = mRear - 1; i >= 0; --i) {
                    if (elementVisitor(mData[i])) {
                        return true;
                    }
                }
                for (int i = capacity; i >= mFront; --i) {
                    if (elementVisitor(mData[i])) {
                        return true;
                    }
                }
            }
            return false;
        }
        void push(const value_type &value) {
            assert(!isFull());
            mData[mRear] = value;
            mRear = safeMod(mRear + 1, modulus);
        }
        void pop() {
            mFront = safeMod(mFront + 1, modulus);
        }
        bool isFull() {
            return safeMod(mFront - mRear, modulus) == 1;
        }
        bool isEmpty() {
            return mFront == mRear;
        }
        reference front() {
            return mData[mFront];
        }
        const_reference front() const {
            return mData[mFront];
        }

        reference back() {
            return mData[mRear-1];
        }
        const_reference back() const {
            return mData[mRear-1];
        }

        int size() {
            return (mRear - mFront + modulus) % modulus;//-1%6 == 5, 所以可以作差
        }
    };
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip::utilities
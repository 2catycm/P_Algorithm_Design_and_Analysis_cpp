//
// Created by 叶璨铭 on 2022/5/5.
//
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
/**
 * For example, a = {6, 6, 2, 3, 4}
 * the result should be {4, 4, 1, 2, 3}
 */
template<class It>
void discretize(It first, It last){
    auto n = std::distance(first, last);
    std::vector<int> indexes(n);
    for (int i = 0; i < n; ++i) {
        indexes[i] = i+1;
    }
    std::sort(indexes.begin(), indexes.end(), [&](int a, int b){
        return first[a-1]<first[b-1];
    });

    for (int id = 1, i = 0; i<n; i++){
        bool renewId = i+1<n && first[indexes[i]-1]!=first[indexes[i+1]-1];
        first[indexes[i]-1] = id;
        if (renewId)
            id++;
    }
}
int main(){
    size_t n;
    std::cin >> n;
    std::vector<int> arrayA(n+1);
    for (size_t i = 1; i <= n; i++) {
        std::cin >> arrayA[i];
    }
    discretize(arrayA.begin()+1, arrayA.end());
//    std::copy(arrayA.begin()+1, arrayA.end(), std::ostream_iterator<int>(std::clog, ", ")); //耗时操作，会tle
    std::vector<int> tree(n+1);
    auto low_bit = [](int x){return x&(-x);};
    auto sumTo = [&](int i){int64_t sum{}; for(;i>=1;i-=low_bit(i))sum+=tree[i]; return sum;};
    auto addAt = [&](int i, int v){for(;i<=n;i+=low_bit(i)) tree[i]+=v;};
    int64_t cnt{};
    for (size_t i = n; i >= 1; --i) {
        addAt(arrayA[i], 1);
        cnt+=sumTo(arrayA[i]-1);
    }
    std::cout<<cnt<<std::endl;
    return 0;
}

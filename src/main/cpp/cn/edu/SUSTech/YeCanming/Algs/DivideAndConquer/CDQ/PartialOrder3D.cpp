//
// Created by 叶璨铭 on 2022/5/3.
//
#define CCG GCC
#define OPTIMIZE optimize
#pragma CCG OPTIMIZE(3)
#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>
template <typename It>
bool P(It elem, const It i){
    if(elem==i)
        return false;
    for (int j = 0; j < 3; ++j) {
        if ((*elem)[j]>(*i)[j])
            return false;
    }
    return true;
}
//这是O(n)的分治
template <typename It>
int f(It first, It last, const It i){
    size_t N = std::distance(first, last);
    int result = 0;
    if (N<=5){
        for (It x=first; x!=last ; ++x) {
            if (P(x, i))
                result++;
        }
        return result;
    }
    It mid = first+(N>>1);
    int div_res = f(first, mid, i)+f(mid, last, i);
    return div_res;
}
int main(){
    int n, k; //1<=n<=1e5
    std::cin>>n>>k;
    std::vector<std::array<int, 3>> data(n);
    for (int i = 0; i < n; ++i) {
        auto& element = data[i];
        std::cin>>element[0]>>element[1]>>element[2];
    }
    std::vector<size_t> valueCnt(n); //满足P的数量为0,1,2, ... , n分别有多少个。
    for (int i = 0; i < n; ++i) {
        valueCnt[f(data.cbegin(), data.cend(), data.cbegin()+i)]++;
    }
    for (int d = 0; d < n; ++d) {
        std::cout<<valueCnt[d]<<std::endl;
    }
    return 0;
}
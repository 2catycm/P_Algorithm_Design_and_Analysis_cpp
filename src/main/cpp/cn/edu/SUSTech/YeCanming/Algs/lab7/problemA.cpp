#pragma GCC optimize(3)
#include <iostream>
#include <cstdint>
#include <map>
#include <tuple>
#include <cassert>
#include <vector>
#include <limits>
std::vector<uint32_t> weight;
std::vector<uint32_t> _prefix_sum;
void prefix_sum(){
   _prefix_sum.push_back(0);
    for (size_t i = 0; i < weight.size(); i++)
    {
        _prefix_sum.push_back(_prefix_sum[i]+weight[i]);
    }
}
uint64_t sum(size_t startInclusive, size_t endInclusive){
    return _prefix_sum[endInclusive+1]-_prefix_sum[startInclusive];
}
uint64_t opt(){
    const auto N = weight.size();
    std::vector<uint64_t> opt_vec(N*N); // 比如N是4， 查询是 0,3 , 
    #define OPT(a, b) opt_vec[(a)*N+(b)]
    for (size_t i = 0; i < N; i++) //i 为 区间首尾偏移量。
    {
        // 从 长度1 开始 是因为已经初始化为0过了。 不行，语法不过：opt_vec(N*N){}
        for (size_t j = 0; j < N&&j+i<N; j++) // j 为区间首
        {
            if (i==0)
            {
                OPT(j, j+i) = 0;
                continue;
            }
            OPT(j, j+i) = std::numeric_limits<uint64_t>::max();
            for (size_t k = 0; k < i; k++)
            {
                OPT(j, j+i) = std::min(OPT(j, j+i), OPT(j, j+k)+OPT(j+k+1, j+i));
            }
            OPT(j, j+i) += sum(j, j+i);
        }
    }
    return OPT(0, N-1);
}
int main(int argc, char const *argv[])
{
    std::ios::sync_with_stdio(false);
    size_t N;
    std::cin>>N;
    for (size_t i = 0; i < N; i++)
    {
        uint32_t w;
        std::cin>>w;
        weight.push_back(w);
    }
    prefix_sum();
    std::cout<<opt();
    return 0;
}

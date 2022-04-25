#pragma GCC optimize(3)
#include <iostream>
#include <cstdint>
#include <map>
#include <tuple>
#include <cassert>
#include <vector>
#include <limits>
// using namespace std;
// constexpr size_t MAX_SIZE = std::
std::vector<uint32_t> weight;
// uint64_t sum(size_t startInclusive, size_t endInclusive){
//     // static uint64_t sum[][];
//     if (startInclusive==endInclusive)
//     {
//         return weight[startInclusive];
//     }
//     assert(startInclusive<endInclusive);
//     static std::map<std::tuple<size_t, size_t>, uint64_t> sum_map;
//     if (sum_map.count(std::make_tuple(startInclusive, endInclusive))){
//         return sum_map[std::make_tuple(startInclusive, endInclusive)];
//     }
    
//     int mid = startInclusive + ((endInclusive-startInclusive)>>1);
//     return sum(startInclusive, mid)+sum(mid+1, endInclusive);
// }
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
uint64_t opt(size_t startInclusive, size_t endInclusive){
    if (startInclusive==endInclusive)
    {
        return 0;
    }
    assert(startInclusive<endInclusive);
    static std::map<std::tuple<size_t, size_t>, uint64_t> opt_map;
    if (opt_map.count(std::make_tuple(startInclusive, endInclusive))){
        return opt_map[std::make_tuple(startInclusive, endInclusive)];
    }
    uint64_t best = std::numeric_limits<uint64_t>::max();
    for (size_t i = startInclusive; i < endInclusive; i++)
    {
        best = std::min(best, opt(startInclusive, i)+opt(i+1, endInclusive));
    }
    return best+sum(startInclusive, endInclusive);
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
    std::cout<<opt(0, N-1);
    return 0;
}

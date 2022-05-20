//
// Created by 叶璨铭 on 2022/5/5.
//
#include <iostream>
#include <vector>
#include <map>
int f(int foodTo, int first, const int& len, const std::vector<int>& weight){
    static std::map<std::tuple<int, int>, int> ans;
    auto key = std::make_tuple(foodTo, first);
    if (ans.contains(key))
        return ans[key];
    ans[key] = 0;
    if (foodTo<=0 || (first+len)<0)
        ans[key] = 0;
    else if (foodTo==1){
        auto diff = weight[0]-first;
        auto diff_0 = -first;
        if (0<=diff && diff<=len){
            ans[key]++;
        }
        if (0<=diff_0 && diff_0<=len){
            ans[key]++;
        }
    }else{
        ans[key] = f(foodTo-1, first, len, weight)+f(foodTo-1, first-weight[foodTo-1], len, weight);
    }
    return ans[key];
}
int main(){
    int n, l, r;
    std::cin>>n>>l>>r;
    std::vector<int> weight(n);
    for (int i = 0; i < n; ++i) {
        std::cin>>weight[i];
    }
    std::cout<<f(n, l, r-l, weight)<<std::endl;
    return 0;
}
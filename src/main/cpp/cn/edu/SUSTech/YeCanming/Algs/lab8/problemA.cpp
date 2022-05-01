#include <vector>
#include <array>
#include <iostream>
constexpr 
std::vector<bool> posibleNumbersOfIntersections(int n){
    static std::array<std::vector<bool>, 300> OPT = {{1}, {1}, {1,1}, {1, 0, 1, 1}};
    if (OPT.size()>n){
        return OPT[n];
    }
    std::vector<bool> result(((n*(n-1))>>1)+1); //分配空间
}
int main(){
   int T, n;
   std::cin>>T;
   for (int i=0; i<T; i++){
        std::cin>>n;
        auto result = posibleNumbersOfIntersections(n);
        for (size_t j = 0; j < result.size(); j++){
            if(result[j]) //读取std::vector<bool>没有坑。
                std::cout<<j<<" ";
        }
        std::cout<<std::endl;
   }
}
#include <iostream>
#include <cstdint>
#include <cassert>
// 使用constexpr 优化了20倍到12ms。 C++17支持。
constexpr int safeMultiply(int a, int b, int modulus){
    assert(modulus>0);
    return (int)((int64_t) a * b% modulus);
}
constexpr int normalizeMod(int a, int modulus){
    assert (modulus>0);
    a%=modulus;
    return a<0?(a+modulus):a;
}
constexpr int fastPower(int a, int b, int modulus){
    assert (b>=0);
    assert (modulus>0);
    //将b视作二进制，取其二进制的低比特，不断乘到result上。
    int result = 1;
    for (int powered = a; b != 0; powered = (int)((int64_t) powered * powered % modulus), b >>= 1) {
        if ((b & 1) == 1)
            result = (int)((int64_t) result * powered % modulus); //不需要toIntExact，因为永远不会抛出异常，modulus会保证。
    }
    return result;
}
constexpr int primeModularInverse(int a, int primeModulus){
    assert( primeModulus>0);
    //根据费马小定理，a的p-1次方模p余1. 
    return normalizeMod(fastPower(a, primeModulus - 2, primeModulus), primeModulus);
}
// constexpr int modulus = 1000'000'007;
constexpr int modulus = 1000000007;
int solve(int n, int m, int k){
    assert (1<=n&&n<=1000); 
    assert (0<=m&&m<=n);
    assert (0<=k&&k<modulus);
    static int opt[1001][1001]{0}; //第一维度（行）是n，第二维度（列）是m
    //注意没有static的话，编译虽然成功，运行时因为函数栈太大报错。
    for (int i = 1; i <= n; i++) //行号
    {
        for (int j = 1; j <= i && j<=m; j++) //列号， 从1开始是因为第一列自动为0
        {
            if(i==j){
                opt[i][j] = safeMultiply(i, k, modulus);
                continue;
            }
            opt[i][j] = opt[i-1][j-1]+opt[i-1][j] % modulus;
            static constexpr auto inv_2 = primeModularInverse(2, modulus);
            if (opt[i][j]%2==0)
                opt[i][j]>>=1;
            else
                opt[i][j] = safeMultiply(inv_2, opt[i][j],  modulus);
        }
    }
    return opt[n][m];
}
int main() {
    int T; std::cin >> T; //<1000
    for (size_t i = 0; i < T; i++)
    {
        // 最多1000回合
        // 1000以下的必须加
        // 数字最多1e9+7
        int n,m,k;
        std::cin>>n>>m>>k;
        std::cout<<solve(n,m,k)<<std::endl;
    }
    return 0;
}

//
// Created by 叶璨铭 on 2022/5/29.
//
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <cstdint>
#include <cmath>
#include <iterator>
#define CharOrdinal(ch) ((ch)-'a')
#define ItOrdinal(it) CharOrdinal(*(it))
int64_t pSum{0};
template<class It>
void getPSum(It patternFirst, const It patternLast){
    for (;patternFirst!=patternLast;++patternFirst){
        int64_t p = ItOrdinal(patternFirst);
        pSum+= p*p+p;
    }
}
std::vector<int64_t> _prefix_sum;
template<class WhatEver>
void prefix_sum(WhatEver const& vec){
    _prefix_sum.push_back(0);
    for (size_t i = 0; i < vec.size(); i++){
        int64_t q = CharOrdinal(vec[i]);
        _prefix_sum.push_back(_prefix_sum[i]+q*(q-1));
    }
}
uint64_t sum(size_t startInclusive, size_t endInclusive){
    return _prefix_sum[endInclusive+1]-_prefix_sum[startInclusive];
}
int64_t getTSum(size_t i, size_t m){
    return sum(i, i+m-1);
}
namespace fft{
    const int MAX = 3e5+5;
    const double PI = std::acos(-1);
    struct comp{
        double x,y;
        comp(double xx = 0,double yy = 0){x = xx,y = yy;}
    };
    comp operator +(comp a,comp b){return comp(a.x+b.x , a.y+b.y);}
    comp operator -(comp a,comp b){return comp(a.x-b.x , a.y-b.y);}
    comp operator *(comp a,comp b){return comp(a.x*b.x-a.y*b.y , a.x*b.y+a.y*b.x);}

    int lim = 1;
    int l,r[MAX];
    void FFT(comp *A,int type){
        for(int i = 0;i < lim;++i)
            if(i < r[i])std::swap(A[i],A[r[i]]);
        for(int mid = 1;mid < lim;mid<<=1){
            comp omg(std::cos(PI/mid),type * std::sin(PI/mid));
            for(int R = mid<<1,j = 0;j < lim;j += R){
                comp w(1,0);
                for(int k = 0;k < mid;++k,w = w * omg){
                    comp x = A[j+k],y = w * A[j + mid + k];
                    A[j + k] = x + y;
                    A[j + mid + k] = x - y;
                }
            }
        }
    }
    comp aa[MAX],bb[MAX];
    void conv(std::string const& Text, std::string const& Pattern){
        int N = Text.size()-1;
        int M = Pattern.size()-1;
        for(int i = 0;i <= N;++i)aa[i].x = CharOrdinal(Text[i]);
        for(int i = 0;i <= M;++i)bb[i].x = CharOrdinal(Pattern[M-i]);
        while(lim <= N + M)lim<<=1,l++;
        for(int i = 0;i < lim;++i)
            r[i] = (r[i>>1]>>1) | ((i&1)<<(l-1));
        FFT(aa,1);
        FFT(bb,1);
        for(int i = 0;i <= lim;++i)aa[i] = aa[i] * bb[i];
        FFT(aa,-1);
    }
    int64_t getConv(size_t i, size_t m){
        return (int64_t)(aa[i+m-1].x/lim+0.5);
    }
}


//bool isMatched(int text, int pattern){
//    return !bool((text-pattern)*(text-pattern-1));
//}
//template<class It>
//bool isMatchedBruteForce(It textFirst, const It textLast, It patternFirst, const It patternLast){
//    for(;patternFirst!=patternLast; ++textFirst, ++patternFirst){
//        if (textFirst==textLast||!isMatched(ItOrdinal(textFirst), ItOrdinal(patternFirst)))
//            return false;
//    }
//    return true;
//}
bool isMatched(size_t i, size_t m){
    return 2*fft::getConv(i, m)==pSum+ getTSum(i, m);
}

template<class It>
std::vector<size_t> solve(const It textFirst, const It textLast, It patternFirst, It patternLast){
    size_t n = std::distance(textFirst, textLast);
    size_t m = std::distance(patternFirst, patternLast);
    std::vector<size_t> matchedIndexes;
    for (int i = 0; i+m-1 < n; ++i) {
        if (isMatched(i, m))
            matchedIndexes.emplace_back(i+1);
    }
    return matchedIndexes;
}
int main(){
    std::string Text, Pattern;
    std::cin>>Text>>Pattern;
    prefix_sum(Text);
    fft::conv(Text, Pattern);
    getPSum(Pattern.begin(),  Pattern.end());
    auto matchResult = solve(Text.begin(), Text.end(), Pattern.begin(),  Pattern.end());
    std::cout<<matchResult.size()<<std::endl;
    std::copy(matchResult.begin(), matchResult.end(), std::ostream_iterator<size_t>(std::cout, " "));
    return 0;
}
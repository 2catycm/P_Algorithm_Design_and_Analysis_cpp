//
// Created by 叶璨铭 on 2022/4/18.
//
#include "ZipUtils.hpp"
#include <iostream>
int main(){
    using namespace cn::edu::SUSTech::YeCanming::Algs::Zip;
    std::string src, dst;
    std::cin>>src>>dst;
    //TODO 判断dst存不存在，存在则警告将会覆盖。
    std::cout<<"Compressing..."<<std::endl;
    if (ZipUtils::compress(src, dst)){
        std::cout<<"Compress process has done successfully."<<std::endl;
        std::cout<<"Folder "<<src<<"\nhas been compressed into ZIP format file "<<dst<<std::endl;
    }else{
        std::cerr<<"Error: Compress process aborted."<<std::endl;
    }
}

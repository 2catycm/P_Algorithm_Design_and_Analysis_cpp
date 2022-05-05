//
// Created by 叶璨铭 on 2022/5/5.
//
#include "includer.hpp"
int main(){
#define AskFor(a) std::cout<<#a<<": "; std::string a; std::cin>>(a)
    AskFor(CppSourceFilePath);
    AskFor(IncludeDirectory); //目前只需要一个
    AskFor(TargetPath);
    //    BOOST_LOG_TRIVIAL(info) << "An informational severity message";
    auto lines = getFileContent(CppSourceFilePath);
    for (const auto& line:lines){
        std::cout<<line<<std::endl;
    }
    return 0;
}
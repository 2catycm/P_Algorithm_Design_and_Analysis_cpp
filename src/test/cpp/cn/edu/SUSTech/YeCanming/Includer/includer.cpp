//
// Created by 叶璨铭 on 2022/3/31.
//
#include <cassert>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
//#include <boost/log/trivial.hpp>
std::string getParentDirectoryWithSlash(const std::string& filepath){
    for (int i = 0; i < filepath.length(); ++i) {
        auto c = filepath[filepath.length()-1-i];
        if (c=='\\'||c=='/')
            return filepath.substr(0, filepath.length()-i);
    }
    assert (false);
    return {};
}
std::list<std::string> getFileContent(const std::string& filepath){
    std::ifstream file;
    file.open(filepath, std::ios::in);
    if(!file.is_open())
        return {};
    std::list<std::string> result;
    std::string strLine;
    while(std::getline(file,strLine)){
        result.push_back(strLine);
        auto len = strLine.size();
        const char* ch = strLine.c_str();
#define GoTroughWhite \
        for (; ch != ch+len; ch++) {\
            if (std::isspace(*ch))\
                continue;\
            break;\
        }
        GoTroughWhite
        if ((*ch)!='#')
            continue;
        ch++;
        GoTroughWhite
        if ((*ch)!='i')
            continue;
        char filename[256]{'\0'};
        for (; ch != ch+len; ch++) {
            if (*ch=='<')
                break;
            if (*ch=='"'){
                for (const char* ch1 = ch+1; ch1 != ch+len; ch1++){
                    if (*ch1=='"'){
                        std::copy(ch+1, ch1, filename);
                    }
                }
            }
        }
        if (strlen(filename)==0)
            continue;
        auto subfileContents = getFileContent(getParentDirectoryWithSlash(filepath)+filename);
        std::list<std::string>::iterator range_end = result.end();
        std::advance(range_end, -1);
        result.erase(range_end);
        for (const auto& line:subfileContents){
            result.push_back(line);
        }
    }
    return result;
}
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
#pragma once
//#define LZ77
//#ifdef LZ77
//#error "pragma失败了"
//#endif
#ifndef ZIP_LZ77
#define ZIP_LZ77
#include "cn/edu/SUSTech/YeCanming/Algs/Zip/structures/RingQueue.hpp"
#include <fstream>
#include <functional>
#include <limits>
#include <map>
#include <sstream>
#include <string_view>
#include <variant>
#include <vector>


namespace cn::edu::SUSTech::YeCanming::Algs::Zip::utilities {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip::utilities;
    size_t hash(const char *data, size_t size) {
        return std::hash<std::string_view>{}(std::string_view(data, size));
    }
    struct Lz77Literal {
        char byte;
        bool operator==(const Lz77Literal &rhs) const {
            return byte == rhs.byte;
        }
        bool operator!=(const Lz77Literal &rhs) const {
            return !(rhs == *this);
        }
    };
    struct Lz77Pointer {
        uint16_t distance;//0-32768
        uint16_t length;  //3-258
        bool operator==(const Lz77Pointer &rhs) const {
            return distance == rhs.distance &&
                   length == rhs.length;
        }
        bool operator!=(const Lz77Pointer &rhs) const {
            return !(rhs == *this);
        }
    };
    using Lz77Element = std::variant<Lz77Literal, Lz77Pointer>;
    //如果写在类内，用继承，那么构造函数、析构函数很难match上。
    // 没关系，运算符重载可以写在外面。
    bool operator==(const Lz77Element &lhs, const Lz77Element &rhs) {
        if (lhs.index() != rhs.index()) return false;
        try {
            const auto &l = std::get<Lz77Literal>(lhs);
            const auto &r = std::get<Lz77Literal>(rhs);
            return l == r;
        } catch (const std::bad_variant_access &e) {
            const auto &l = std::get<Lz77Pointer>(lhs);
            const auto &r = std::get<Lz77Pointer>(rhs);
            return l == r;
        }
    }
    bool operator!=(const Lz77Element &lhs, const Lz77Element &rhs) {
        return !(rhs == lhs);
    }
    //    struct Lz77Element : std::variant<Lz77Literal, Lz77Pointer> {
    //
    //    };
    std::vector<Lz77Element> lz77_compress(const char *buffer, size_t bufferLen) {
        std::vector<Lz77Element> result;
        // positions->hash
        //存的是每一个位置往后4个或者曾经匹配成功的长度的哈希值。
        constexpr auto windowSize = 32 * 1024;                //32kByte
        ThisPackage::RingQueue<size_t, windowSize> hashWindow;//队列头为窗口左侧，队列尾为窗口右侧。
        size_t i = 0;
        for (; i < bufferLen - 4;) {
            size_t current_hash = hash(buffer + i, 4);
            uint16_t distance = 0;
            bool hasFound = hashWindow.rear2frontTraversal([&](const size_t &hash) {
                distance++;
                return current_hash == hash;
            });
            if (hasFound) {
                uint16_t position = i - distance;//解压/输入流先前位置
                uint16_t length = 0;             //匹配长度
                for (size_t j = i + length; j < bufferLen && length <= 258; ++j, ++length) {
                    if (buffer[j] != buffer[position++])//匹配始终发生在输入流。
                        break;
                }
                if (length > 3) {
                    // 输出 distance + length
                    result.emplace_back(Lz77Pointer{distance, length});
                    // 更新字典
                    hashWindow.push(current_hash);
                    if (hashWindow.isFull()) {
                        hashWindow.pop();
                    }
                    //跳指针
                    i += length;
                    continue;
                }
                // should have continued here
                //else go to the unmatch case
            }
            // 输出literal
            result.emplace_back(Lz77Literal{buffer[i]});
            // 更新字典
            hashWindow.push(current_hash);
            if (hashWindow.isFull()) {
                hashWindow.pop();
            }
            //指针前进
            ++i;
        }
        //还有最后几个字节没有处理，没有在上面的for处理是防止hash无法计算。
        for (; i < bufferLen; ++i) {
            result.emplace_back(Lz77Literal{buffer[i]});
        }
        return result;// move construct
    }
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip::utilities
#endif//ZIP_LZ77

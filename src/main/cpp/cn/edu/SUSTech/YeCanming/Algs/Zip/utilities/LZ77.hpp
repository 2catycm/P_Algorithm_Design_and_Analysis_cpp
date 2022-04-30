#include <fstream>
#include <limits>
#include <map>
#include <sstream>

namespace cn::edu::SUSTech::YeCanming::Algs::Zip::utilities {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip::utilities;
    struct LZ77 {
        // std::stringstream dataStream{"", std::ios::in | std::ios::binary};
        // friend std::ostream &operator<<(std::ostream &fs, const LZ77 &lz77) {
        //     fs << lz77.dataStream.str();
        //     assert(fs.good());
        //     lz77.dataStream.clear();
        //     return fs;
        // }

        LZ77 write(const char *data, size_t size) {
            // LZ77的hash表，hash->pos  表示pos这个位置开始连续多个值能够求出这个hash。
            // 使用static一方面太大的数组不能放在栈空间，另一方面这样是线程安全的。
            // static uint16_t dictionary[];
            static std::map<size_t, uint16_t> dictionary;
            // 也可以pos->hash
            // 判断新的位置是否匹配
            auto matches = [&](size_t i) {
                size_t newHash = hash(data + i, 4);
                return dictionary.find(newHash) == dictionary.end();
            };
            for (size_t i = 0; i < size; ) {
                if (matches(i)) {
                    uint16_t posi = dictionary[newHash];
                     //求 distance
                    uint16_t distance = i-posi;
                    size_t j = i;
                    for (; j < size; j++) {
                       if(data[j]!=data[posi++])
                            break;
                    }
                    uint16_t length = j-i;
                    // 输出 distance + length
                    if (length>3){
                        
                    }
                }
                // 输出literal

                // 更新字典

                //指针前进
            }
        }

    private:
        static size_t hash(const char *data, size_t size) {
            return std::hash<std::string_view>{}(std::stringview(data, size));
        }
    };
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip::utilities
#include <gtest/gtest.h>
#include <span>
#define EXPECT_MEMEQ(val1, val2, limit)                                               \
    if (0 != memcmp(val1, val2, limit)) {                                             \
        std::cout << "Expected: " << std::hex << std::uppercase << std::setfill('0'); \
        for (const auto b : std::as_bytes(std::span{val1})) {                         \
            std::cout << std::setw(2) << std::to_integer<unsigned>(b) << ' ';         \
        }                                                                             \
        std::cout << '\n';                                                            \
        std::cout << "Actually: " << std::hex << std::uppercase << std::setfill('0'); \
        for (const auto b : std::as_bytes(std::span{val2})) {                         \
            std::cout << std::setw(2) << std::to_integer<unsigned>(b) << ' ';         \
        }                                                                             \
        std::cout << '\n';                                                            \
        EXPECT_TRUE(false);                                                           \
    }
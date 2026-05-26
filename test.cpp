#include <gtest/gtest.h>
#include <string>

// Простая функция для тестирования
std::string hello() {
    return "Hello, World!";
}

// Тест
TEST(BasicTest, HelloWorld) {
    EXPECT_EQ(hello(), "Hello, World!");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

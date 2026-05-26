#include <gtest/gtest.h>
#include <string>

class CurseRestrictionStrategy {
public:
    bool Check(const std::string& text) const {
        return text.find("fuck") == std::string::npos && 
               text.find("shit") == std::string::npos;
    }
};

TEST(CurseTest, BlocksFuck) {
    CurseRestrictionStrategy s;
    EXPECT_FALSE(s.Check("fuck"));
    EXPECT_TRUE(s.Check("hello"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

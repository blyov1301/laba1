#include <iostream>
#include <string>
#include <memory>

class TextRestrictionStrategy
{
public:
    virtual ~TextRestrictionStrategy() = default;
    virtual bool Check(std::string const& text) const = 0;
};

class CurseRestrictionStrategy : public TextRestrictionStrategy
{
public:
    bool Check(std::string const& text) const override
    {
        auto npos = std::string::npos;
        if (text.find("fuck") != npos || text.find("shit") != npos)
        {
            return false;
        }
        return true;
    }
};

class TextRestricter
{
public:
    explicit TextRestricter(std::unique_ptr<TextRestrictionStrategy>&& strategy)
        : strategy_(std::move(strategy))
    {}

    bool ConcatText(std::string const& text_1,
                    std::string const& text_2,
                    std::string& concatedText) const
    {
        concatedText = text_1 + text_2;
        return strategy_->Check(concatedText);
    }

private:
    std::unique_ptr<TextRestrictionStrategy> strategy_;
};

int main()
{
    int tests_passed = 0;
    int tests_failed = 0;
    
    auto strategy = std::make_unique<CurseRestrictionStrategy>();
    TextRestricter restricter(std::move(strategy));
    
    std::string result;
    
    // Тест 1: нормальный текст
    bool ok = restricter.ConcatText("hello", "world", result);
    if (ok == true && result == "helloworld") {
        std::cout << "✓ Test 1 passed" << std::endl;
        tests_passed++;
    } else {
        std::cout << "✗ Test 1 failed" << std::endl;
        tests_failed++;
    }
    
    // Тест 2: текст с fuck
    result.clear();
    ok = restricter.ConcatText("fuck", "you", result);
    if (ok == false && result.empty()) {
        std::cout << "✓ Test 2 passed" << std::endl;
        tests_passed++;
    } else {
        std::cout << "✗ Test 2 failed" << std::endl;
        tests_failed++;
    }
    
    // Тест 3: текст с shit
    result.clear();
    ok = restricter.ConcatText("bull", "shit", result);
    if (ok == false && result.empty()) {
        std::cout << "✓ Test 3 passed" << std::endl;
        tests_passed++;
    } else {
        std::cout << "✗ Test 3 failed" << std::endl;
        tests_failed++;
    }
    
    std::cout << "\n=== RESULTS ===" << std::endl;
    std::cout << "Passed: " << tests_passed << std::endl;
    std::cout << "Failed: " << tests_failed << std::endl;
    
    return tests_failed == 0 ? 0 : 1;
}

#include <iostream>
#include <string>
#include <memory>
#include <cassert>

// Копируем только нужные классы для теста
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
        if (strategy_->Check(concatedText))
        {
            return true;
        }
        else
        {
            concatedText.clear();
            return false;
        }
    }

private:
    std::unique_ptr<TextRestrictionStrategy> strategy_;
};

// Простой тест
void TestCurseRestriction()
{
    std::cout << "Testing CurseRestrictionStrategy...\n";
    
    auto strategy = std::make_unique<CurseRestrictionStrategy>();
    TextRestricter restricter(std::move(strategy));
    
    std::string result;
    
    // Тест 1: обычный текст должен пройти
    bool ok = restricter.ConcatText("hello", "world", result);
    assert(ok == true);
    assert(result == "helloworld");
    std::cout << "  Test 1 passed: normal text allowed\n";
    
    // Тест 2: текст с "fuck" должен быть заблокирован
    ok = restricter.ConcatText("fuck", "you", result);
    assert(ok == false);
    assert(result.empty());
    std::cout << "  Test 2 passed: curse word 'fuck' blocked\n";
    
    // Тест 3: текст с "shit" должен быть заблокирован
    ok = restricter.ConcatText("bull", "shit", result);
    assert(ok == false);
    assert(result.empty());
    std::cout << "  Test 3 passed: curse word 'shit' blocked\n";
    
    std::cout << "All tests passed!\n";
}

int main()
{
    TestCurseRestriction();
    return 0;
}

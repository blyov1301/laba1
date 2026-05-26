#include <iostream>
#include <memory>
#include <string>
#include <cassert>

// Копируем минимально необходимые классы для теста
class TextRestrictionStrategy
{
public:
    virtual ~TextRestrictionStrategy() = default;
    virtual bool Check(std::string const& text) const = 0;
};

class NoRestrictionStrategy : public TextRestrictionStrategy
{
public:
    bool Check(std::string const& text) const override { return true; }
};

class CurseRestrictionStrategy : public TextRestrictionStrategy
{
public:
    bool Check(std::string const& text) const override
    {
        return text.find("fuck") == std::string::npos && 
               text.find("shit") == std::string::npos;
    }
};

class LengthRestrictionStrategy : public TextRestrictionStrategy
{
public:
    LengthRestrictionStrategy(std::size_t min, std::size_t max) : min_(min), max_(max) {}
    bool Check(std::string const& text) const override
    {
        return text.length() >= min_ && text.length() <= max_;
    }
private:
    std::size_t min_, max_;
};

class TextRestricter
{
public:
    explicit TextRestricter(std::unique_ptr<TextRestrictionStrategy>&& s) : strategy_(std::move(s)) {}
    
    bool ConcatText(std::string const& a, std::string const& b, std::string& out) const
    {
        out = a + b;
        if (strategy_->Check(out)) return true;
        out.clear();
        return false;
    }
    
private:
    std::unique_ptr<TextRestrictionStrategy> strategy_;
};

// ============ ТЕСТ ============
int main()
{
    std::cout << "=== Running Tests ===\n";
    
    // Тест 1: NoRestrictionStrategy
    auto r1 = TextRestricter(std::make_unique<NoRestrictionStrategy>());
    std::string result;
    
    bool ok = r1.ConcatText("hello", "world", result);
    assert(ok == true);
    assert(result == "helloworld");
    std::cout << "✓ Test 1 passed: NoRestrictionStrategy\n";
    
    // Тест 2: CurseRestrictionStrategy
    auto r2 = TextRestricter(std::make_unique<CurseRestrictionStrategy>());
    
    ok = r2.ConcatText("bad ", "fuck", result);
    assert(ok == false);
    assert(result.empty());
    std::cout << "✓ Test 2 passed: CurseRestrictionStrategy\n";
    
    // Тест 3: LengthRestrictionStrategy (длина от 1 до 5)
    auto r3 = TextRestricter(std::make_unique<LengthRestrictionStrategy>(1, 5));
    
    ok = r3.ConcatText("ab", "cde", result);  // "abcde" длина 5
    assert(ok == true);
    assert(result == "abcde");
    
    ok = r3.ConcatText("too", "longgg", result);  // слишком длинная
    assert(ok == false);
    assert(result.empty());
    std::cout << "✓ Test 3 passed: LengthRestrictionStrategy\n";
    
    std::cout << "\n✅ ALL TESTS PASSED!\n";
    return 0;
}

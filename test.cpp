#include <cassert>
#include <string>

// Копируем нужные классы (или можно сделать #include, но проще скопировать)

class NoRestrictionStrategy {
public:
    bool Check(std::string const& text) const { return true; }
};

class CurseRestrictionStrategy {
public:
    bool Check(std::string const& text) const {
        return text.find("fuck") == std::string::npos && 
               text.find("shit") == std::string::npos;
    }
};

class LengthRestrictionStrategy {
public:
    LengthRestrictionStrategy(std::size_t min, std::size_t max) : min_(min), max_(max) {}
    bool Check(std::string const& text) const {
        return text.length() >= min_ && text.length() <= max_;
    }
private:
    std::size_t min_, max_;
};

template <typename T>
class TextRestricter {
public:
    explicit TextRestricter(T&& s) : strategy_(std::move(s)) {}
    
    bool ConcatText(std::string const& a, std::string const& b, std::string& out) const {
        out = a + b;
        if (strategy_.Check(out)) return true;
        out.clear();
        return false;
    }
private:
    T strategy_;
};

template <typename T>
auto MakeTextRestrictor(T&& s) { return TextRestricter<T>(std::move(s)); }

// Один тест - проверяем ConcatText с разными стратегиями
int main() {
    // Тест 1: NoRestrictionStrategy - всегда успех
    auto r1 = MakeTextRestrictor(NoRestrictionStrategy());
    std::string result;
    assert(r1.ConcatText("hello", "world", result) == true);
    assert(result == "helloworld");
    
    // Тест 2: CurseRestrictionStrategy - блокирует плохие слова
    auto r2 = MakeTextRestrictor(CurseRestrictionStrategy());
    assert(r2.ConcatText("bad ", "fuck", result) == false);
    assert(result.empty());
    
    // Тест 3: LengthRestrictionStrategy - проверка длины
    auto r3 = MakeTextRestrictor(LengthRestrictionStrategy(1, 5));
    assert(r3.ConcatText("ab", "cde", result) == true);   // "abcde" length 5
    assert(r3.ConcatText("too", "longgg", result) == false); // too long
    
    return 0; // Все тесты прошли
}

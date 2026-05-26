#include <iostream>
#include <memory>
#include <string>

class TextRestrictionStrategy
{
public:
    virtual ~TextRestrictionStrategy() = default;
    virtual bool Check(std::string const& text) const = 0;
};

class NoRestrictionStrategy : public TextRestrictionStrategy
{
public:
    bool Check(std::string const& text) const override
    {
        return true;
    }
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

class LengthRestrictionStrategy : public TextRestrictionStrategy
{
public:
    LengthRestrictionStrategy(std::size_t minLength, std::size_t maxLength)
        : minLength_(minLength), maxLength_(maxLength)
    {}

    bool Check(std::string const& text) const override
    {
        auto length = text.length();

        if (length < minLength_ || length > maxLength_)
        {
            return false;
        }

        return true;
    }

private:
    std::size_t minLength_, maxLength_;
};

class TextRestricter
{
public:
    explicit TextRestricter(std::unique_ptr<TextRestrictionStrategy>&& strategy)
        : strategy_(std::move(strategy))
    {}

    void PrintText(std::string const& text) const
    {
        if (strategy_->Check(text))
        {
            std::cout << text << std::endl;
        }
        else
        {
            std::cout << "** Given text was restricted. **" << std::endl;
        }
    }

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

    void ChangeStrategy(std::unique_ptr<TextRestrictionStrategy>&& strategy)
    {
        strategy_ = std::move(strategy);
    }

private:
    std::unique_ptr<TextRestrictionStrategy> strategy_;
};

void ConcatAndPrintText(TextRestricter const& textRestricter,
                        std::string const& text_1,
                        std::string const& text_2)
{
    std::string concatedText;
    
    if (textRestricter.ConcatText(text_1, text_2, concatedText))
    {
        std::cout << concatedText << std::endl;
    }
    else
    {
        std::cout << "** Concated text was restricted. **" << std::endl;
    }
}

void Test(TextRestricter const& textRestricter)
{
    textRestricter.PrintText("fuck");
    textRestricter.PrintText("looooooooooooooooooooooooooong text");
    ConcatAndPrintText(textRestricter, "hi sh", "it bye");
}

int main()
{
    TextRestricter textRestricter(std::make_unique<NoRestrictionStrategy>());

    std::cout << "[*] Test with 'NoRestrictionStrategy'." << std::endl;
    Test(textRestricter);

    std::cout << "\n[*] Test with 'CurseRestrictionStrategy'." << std::endl;
    textRestricter.ChangeStrategy(std::make_unique<CurseRestrictionStrategy>());
    Test(textRestricter);

    std::cout << "\n[*] Test with 'LengthRestrictionStrategy'." << std::endl;
    textRestricter.ChangeStrategy(std::make_unique<LengthRestrictionStrategy>(0, 8));
    Test(textRestricter);
}

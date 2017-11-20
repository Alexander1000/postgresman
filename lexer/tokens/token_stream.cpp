#include <vector>

class TokenStream
{
public:
    TokenStream()
    {
        this->tokenList.clear();
    }

    void add(Token* token)
    {
        this->tokenList.push_back(token);
    }

protected:
    std::vector<Token*> tokenList;
};

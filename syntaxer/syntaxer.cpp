class Syntaxer
{
public:
    Syntaxer(TokenStream* tokenStream)
    {
        this->tokenStream = tokenStream;
    }

    void analyze()
    {
    }

protected:
    TokenStream* tokenStream;
};

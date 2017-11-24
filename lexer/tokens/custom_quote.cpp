class TokenCustomQuote : public Token
{
public:
    TokenCustomQuote(int line, int column, IOReader* reader) : Token(line, column)
    {
        this->reader = reader;
    }

protected:
    IOReader* reader;
};

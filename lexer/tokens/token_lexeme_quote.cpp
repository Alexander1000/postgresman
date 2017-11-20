class TokenLexemeQuote : public Token
{
public:
    TokenLexemeQuote(int line, int column, IOReader* reader) : Token(line, column)
    {
        this->reader = reader;
    }

protected:
    IOReader* reader;
};

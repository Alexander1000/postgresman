class TokenLexemeNumeric : public Token
{
public:
    TokenLexemeNumeric(int line, int column, IOReader* reader) : Token(line, column)
    {
        this->reader = reader;
    }

protected:
    IOReader* reader;
};

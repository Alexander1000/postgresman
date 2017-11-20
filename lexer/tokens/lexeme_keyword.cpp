class TokenLexemeKeyword : public TokenLexemeWord
{
public:
    TokenLexemeKeyword(int line, int column, IOReader* reader) : TokenLexemeWord(line, column, reader)
    {
        this->reader = reader;
    }

protected:
    IOReader* reader;
};

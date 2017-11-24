class SquareBracketClose : public Token
{
public:
    SquareBracketClose(int line, int column, IOReader* reader) : Token(line, column)
    {
        this->reader = reader;
    }

protected:
    IOReader* reader;
};

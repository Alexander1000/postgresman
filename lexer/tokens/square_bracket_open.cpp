class SquareBracketOpen : public Token
{
public:
    SquareBracketOpen(int line, int column, IOReader* reader) : Token(line, column)
    {
        this->reader = reader;
    }

protected:
    IOReader* reader;
};

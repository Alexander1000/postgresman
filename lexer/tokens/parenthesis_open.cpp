class ParenthesisOpen : public Token
{
public:
    ParenthesisOpen(int line, int column, IOReader* reader) : Token(line, column)
    {
        this->reader = reader;
    }

protected:
    IOReader* reader;
};
